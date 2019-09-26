---
title: R语言与数据库资源链接管理
date: 2019-10-01
categories:
  - R语言
  - IO管理
tags:
  - R语言IO管理
keywords:
  - R语言
  - IO管理
  - 数据库资源链接管理
thumbnailImagePosition: left
thumbnailImage: https:.png
---

R语言作为一门统计分析类计算机语言，与数据库对接读写数据是必不可少的操作。这篇文章我们将介绍R语言与数据库资源链接管理。

<!--more-->

<!-- toc -->

R语言中建立并管理数据库资源连接的主流方式有两种，**ODBC**（**Open Database Connectivity**）方式，**DBI**（**R Database Interface**）方式。其中ODBC方式需要我们在操作系统中，使用ODBC管理软件事先配置好数据库链接方式。而DBI方式本质上是**JDBC**（**Java Database Connectivity**）在R语言中的实现，所以我们需要事先安装并配置{{< hl-text purple >}}rjava{{< /hl-text >}}程序包。

<br>

## 1、ODBC方式

使用ODBC方式连接数据库，需要用到ODBC管理软件。window操作系统下自带**ODBC 数据资源管理器**，而对于**unix**类操作系统，我们可能需要手动安装 [unixODBC](http://www.unixodbc.org/) 软件。

接下来我们需要安装与数据库相应的**ODBC驱动程序**，大部分驱动程序都可以在数据库相应的官方网站中直接下载，比如 [MySQL ODBC Driver](https://dev.mysql.com/downloads/connector/odbc/) 、 [SQL Server ODBC Driver](https://docs.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server) 。

<br>

### 1.1、window操作系统ODBC配置

在window操作系统O中配置ODBC，我们只需要打开**ODBC 数据资源管理器**点击**添加**，接下来依次选择需要使用的数据库驱动程序、设置**DSN**（**Data Source Name**）及数据库所在服务器地址、设置登陆名及密码，设置其它必要信息并一路确定即可建立**ODBC 数据源**。更多帮助信息请参考： [ODBC 数据资源管理器 使用帮助](https://support.office.com/zh-cn/article/%e7%ae%a1%e7%90%86-odbc-%e6%95%b0%e6%8d%ae%e6%ba%90-b19f856b-5b9b-48c9-8b93-07484bfab5a7?ui=zh-CN&rs=zh-CN&ad=CN) 。

{{< image group="group:ODBC" classes="fancybox nocaption fig-33" title="步骤一" thumbnail="https://s2.ax1x.com/2019/08/17/mu16AK.png" src="https://s2.ax1x.com/2019/08/17/mu1s76.png" >}}
{{< image group="group:ODBC" classes="fancybox nocaption fig-33" title="步骤二" thumbnail="https://s2.ax1x.com/2019/08/17/mu1d1J.png" src="https://s2.ax1x.com/2019/08/17/mu1Dn1.png" >}}
{{< image group="group:ODBC" classes="fancybox nocaption fig-33 clear" title="步骤三" thumbnail="https://s2.ax1x.com/2019/08/17/mu1wc9.png" src="https://s2.ax1x.com/2019/08/17/mu1r0x.png" >}}

<br>

### 1.2、unix类操作系统ODBC配置

在unix类操作系统O中配置ODBC，我们可以安装unixODBC图形化界面，像在windows操作系统中一样配置ODBC。当然我们也可以直接修改unixODBC的配置文件（配置文件大多在`/etc`或`/usr/local/etc`文件夹下），其中**odbcinst.ini**文件中需要配置数据库驱动程序，**odbc.ini**文件中需要配置**DSN**相关信息。最后我们可以在命令行使用` isql DSN UID PWD`的形式测试链接是否有效。

```
## odbcinst.ini
[mssqlDriver]
Driver=/opt/microsoft/msodbcsql17/lib64/libmsodbcsql-17.3.so.1.1

## odbc.ini
[mssql]
Driver = mssqlDriver
Server = tcp: 192.168.1.10, 1433
Database = mdb
```

<br>

### 1.3、R语言中使用ODBC

以ODBC的方式连接数据库，需要使用{{< hl-text purple >}}RODBC{{< /hl-text >}}程序包。注意RODBC连接到数据库时，用到的**dsn**参数必须是在ODBC管理软件中设置的。

```R
conn <- RODBC::odbcConnect(dsn = "dsnName", uid = 'userName', pwd = 'password')
```

RODBC中的函数包含两大类，其中的以**odbc**开头的函数主要负责管理数据库连接、作为底层命令查询及获取数据；而以**sql**开头的函数则可以看作是使用者层面的函数，主要用于执行SQL语句，增删改查表格等。以下是RODBC中的一些常用函数：

| 函数               | 解释说明
|:-------------------|:-----------------------------------------------------------------
| odbcConnect        | 建立数据库链接
| odbcReConnect      | 重新建立数据库链接
| odbcClose          | 关闭数据库链接
| odbcCloseAll       | 关闭所有数据库链接
| odbcGetInfo        | 获取当前数据库链接的各项信息（服务器名称、数据库名称、数据库驱动信息等）
| getSqlTypeInfo     | 通过数据库驱动名称（由**odbcGetInfo**获取），获取R语言对象在数据库中对应的数据类型
| setSqlTypeInfo     | 通过数据库驱动名称，修改R语言对象在数据库中对应的数据类型
| odbcSetAutoCommit  | 开启一次SQL语句批处理，`autoCommit = TRUE`时会自动提交处理结果，每条语句都是独立的
| odbcEndTran        | 提交或放弃SQL语句批处理结果
| sqlQuery           | 在数据库中执行SQL语句，并直接取出结果
| sqlTypeInfo        | 获取当前数据库中所有数据类型信息
| sqlTables          | 列举数据库中包含的表格（包括表格、视图等）
| sqlColumns         | 列举数据库中某个表格的字段信息
| sqlPrimaryKeys     | 列举数据库中某个表格的主键信息
| sqlFetch           | 读取数据库中的某个表格（也可以读取前**n**行）
| sqlFetchMore       | 读取**sqlFetch**未读取完毕的表格中的剩余部分
| sqlSave            | 向数据库中存入一个表格，或向已存在的表格中插入数据
| sqlUpdate          | 向数据库中的某个表格插入数据
| sqlCopy            | 将数据库中某条语句对应的查询结果存储到表格中
| sqlCopyTable       | 将数据库中的某个表格拷贝到另一个表格中
| sqlClear           | 删除数据库中某个表格的所有数据
| sqlDrop            | 删除数据库中的某个表格

<br>

## 2、DBI方式

使用DBI方式连接数据库时，首先需要安装{{< hl-text purple >}}DBI{{< /hl-text >}}程序包，但DBI并不负责直接与数据库连接，而是提供了一系列的连接规范，类似于Java中的接口类。所以我们还需要安装与数据库相对应的驱动程序包，比如{{< hl-text purple >}}RMySQL、RSQLServer、RSQLite{{< /hl-text >}}等。当然我们也可以使用ODBC的驱动程序，此时需要使用{{< hl-text purple >}}odbc{{< /hl-text >}}程序包。

由于DBI中的函数可以被各种类型的驱动程序包实现，所以使用这些函数操作不同类型的数据库时，使用方式、返回结果可能会稍有不同，或者有些函数未被实现、有些函数的实现方式与设计理念不符。其中最大的差别应该是数据库的连接方式：

```R
# 连接 SQLServer
conn <- DBI::dbConnect(drv = RSQLServer::SQLServer(), 
  server = "serverIP/hostName", port = "port", database = 'dbName', 
  properties = list(user="userName", password='password'))
# 连接 MySQL
conn <- DBI::dbConnect(drv = RMySQL::MySQL(), 
  host = "serverIP/hostName", port = "port", dbname = "dbName", 
  uid = 'userName', pwd = 'password')
# 连接 SQLite
conn <- DBI::dbConnect(drv = RSQLite::SQLite(), 
  dbname = 'dbName.db')
# 使用odbc驱动连接数据库
conn <- DBI::dbConnect(drv = odbc::odbc(), 
  dsn = "dsnName", dbname = "dbName", 
  uid = 'userName', pwd = 'password')
```

DBI中的函数大部分以**db**开头，功能包含了管理链接、增删改查等各个方面。其它函数大多属于底层函数，主要负责使上层函数使用起来更加人性化。以下是DBI中的一些常用函数：

| 函数               | 解释说明
|:-------------------|:-----------------------------------------------------------------
| dbCanConnect       | 判断能否与某个数据库建立链接
| dbConnect          | 建立数据库链接
| dbDisconnect       | 断开数据库链接
| dbIsValid          | 判断当前数据库链接是否为有效链接
| dbIsReadOnly       | 判断当前数据库链接是否为只读链接
| dbExecute          | 在数据库中执行SQL语句，并直接取出结果（有多少行受影响），用于增删改
| dbGetQuery         | 在数据库中执行SQL语句，并直接取出结果，用于查询
| dbSendStatement    | 向数据库中发送需要执行的SQL语句，返回SQL执行结果外部指针（**DBIResult**），用于增删改
| dbGetRowsAffected  | 查询受当前SQL执行结果影响的记录数
| dbSendQuery        | 向数据库中发送需要执行的SQL语句，返回SQL执行结果外部指针，用于查询
| dbListResults      | 列举数据库中所有需要执行的SQL语句
| dbHasCompleted     | 查询需要执行的SQL语句是否已经执行完毕，或者说SQL执行结果是否完成
| dbGetStatement     | 查询获取当前SQL执行结果的SQL语句
| dbColumnInfo       | 查询SQL执行结果中的字段类型
| dbFetch、fetch     | 从SQL执行结果中取出数据
| dbGetRowCount      | 查询已从SQL执行结果中取出了多少条记录
| dbBind             | 按行合并SQL执行结果与R语言中的对象
| dbClearResult      | 清除SQL执行结果
| dbBegin            | 开启一次SQL语句批处理
| dbCommit           | 提交SQL语句批处理结果
| dbRollback         | 放弃SQL语句批处理结果，即 *回滚*
| dbWithTransaction  | 执行SQL语句批处理，如果没有异常则提交，有异常则回滚
| dbBreak            | 在**dbWithTransaction**中提前退出，并回滚
| dbListConnections  | 列举某个数据库驱动建立的数据库链接数量
| dbListObjects      | 列举数据库中包含的对象（包括表格、视图等）
| dbListTables       | 列举数据库中包含的表格
| dbListFields       | 列举数据库中的某个表格包含的字段
| dbDataType         | 判断R语言中的某个对象，在数据库中应该对应的数据类型
| dbReadTable        | 读取数据库中的某个表格
| dbCreateTable      | 在数据库中创建一个表格
| dbWriteTable       | 向数据库中存入一个表格
| dbAppendTable      | 向数据库中的某个表格插入数据
| dbRemoveTable      | 删除数据库中的某个表格
| dbExistsTable      | 判断数据库中是否存在某个表格
| sqlColumnToRownames   | 将某个字段转化为行名
| sqlRownamesToColumn   | 将行名转化为单独的字段

<br>

{{< note "思考思考" "#e6e6ff" >}}
- **ODBC**可以建立连接到**Access、Excel**的数据源吗？
- 如果获取所有的数据库链接列表？
- **DBI**如何关闭所有数据库链接？

{{< /note >}}

<br>
