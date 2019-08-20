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
thumbnailImage: https://s2.ax1x.com/2019/08/17/muNHqH.png
---

**SQL Server** 中提供了**定时作业**的功能，可以帮助我们按照计划执行特定的任务，但这种方式每次都要在图形化界面设置一大堆条件才能启用。有没有一种便捷的方式，只需提供**计划执行时间**和**SQL语句**即可在规定时间执行相应的语句？这篇文章我们将介绍如何在 **SQL Server** 中打造**定时语句**系统。

<!--more-->

<!-- toc -->

假设我们的业务部门有一项需求——将某个用户禁言24小时，24小时后自动放开禁言。或者用户注销账号的时候，给用户留7天 *冷静时间* ，7天内用户可以放弃注销。

如果使用定时作业的方式完成这样的需求，我们可能需要编写大量的SQL语句，并且每次都需要手动在定时作业中设置执行时间。接下来介绍的定时语句系统，则可以让我们在面对这些大规模且随时有可能产生的、需要在未来处理的SQL语句时，只需要考虑两个因素——计划执行时间和SQL语句。

<br>

## 1、具体实现步骤

实现定时语句的过程可以分为三个步骤—— [创建定时语句管理表](#创建定时语句管理表)、 [创建实现定时语句的存储过程](#创建实现定时语句的存储过程)、 [创建 SQL Server 作业](#创建 SQL Server 作业)。为了方便演示，这里所有的操作我们都在数据库**mdb**中完成。

<br>

### 1.1、创建定时语句管理表

首先我们需要创建定时语句管理表，当创建定时语句时，需要要向这张表中插入计划执行时间和SQL语句，当定时语句被执行后，需要向这张表插入执行完成时间，如果执行失败我们还需要插入错误日志。以下是定时语句管理表中我们需要创建的所有字段及相应的释义：

| 字段名称          | 解释说明                                                    |
|:------------------|:------------------------------------------------------------|
| id                | 序号，用于确定语句唯一性                                    |
| execTime          | 需要执行的时间，必不可少                                    |
| execContent       | 需要执行的语句，必不可少                                    |
| isFinished        | 语句执行状态，0：未执行；1：执行成功；-1：执行失败          |
| finishTime        | 语句执行完成时间，无论是否执行成功都会更新该值              |
| errorMSG          | 语句执行遇到错误时，需要保存的错误日志                      |
| inputTime         | 数据插入时间                                                |

当然这里我们也可以稍作修改，不必提供计划执行时间，而是提供**延迟时间**（语句提交后需要等待多久才能执行）。此时我们需要修改存储过程中的相应内容，根据表中的**inputTime**字段和提供的延迟时间，得出计划执行时间。

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

<br>

### 1.2、创建实现定时语句的存储过程

接下来我们需要创建一个存储过程，每当这个存储过程被执行时，定时语句管理表中记录的，所有已经到了计划执行时间并且尚未被执行的语句，会按照计划执行时间的先后顺序逐一被执行。

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

### 1.3、创建 SQL Server 作业

最后我们需要建立一个作业来频繁的运行刚刚创建的存储过程，运行的越频繁，定时语句的实际执行时间就会与计划执行时间越接近。两者之间总是会存在误差，但相比任务需要被延迟的时间，误差应当是可以忽略不计的。

这里我们应当保证已经启用了 **SQL Server 代理**，如果尚未启用，可以根据 **SQL Server** 官方文档中介绍的流程 [启动 SQL Server 代理](https://docs.microsoft.com/zh-cn/sql/ssms/agent/start-stop-or-pause-the-sql-server-agent-service)
。接下来我们需要在**数据库引擎实例**中展开 **SQL Server 代理**，右击**作业**选择**新建作业**，在弹出来的选项卡中填写以下信息：

- 在**常规**界面为作业设置名称，并确保勾选了**已启用**。

- 在**步骤**界面选择**新建**，在弹出窗口中设置需要执行的步骤。这里我们只需要执行存储过程 **pSchedule** ，所以应该在**命令**窗格填写`EXEC mdb.dbo.pSchedule`。

- 在**计划**界面选择**新建**，在弹出窗口中设置执行计划。**计划类型**中我们可以选择 **CPU 空闲时启动**，此时我们必须提前 [设置 CPU 空闲时间和持续时间](https://docs.microsoft.com/zh-cn/sql/ssms/agent/set-cpu-idle-time-and-duration-sql-server-management-studio)，只有CPU状态满足设定的条件，作业才会被执行；我们也可以选择**重复执行**，此时我们应当设置作业每天间隔10分钟执行一次，并且确保**持续时间**从当天开始，无结束日期；当然我们还可以结合两种方法，设置多个计划，只要任一计划达到触发条件，作业就会执行。

- 如果我们在 **SQL Server 代理**中设置了**操作员**，此时我们还可以在**警报**或者**通知**界面，选择当作业执行失败时以邮件等形式告知相关人员，真正做到 *无事不登数据库* 。

{{< image group="group:作业" classes="fancybox nocaption fig-33" title="设置作业名称" thumbnail="https://s2.ax1x.com/2019/08/17/mu16AK.png" src="https://s2.ax1x.com/2019/08/17/mu1s76.png" >}}
{{< image group="group:作业" classes="fancybox nocaption fig-33" title="设置执行步骤" thumbnail="https://s2.ax1x.com/2019/08/17/mu1d1J.png" src="https://s2.ax1x.com/2019/08/17/mu1Dn1.png" >}}
{{< image group="group:作业" classes="fancybox nocaption fig-33 clear" title="设置执行计划" thumbnail="https://s2.ax1x.com/2019/08/17/mu1wc9.png" src="https://s2.ax1x.com/2019/08/17/mu1r0x.png" >}}

<br>

## 2、测试定时语句系统

现在我们需要测试定时语句系统能否正常运行。这里我们测试了定时语句系统能否处理必然出错的语句；定时语句系统如果处理计划执行时间不同的数据；以及在不同时间插入定时语句是否有影响。

正如之前提到的那样，当我们设置定时语句时，只需要向定时语句管理表中插入计划执行时间和SQL语句即可。但是当SQL语句篇幅比较大，或者SQL语句中的大部分内容都有复用价值时，我们还是应当将SQL语句封装为存储过程（或者函数等），通过传递变量的方式实现不同的作用。此外我们还需要注意，这里不能用SQL语句做查询，因为我们无法接收到查询结果。

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

{{< image classes="fancybox nocaption fig-100 clear" title="定时语句系统测试结果" src="https://s2.ax1x.com/2019/08/17/mu10XR.png" >}}

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 如何使用定时语句系统，实现文章开头所说的业务需求？

{{< /note >}}

