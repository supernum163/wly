---
title: "Hive常用数据操作语句梳理"
date: 2021-03-18
categories:
  - 进军大数据
tags:
  - 大数据
keywords:
  - 大数据
  - Hive
  - DML
comments: true
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/09/28/uQE3hF.png
---

Hive **DML**（数据操作语句）是Hive底层与数据交互的基础，本章将介绍使用HiveQL进行增删改查等操作。

<!--more-->

<!-- toc -->

<br>

## 1、插入数据

- 我们可以通过`LOAD DATA ...`语句从文件中读取数据插入到Hive表中，其中：
  - `LOCAL`表示从本地文件系统中寻找文件，缺省时会从HDFS文件系统中寻找
  - `OVERWRITE`表示用覆盖表中的数据，设定了分区时只会覆盖分区表中的数据

之前的文章中我们已经介绍了通过设置`row format delimited ...`的方式读取csv文件，本文我们将尝试使用`row format serde ...`（**serde**: serialize and deserialize）的方式读取csv文件。假设我们有一份使用utf8编码存储的<student.csv>数据表，表中的数据如下：

| id | name | birthday   | class          | score                      | addr       | contact       | grade |
|:---|:-----|:-----------|:---------------|:---------------------------|:-----------|:--------------|:------|
| 1  | 张三 | 1998-01-23 | 语文;数学;英语 | 语文:60;数学:70;英语:80    | 老街路;87  | 0;13137218094 | 2017  |
| 2  | 李四 | 1997-11-17 | 语文;数学;物理 | 语文:90;数学:100;物理:NULL | 老街路;113 | 0;13153548707 | 2017  |
| 3  | 王五 | 1997-03-05 | 英语;物理      | 英语:100;物理:NULL         | 广林路;35  | 1;8808-3122   | 2017  |

```hive
LOAD DATA [LOCAL] INPATH "filepath" [OVERWRITE] INTO TABLE tablename 
  [PARTITION (partcol1=val1, partcol2=val2 ...)] 
  [INPUTFORMAT "inputformat" SERDE "serde"]
  
# 如果存在则删除student表;
drop table if exists student;
# 创建student表;
create table student (
    id int, name varchar(10), birthday date, 
    class array<string>, score map<string, int>,
    addr struct<street:string, No:int>,
    contact uniontype<bigint, string>
  ) 
  comment "学生信息记录表" 
  partitioned by (grade int)
  row format serde "org.apache.hadoop.hive.serde2.lazy.LazySimpleSerDe"
  with serdeproperties(
    "field.delim"=",",
    "collection.delim"=";",
    "mapkey.delim"=":",
    "lines.delim"="\n",
    "null.defined"="NULL",
    "serialization.encoding"="utf8"
  )
  stored as textfile
  tblproperties ("skip.header.line.count" = "1")
;
# 读取csv文件中的数据插入student表;
load data local inpath "student.csv" overwrite into table student 
  partition (grade = 2017)
;
```

- 我们可以通过以下语句，将查询结果插入Hive表，其中：
  - `INSERT OVERWRITE`表示覆盖原有数据，向分区表插入数据时可以指定`IF NOT EXISTS`，表示分区不存在时则覆盖（自动创建分区）
  - 使用动态决定分区的语句时，必须设置允许动态分区，或将动态分区设为非严格模式。
  
```hive
# 插入数据;
INSERT OVERWRITE TABLE tablename1 [PARTITION (partcol1=val1, ...) [IF NOT EXISTS]] select_statement1 FROM from_statement;
INSERT INTO TABLE tablename1 [PARTITION (partcol1=val1, ...)] select_statement1 FROM from_statement;
# 批量插入数据;
FROM from_statement
INSERT OVERWRITE TABLE tablename1 [PARTITION (partcol1=val1, ...) [IF NOT EXISTS]] select_statement1
[INSERT OVERWRITE TABLE tablename2 [PARTITION ... [IF NOT EXISTS]] select_statement2]
[INSERT INTO TABLE tablename2 [PARTITION ...] select_statement2] ...;
FROM from_statement
INSERT INTO TABLE tablename1 [PARTITION (partcol1=val1, ...)] select_statement1
[INSERT INTO TABLE tablename2 [PARTITION ...] select_statement2]
[INSERT OVERWRITE TABLE tablename2 [PARTITION ... [IF NOT EXISTS]] select_statement2] ...;
# 插入数据时动态决定分区;
INSERT OVERWRITE TABLE tablename PARTITION (partcol1[=val1], ...) select_statement FROM from_statement;
INSERT INTO TABLE tablename PARTITION (partcol1[=val1], ...) select_statement FROM from_statement;

# 示例，创建临时表;
create table student1 like student;
create table student2 like student;
# 示例，插入数据;
insert overwrite table student1 partition(grade=2018) 
  select id,name,birthday,class,score,addr,contact from student where id = 3;
# 示例，批量插入;
from student
insert into table student1 partition(grade=2018) 
  select id,name,birthday,class,score,addr,contact where id = 1
insert into table student2 partition(grade=2018) 
  select id,name,birthday,class,score,addr,contact where id = 2;
# 示例，动态决定分区;
set hive.exec.dynamic.partition=true;
set hive.exec.dynamic.partition.mode=nonstrict;
insert into table student2 partition(grade)
  select * from student where id = 3;  
```

- 我们可以使用以下语句将查询结果插入至文件系统:

```
# 将查询结果插入至文件系统;
INSERT OVERWRITE [LOCAL] DIRECTORY directory1
  [ROW FORMAT row_format] [STORED AS file_format]
  select_statement FROM from_statement;
# 批量插入;
FROM from_statement
INSERT OVERWRITE [LOCAL] DIRECTORY directory1 select_statement1
[INSERT OVERWRITE [LOCAL] DIRECTORY directory2 select_statement2] ...

# 示例，将查询结果插入至文件系统;
insert overwrite local directory "student"
  row format delimited 
    fields terminated by "," escaped by "\\"
    collection items terminated by ";"
    map keys terminated by ":"
    lines terminated by "\n"
    null defined as "NULL"
  stored as textfile 
  select * from student
;
```

- 我们还可以通过以下语句，直接向Hive表中插入记录。向student表中插入数据时需要注意，因为我们在创表时设置了`skip.header.line.count`将文件首行最为标题行跳过，所以插入数据之前必须取消这一设置，否则插入事务可以正常执行，但查询时会忽略插入的第一条记录。

```hive
INSERT INTO TABLE tablename [PARTITION (partcol1[=val1], ...)]
  VALUES values_row, ...;
  
# 示例，取消略过第一条记录的设置;
alter table student set tblproperties ("skip.header.line.count" = "0");
# 示例，直接向Hive表中插入记录;
insert into table student partition(grade=2018)
  values (
    3, "王五", "1997-03-05",
    array("英语","物理"),
    map("英语",100,"物理",NULL),
    named_struct("street", "广林路","no", 36),
    create_union(1, cast(NULL as bigint), "8808-3122")
  )
;
```


---
参考：
[Hive DML](https://cwiki.apache.org/confluence/display/Hive/LanguageManual+DML)




