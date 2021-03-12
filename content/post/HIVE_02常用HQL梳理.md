---
title: "常用HiveQL梳理"
date: 2021-03-15
categories:
  - 进军大数据
tags:
  - 大数据
keywords:
  - 大数据
  - Hive
comments: true
thumbnailImagePosition: left
thumbnailImage: https://null.png
---

**HiveQL**（Hive结构化查询语句）是Hive与底层数据交互的基础，本章将介绍使用HiveQL管理数据库、表、视图、函数、分区等操作。

<!--more-->

<!-- toc -->

<br>

## 1、数据库操作相关语句

- 我们可以使用如下语句**创建数据库**，其中：
  - `DATABASE` 与 `SCHEMA` 在Hive中指的都是数据库，可以混用
  - `COMMENT` 用于添加注释
  - `LOCATION` 用于设置外部表存放位置
  - `MANAGEDLOCATION` 用于设置管理表存放位置
  - `WITH DBPROPERTIES` 用于设置数据库的其它属性

```hive
CREATE (DATABASE|SCHEMA) [IF NOT EXISTS] database_name
  [COMMENT database_comment]
  [LOCATION hdfs_path]
  [MANAGEDLOCATION hdfs_path]
  [WITH DBPROPERTIES (property_name=property_value, ...)];
```

- 我们可以使用如下语句**删除数据库**，其中：
  - `RESTRICT` 指定当数据库非空时不能删除（默认选项）
  - `CASCADE` 指定删除数据库同时删除数据库中的内容  
  
```hive
DROP (DATABASE|SCHEMA) [IF EXISTS] database_name [RESTRICT|CASCADE];
```

- 我们可以使用如下语句**修改数据库**：

```hive
# 修改数据库的属主;
ALTER (DATABASE|SCHEMA) database_name SET OWNER [USER|ROLE] user_or_role; 
# 修改外部表存放位置;
ALTER (DATABASE|SCHEMA) database_name SET LOCATION hdfs_path;
# 修改管理表存放位置，仅支持 Hive 4.0.0 及以上版本;
ALTER (DATABASE|SCHEMA) database_name SET MANAGEDLOCATION hdfs_path;
# 修改数据库的其它属性;
ALTER (DATABASE|SCHEMA) database_name SET DBPROPERTIES (property_name=property_value, ...); 
```

- 以下是其余数据库操作相关的常用语句：

```hive
# 列举所有数据库;
SHOW DATABASES;
# 查看数据库选项;
DESCRIBE DATABASE [EXTENDED] database_name;
# 切换数据库;
USE database_name;
# 查看当前数据库;
SELECT CURRENT_DATABASE();
```

## 2、表操作相关语句

- 我们可以使用如下语句**创建表**，其中：
  - `TEMPORARY` 表示创建临时表（仅作用于当前线程）
  - `EXTERNAL` 表示创建外部表（Hive中默认创建管理表）
  - `data_type` 表示字段的数据类型，可以是如下类型：
    - 二进制类型：BINARY
    - 逻辑值类型：BOOLEAN
    - 整数类型：TINYINT、SMALLINT、INT、BIGINT
    - 小数类型：DOUBLE、FLOAT、DECIMAL
    - 字符串类型：CHAR、VARCHAR、STRING
    - 日期时间类型：DATE、TIMESTAMP
    - array类型：ARRAY < data_type >
    - map类型：MAP < primitive_type, data_type >
    - struct类型：STRUCT < col_name : data_type [COMMENT col_comment], ...>
    - union类型：UNIONTYPE < data_type, data_type, ... >
  - `column_constraint_specification`用于对字段设置约束，可以进行以下设置：
    - 主键约束：PRIMARY KEY
    - 取值唯一性约束：UNIQUE
    - 非空值约束：NOT NULL
    - 默认值约束：DEFAULT [default_value]
    - 自定义取值约束：CHECK  [check_expression] 
    - 启用约束（仅对新增数据有效）：DISABLE NOVALIDATE
    - 关闭约束（可以对约束列的数据进行修改）：DISABLE NOVALIDATE
    - 是否将约束用于查询优化：RELY/NORELY 
  - `constraint_specification`用于对字段添加额外的约束，如添加主键、外键约束：
    - `PRIMARY KEY (col_name, ...) DISABLE NOVALIDATE RELY/NORELY`
    - `CONSTRAINT constraint_name FOREIGN KEY (col_name, ...) REFERENCES table_name(col_name, ...) DISABLE NOVALIDATE`
  - `PARTITIONED BY`分支语句用于设置分区字段
  - `CLUSTERED BY`分支语句用于设置分桶字段，`SORTED BY`用于设置桶内排序字段，`INTO num_buckets BUCKETS]`用于设置分桶数量
  - `SKEWED BY`分支语句应用于严重倾斜的字段，可以将其取值记录在元数据中。同时如果指定了`STORED AS DIRECTORIES`，则会根据倾斜值建立子目录
  - `ROW FORMAT`分支语句用于设置以特定的格式从文件中读取数据，
    - `STORED AS`用于设置本地文件的存储类型。如读取csv文件：
      - `ROW FORMAT DELIMITED FIELDS TERMINATED BY "," LINES TERMINATED BY "\n" STORED AS TEXTFILE`
    - `file_format`支持的文件类型有：
      - 特定格式的文件：TEXTFILE、JSONFILE、SEQUENCEFILE、RCFILE、ORC、PARQUET、AVRO
      - 自定义写入、查询格式：INPUTFORMAT input_format_classname OUTPUTFORMAT output_format_classname
    - `STORED BY` 用于设置非本地表的存储类型，如存储在**HBase**中的表。
  - `TBLPROPERTIES` 用于设置表的其它属性。如读取数据时略过第一行（标题行）:
    - `tblproperties ("skip.header.line.count" = "1")`
  - `AS`分支语句用于将查询结果插入新创建的表中
  
```hive
# 创建表;
CREATE [TEMPORARY] [EXTERNAL] TABLE [IF NOT EXISTS] [db_name.]table_name
  [(col_name data_type [column_constraint_specification] [COMMENT col_comment], ... [constraint_specification])]
  [COMMENT table_comment]
  [PARTITIONED BY (col_name data_type [COMMENT col_comment], ...)]
  [CLUSTERED BY (col_name, col_name, ...) [SORTED BY (col_name [ASC|DESC], ...)] INTO num_buckets BUCKETS]
  [SKEWED BY (col_name, col_name, ...)]
     ON ((col_value, col_value, ...), (col_value, col_value, ...), ...)
     [STORED AS DIRECTORIES]
  [
    [ROW FORMAT row_format] 
    [STORED AS file_format] | STORED BY 'storage.handler.class.name' 
    [WITH SERDEPROPERTIES (...)]
  ]
  [LOCATION hdfs_path]
  [TBLPROPERTIES (property_name=property_value, ...)]
  [AS select_statement];
 
# 根据已有的表或视图创建表结构;
CREATE [TEMPORARY] [EXTERNAL] TABLE [IF NOT EXISTS] [db_name.]table_name
  LIKE existing_table_or_view_name
  [LOCATION hdfs_path];

# 示例，创建可以从csv中读取数据的表结构；
create table test 
  ( id int, name varchar(10), class varchar(2) ) 
  comment "name：学生姓名，class：班级，year：入学年份" 
  partitioned by (year int)  
  row format delimited 
    fields terminated by "," 
    lines terminated by "\n" 
  stored as textfile 
  tblproperties ("skip.header.line.count" = "1")
;
# 示例，从本地csv文件中读入数据到分区表
load data local inpath 'student.csv' into table student 
  partition (year = 2012)
;
# 示例，从Hive表中读入数据到分区表并覆盖
set hive.exec.dynamic.partition=true ;
set hive.exec.dynamic.partition.mode=nonstrict ;
insert overwrite table student 
  partition (year = 2013)
  select id, name, class from student
;
```

- 我们可以使用如下语句**删除表**，其中：
  - `PURGE` 表示删除表时，将数据表也彻底删除（默认是放入回收站）

```hive
DROP TABLE [IF EXISTS] table_name [PURGE];
```

- 我们可以使用如下语句**清空表**，其中：
  - `PARTITION` 可以用于指定需要清空的分区，如`PARTITION (year = 2021)`
  
```hive
TRUNCATE [TABLE] table_name [PARTITION partition_spec];
```

- 我们可以使用如下语句修改建表时的设置：

```hive
# 修改表名称;
ALTER TABLE table_name RENAME TO new_table_name;

# 添加字段;
ALTER TABLE table_name [PARTITION partition_spec]
  ADD|REPLACE COLUMNS (col_name data_type [COMMENT col_comment], ...)
  [CASCADE|RESTRICT]
# 修改字段名称、数据类型、约束、注释、位置;
ALTER TABLE table_name [PARTITION partition_spec] 
  CHANGE [COLUMN] col_old_name col_new_name column_type
  [CONSTRAINT constraint_name constraints] [COMMENT col_comment] [FIRST|AFTER column_name] 
  [CASCADE|RESTRICT];
# 添加约束;
ALTER TABLE table_name ADD CONSTRAINT constraint_name constraint_specification;
# 删除约束;
ALTER TABLE table_name DROP CONSTRAINT constraint_name;

# 添加分区;
ALTER TABLE table_name ADD [IF NOT EXISTS] (PARTITION partition_spec [LOCATION 'location'], ...);
# 分区重命名;
ALTER TABLE table_name PARTITION partition_spec RENAME TO PARTITION partition_spec;
# 分区交换;
ALTER TABLE table_name_2 EXCHANGE PARTITION (partition_spec, ...) WITH TABLE table_name_1;
# 分区信息更新（修复metastore与HDFS中的分区信息不一致）;
MSCK [REPAIR] TABLE table_name [ADD/DROP/SYNC PARTITIONS];
ALTER TABLE table_name RECOVER PARTITIONS;
# 分区删除;
ALTER TABLE table_name DROP [IF EXISTS] (PARTITION partition_spec, ...) [IGNORE PROTECTION] [PURGE];  
# 分区归档/删档;
ALTER TABLE table_name ARCHIVE PARTITION partition_spec;
ALTER TABLE table_name UNARCHIVE PARTITION partition_spec;

# 修改表的分桶情况;
ALTER TABLE table_name CLUSTERED BY (col_name, col_name, ...) [SORTED BY (col_name, ...)]
  INTO num_buckets BUCKETS;
  
# 修改表的严重倾斜字段;
ALTER TABLE table_name SKEWED BY (col_name1, col_name2, ...)
  ON ([(col_name1_value, col_name2_value, ...) [, (col_name1_value, col_name2_value), ...]
ALTER TABLE table_name NOT SKEWED;
ALTER TABLE table_name NOT STORED AS DIRECTORIES;
ALTER TABLE table_name SET SKEWED LOCATION (col_name1="location1" [, col_name2="location2", ...] );
  [STORED AS DIRECTORIES];

# 修改表/分区表的数据读入格式;
ALTER TABLE table_name [PARTITION partition_spec] SET FILEFORMAT file_format;
ALTER TABLE table_name [PARTITION partition_spec] SET SERDE serde_class_name [WITH SERDEPROPERTIES serde_properties];
ALTER TABLE table_name [PARTITION partition_spec] SET SERDEPROPERTIES serde_properties;
ALTER TABLE table_name [PARTITION partition_spec] UNSET SERDEPROPERTIES (property_name, ... );

# 修改表/分区表的存储位置;
ALTER TABLE table_name [PARTITION partition_spec] SET LOCATION "new location";

# 修改表的其它属性;
ALTER TABLE table_name SET TBLPROPERTIES table_properties;
ALTER TABLE table_name SET TBLPROPERTIES ('comment' = new_comment);
```

- 以下是其余表操作相关的常用语句：

```hive
# 列举表;
SHOW TABLES;
# 查看表信息;
DESCRIBE [EXTENDED] tablename;
# 列举表分区;
SHOW PARTITIONS table_name;

# 表/分区表信息更新;
ALTER TABLE table_name TOUCH [PARTITION partition_spec];
# 表/分区表开关保护;
ALTER TABLE table_name [PARTITION partition_spec] ENABLE|DISABLE NO_DROP [CASCADE];
ALTER TABLE table_name [PARTITION partition_spec] ENABLE|DISABLE OFFLINE;
# 表/分区表压缩;
ALTER TABLE table_name [PARTITION (partition_key = 'partition_value', ...)]
  COMPACT 'compaction_type'[AND WAIT]
  [WITH OVERWRITE TBLPROPERTIES ("property"="value" , ...)];
ALTER TABLE table_name [PARTITION (partition_key = 'partition_value', ...)] CONCATENATE;
# 表/分区表字段信息更新;
ALTER TABLE table_name [PARTITION (partition_key = 'partition_value' [, ...])] UPDATE COLUMNS;  
```

## 3、视图操作相关语句

- 我们可以使用如下语句**管理普通视图**：

```hive
# 创建视图;
CREATE VIEW [IF NOT EXISTS] [db_name.]view_name [(column_name [COMMENT column_comment], ...) ]
  [COMMENT view_comment]
  [TBLPROPERTIES (property_name = property_value, ...)]
  AS select_statement;
# 删除视图;
DROP VIEW [IF EXISTS] [db_name.]view_name;
# 修改视图属性;
ALTER VIEW [db_name.]view_name SET TBLPROPERTIES table_properties;
# 创建视图对应的查询语句;
ALTER VIEW [db_name.]view_name AS select_statement;
```

- 我们可以使用如下语句**管理物化视图**（物化视图在普通视图的基础上进行预运算，并能使用自动存储程序保存运算结果，可以有效的加速查询操作）：

```hive
# 创建物化视图;
CREATE MATERIALIZED VIEW [IF NOT EXISTS] [db_name.]materialized_view_name
  [DISABLE REWRITE]
  [COMMENT materialized_view_comment]
  [PARTITIONED ON (col_name, ...)]
  [CLUSTERED ON (col_name, ...) | DISTRIBUTED ON (col_name, ...) SORTED ON (col_name, ...)]
  [
    [ROW FORMAT row_format]
    [STORED AS file_format] | STORED BY 'storage.handler.class.name' 
    [WITH SERDEPROPERTIES (...)]
  ]
  [LOCATION hdfs_path]
  [TBLPROPERTIES (property_name=property_value, ...)]
  AS select_statement;
# 删除物化视图;
DROP MATERIALIZED VIEW [db_name.]materialized_view_name;
# 开启、关闭物化视图的自动重写功能;
ALTER MATERIALIZED VIEW [db_name.]materialized_view_name ENABLE|DISABLE REWRITE;
```

## 4、自定义宏、函数操作相关语句

- 我们可以使用如下语句**管理自定义宏**：

```hive
# 创建临时宏;
CREATE TEMPORARY MACRO macro_name([col_name col_type, ...]) expression;
# 删除临时宏;
DROP TEMPORARY MACRO [IF EXISTS] macro_name;
```

- 我们可以使用如下语句**管理自定义函数**，其中`class_name`即由Java实现的类方法名称：

```hive
# 创建临时函数;
CREATE TEMPORARY FUNCTION function_name AS class_name;
# 删除临时函数;
DROP TEMPORARY FUNCTION [IF EXISTS] function_name;
# 创建函数;
CREATE FUNCTION [db_name.]function_name AS class_name
  [USING (JAR|FILE|ARCHIVE 'file_uri', ...)];
# 删除函数;
DROP FUNCTION [IF EXISTS] function_name;
# 重新加载函数
RELOAD (FUNCTIONS|FUNCTION);
```

## 5、show相关语句

```hive
# 列举数据库;
SHOW (DATABASES|SCHEMAS) [LIKE 'identifier_with_wildcards'];
# 列举表;
SHOW TABLES [IN database_name] ['identifier_with_wildcards'];
# 列举视图;
SHOW VIEWS [IN/FROM database_name] [LIKE 'pattern_with_wildcards'];
# 列举物化视图;
SHOW MATERIALIZED VIEWS [IN/FROM database_name] [LIKE 'pattern_with_wildcards’];
# 列举表分区;
SHOW PARTITIONS [db_name.]table_name [PARTITION(partition_spec)] 
  [WHERE where_condition] [ORDER BY col_list] [LIMIT rows]; 
# 列举表的详细信息;
SHOW TABLE EXTENDED [IN|FROM database_name] LIKE 'identifier_with_wildcards' [PARTITION(partition_spec)];
# 列举创表时的详细信息;
SHOW CREATE TABLE ([db_name.]table_name|view_name);
# 列举表的属性信息;
SHOW TBLPROPERTIES tblname;
# 列举表的某一项属性信息;
SHOW TBLPROPERTIES tblname("foo");
# 列举表字段;
SHOW COLUMNS (FROM|IN) table_name [(FROM|IN) db_name] [ LIKE 'pattern_with_wildcards'];
# 列举函数;
SHOW FUNCTIONS [LIKE "<pattern>"];
# 列举表锁;
SHOW LOCKS <table_name> [PARTITION (<partition_spec>)] [EXTENDED];
# 列举数据库锁;
SHOW LOCKS (DATABASE|SCHEMA) database_name;
# 查看参数配置值;
SHOW CONF <configuration_name>;
# 列举Hive事务;
SHOW TRANSACTIONS;
# 列举Hive合并信息;
SHOW COMPACTIONS;
```

## 6、describe相关语句

```hive
# 查看数据库的各项信息;
DESCRIBE (DATABASES|SCHEMAS) [EXTENDED] db_name;
# 查看表、视图、分区、字段的各项信息;
DESCRIBE [EXTENDED | FORMATTED]
  [db_name.]table_name [PARTITION partition_spec] [col_name ( [.field_name] | [.'$elem$'] | [.'$key$'] | [.'$value$'] )* ];
# 查看函数的各项信息;
DESCRIBE FUNCTION [EXTENDED] function_name;
```

## 7、终止Hive事务

```hive
ABORT TRANSACTIONS transactionID [ transactionID ...];
```

---
参考：

[HiveQL](https://cwiki.apache.org/confluence/display/Hive/LanguageManual)
[Hive参数配置](https://cwiki.apache.org/confluence/display/Hive/Configuration+Properties)




