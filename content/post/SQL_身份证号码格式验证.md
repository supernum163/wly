---
title: "SQL Server 使用SQL检查用户身份证号码格式"
date: 2019-07-26
categories:
  - SQL
tags:
  - SQL
keywords:
  - SQL Server
  - 身份证号码格式检查
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/VLJB4m49/image.png
---

如今搭建网络交易平台大多需要用户进行**实名认证**，但有时候用户填写的实名认证信息有可能是随手乱写的，也有可能是精心伪造的。尤其是**身份证号码**，必须进行**格式验证**才能入库。那么这篇文章，我们就将介绍如何使用**SQL**检查用户身份证号码格式。

<!--more-->

<!-- toc -->

## 1、身份证号码格式

要验证用户输入的居民身份证号码是否正确，首先我们需要知道身份证号码的格式。我国现行的**二代居民身份证**，**身份证号码**是由十七位数字加一位**校验码**构成的，而且身份证号码的不同部分分别有不同的含义。

- 前六位数字是**地址码**，代表了居民出生地的行政区划代码，按照**GB/T2260**的规定执行。其中：前一、二位数字代表所在省（直辖市、自治区）的代码；第三、四位数字代表所在地（市）的代码；第五、六位数字代表所在县（市、旗、区）的代码。

- 中间八位数字（第七位至十四位）是**生日码**，代表了居民的出生年月日。生日码按公历计算，年月日之间没有分割符。

- 紧接着三位数字（第十五位至十七位）是**顺序码**，代表了在同一地址码所标识的区域范围内，为同一个日期出生的人编定的顺序号。顺序码的奇数分配给男性，偶数分配给女性。

- 最后一位（第十八位数）是**校验码**，计算方法是将身份证前十七位数分别乘以不同系数，从第一至十七位的系数分别为**7、9、10、5、8、4、2、1、6、3、7、9、10、5、8、4、2**，将这十七位数字和系数相乘的结果相加，用加出来的和除以11，所得余数由小到大分别对应**1、0、X、9、8、7、6、5、4、3、2**（注意这里的**X**一定是大写的）。

<br>

## 2、使用SQL检查身份证号码格式

根据以上规则，我们可以编写SQL语句检查身份证号码格式。为了方便反复调用这里的SQL语句，我们可以在SQL Server中自定义一个名为**身份证号码格式检查**的SQL函数，它可以接受一个用户端传来的字符串，判断是否符合身份证格式规范，并以整形数字的形式返回结果：不符合规范返回0，未检测出错误返回1。这里我们也可以返回多种状态，比如符合规范但不满18周岁返回-1等等。

以下SQL函数中，我们首先检查了用户输入的内容是否由十七位数字加一位校验码构成。接下来理论上我们应当检查地址码部分，但是地址码比较复杂，不容易直接通过SQL语句写明白其中的逻辑，最好的方式就是下载一份地址码对照表，再用**查表法**检查用户输入的相应内容是否为真正的地址码，但我们这里直接略过了这一步。接下来我们检查了用户的出生日期，并设定年龄超出150周岁的人不存在，小于18周岁的人不能进行网络交易。接下来的顺序码除了根据用户填写的性别进行检查，就没有更好的检查方式了，所以我们这里直接略过了这一步。实际上，只要不是精心伪造，即使略过地址码和顺序码的检查，我们仍有很大把握通过校验码判断出用户输入的内容是否为虚假身份证号码。

```SQL
CREATE FUNCTION 身份证号码格式检查
(
	@citizenID VARCHAR(64)
)
	RETURNS INT
AS BEGIN

	DECLARE 
		@birthDate DATE,
		@lastLetter CHAR,
		@verIfyLetter CHAR,
		@idx INT,
		@tmpChar CHAR,
		@tmpNum INT, 
		@checksum INT

		

	-- 身份张号码长度必须为18位
	IF LEN(@citizenID) != 18 or DATALENGTH(@citizenID) != 18 BEGIN
	    RETURN 0
	END

	-- 身份证号码前17为必须为数字
	SET @idx = 1
	WHILE @idx < 18 BEGIN
		SET @tmpChar = SUBSTRING(@citizenID, @idx, 1)
		IF  @tmpChar < '0' OR @tmpChar > '9' BEGIN
			RETURN 0
		END
		SET @idx = @idx + 1
	END

	-- 身份证号码最后一位可以为数字或字母"X"
	SET @tmpChar = SUBSTRING(@citizenID, @idx, 1)
	IF (@tmpChar < '0' OR @tmpChar > '9') AND @tmpChar != 'X' BEGIN
		RETURN 0
	END

	-- 出生日期检验
	SET @birthDate = TRY_CONVERT(DATE, SUBSTRING(@citizenID, 7, 8), 112)
	IF @birthDate IS NULL BEGIN
		RETURN 0
	END

	-- 出生日期检验，超出150周岁
	IF DATEDIFF(YEAR, @birthDate, GETDATE()) > 150 BEGIN
		RETURN 0
	END
	
	-- 出生日期检验，未满18周岁
	IF DATEDIFF(YEAR, @birthDate, GETDATE()) < 18 BEGIN
		RETURN 0
	END

	-- 尾号校验
	SET @idx = 1
	SET @checksum = 0
	WHILE @idx < 18 BEGIN
		SET @tmpNum = TRY_PARSE(SUBSTRING(@citizenID, @idx, 1) AS INT)
		SET @checksum = @checksum + @tmpNum * choose(@idx, 7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2)
		SET @idx = @idx + 1
	END
	SET @lastLetter = SUBSTRING(@citizenID, @idx, 1)
	SET @checksum = @checksum % 11 + 1
	SET @verIfyLetter = choose(@checksum, '1','0','X','9','8','7','6','5','4','3','2')
	IF @lastLetter != @verIfyLetter BEGIN
		RETURN 0
	END

	-- 未检测出错误
	RETURN 1

END
```

接下来让我们伪造几个身份证号码，检查刚刚编写的SQL函数能否给出正确的判断。

```
SELECT dbo.身份证号码格式检查('987654321')
-- 返回结果为0，字符串长度不够18位

SELECT dbo.身份证号码格式检查('1234567890abcdefgh')
-- 返回结果为0，字符串中包含非法字符

SELECT dbo.身份证号码格式检查('123456789012345678')
-- 返回结果为0，出生日期无效

SELECT dbo.身份证号码格式检查('123456201001011234')
-- 返回结果为0，小于18周岁

SELECT dbo.身份证号码格式检查('123456199001011234')
-- 返回结果为0，校验码不符

SELECT dbo.身份证号码格式检查('123456199001011233')
-- 返回结果为1，未检测出错误（注意：没有123456这个地址码）
```

<br>

