---
title: "SQL Server 打造定时语句系统"
date: 2019-08-29
categories:
  - SQL
tags:
  - SQL
keywords:
  - SQL Server
  - 定时语句
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/VLJB4m49/image.png
---

**定时语句**。

<!--more-->

<!-- toc -->

## 1、前言

只需提供**计划执行时间**和**SQL语句**即可在规定时间执行相应的语句。

<br>

## 2、具体步骤

### 2.1、创建定时语句管理表

```SQL
CREATE TABLE mdb.dbo.tSchedule (
  id INT IDENTITY(1, 1),
  execTime DATETIME NOT NULL,
  execContent VARCHAR(MAX) NOT NULL,
  isFinished INT DEFAULT 0,
  finishTime DATETIME NULL,
  errorMSG VARCHAR(MAX) NULL,
  inputTime DATETIME DEFAULT GETDATE()
)
```

| 字段名称          | 解释说明                                                    |
|:------------------|:------------------------------------------------------------|
| id                | 序号，用于确定语句唯一性                                    |
| execTime          | 需要执行的时间，必不可少                                    |
| execContent       | 需要执行的语句，必不可少                                    |
| isFinished        | 语句是否被执行过，0：未执行；1：执行成功；-1：执行失败      |
| finishTime        | 语句执行完成时间，无论是否执行成功都会更新该值              |
| errorMSG          | 语句执行遇到错误时，需要保存的错误日志                      |
| inputTime         | 数据插入时间                                                |

<br>

### 2.2、创建实现定时语句的存储过程

```SQL
CREATE PROCEDURE mdb.dbo.pSchedule AS
BEGIN
	
	DECLARE @t TABLE(
		i INT IDENTITY(1, 1),
		id INT,
		execContent VARCHAR(MAX)
	) 
	-- 查询所有需要被执行的语句
	INSERT INTO @t (id, execContent)
		SELECT id, execContent FROM mdb.dbo.tSchedule
			WHERE isFinished = 0 AND execTime <= GETDATE()
			ORDER BY execTime

	-- 初始化变量
	DECLARE @i INT, @n INT, @id INT, @execContent VARCHAR(max)
	-- “@n”表示共有多少条语句需要被执行
	SELECT @n = count(*) FROM @t
	-- “@i”表示当前需要被执行的是那一条语句
	SET @i = 1

	execLoop:
	-- 执行完毕则退出
	IF @i > @n RETURN
	-- 获取每次需要执行的语句
	SELECT @id = id, @execContent = execContent FROM @t WHERE i = @i
	-- 语句执行成功
	BEGIN TRY
		EXEC(@execContent)
		UPDATE mdb.dbo.tSchedule
			SET isFinished = 1, finishTime = GETDATE()
			WHERE id = @id
	END TRY
	-- 语句执行失败，则插入错误日志
	BEGIN CATCH
		UPDATE mdb.dbo.tSchedule
			SET isFinished = -1, finishTime = GETDATE(), errorMSG = ERROR_MESSAGE()
			WHERE id = @id
	END CATCH
	-- 进入下一次循环
	SET @i = @i + 1
	GOTO execLoop

END
```

<br>

### 2.3、创建 SQL Server 作业

首先我们应当 [启动 SQL Server 代理](https://docs.microsoft.com/zh-cn/sql/ssms/agent/start-stop-or-pause-the-sql-server-agent-service)
。接下来我们徐哟啊在**数据库引擎实例**中展开**SQL Server 代理**，右击**作业**选择**新建作业**，在弹出来的选项卡中填写以下信息：

- 在**常规**界面为作业设置名称，并确保勾选了**已启用**。

- 在**步骤**界面选择**新建**，在弹出窗口中设置需要执行的步骤。这里我们只需要执行存储过程**pSchedule**，所以应该在**命令**窗格填写`EXEC mdb.dbo.pSchedule`。

- 在**计划**界面选择**新建**，在弹出窗口中设置执行计划。**计划类型**中我们可以选择**CPU 空闲时启动**，此时我们必须提前 [设置 CPU 空闲时间和持续时间](https://docs.microsoft.com/zh-cn/sql/ssms/agent/set-cpu-idle-time-and-duration-sql-server-management-studio)，只有CPU状态满足设定的条件，作业才会被执行；当然我们也可以选择**重复执行**，此时我们应当设置作业每天间隔10分钟执行一次，并且确保**持续时间**从当天开始，无结束日期。

- 如果我们在**SQL Server 代理**中设置了**操作员**，此时我们还可以在**警报**或者**通知**界面，选择当作业执行失败时以邮件等形式告知相关人员，真正做到 *无事不登数据库* 。

{{< image group="group:作业" classes="fancybox nocaption fig-33" title="设置作业名称"
thumbnail="" src="https://i.postimg.cc/a.png" >}}
{{< image group="group:作业" classes="fancybox nocaption fig-33" title="设置执行步骤" src="https://i.postimg.cc/a.png" >}}
{{< image group="group:作业" classes="fancybox nocaption fig-33 clear" title="设置执行计划" src="https://i.postimg.cc/a.png" >}}

<br>

## 3、测试


```SQL
-- 设置10分钟之后，执行一条必然出错的语句
insert into mdb.dbo.tSchedule (execTime, execContent)
select dateadd(MINUTE, 10, getdate()), 'selet 1'

-- 设置20分钟之后，创建测试表
insert into mdb.dbo.tSchedule (execTime, execContent)
select dateadd(MINUTE, 20, getdate()), 'create table mdb.dbo.tTest(用户Id int, 信息 ntext)'

-- 设置30分钟之后，向测试表插入信息
insert into mdb.dbo.tSchedule (execTime, execContent)
select dateadd(MINUTE, 30, getdate()), 'insert into mdb.dbo.tTest values(123, ''abc'')'
```

<br>

