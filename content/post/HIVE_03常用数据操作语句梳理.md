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
create temporary table student1 (
    id int, name varchar(10), birthday date, 
    class array<string>, score map<string, int>,
    addr struct<street:string, No:int>,
    contact uniontype<bigint, string>
  ) 
  partitioned by (grade int)
  stored as orc TBLPROPERTIES ("transactional"="true")
;
create temporary table student2 like student1;
alter table student2 set tblproperties ("transactional"="true");
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
  VALUES values_row, values_row, ...;
  
# 示例，取消略过第一条记录的设置;
alter table student set tblproperties ("skip.header.line.count" = "0");
# 示例，直接向Hive表中插入记录;
insert into table student partition(grade=2018)
  values (
    4, "赵六", "1997-07-08",
    array("英语","物理"),
    map("英语",90,"物理",NULL),
    named_struct("street", "广林路","no", 37),
    create_union(1, cast(NULL as bigint), "8808-3124")
  )
;
```

## 2、更新、删除、合并数据

- 我们可以使用以下语句更新、删除、合并数据。注意要执行这些操作，必须首先开启事务性，并保证存储数据的表本身支持事务性操作。

```hive
# 更新数据;
UPDATE tablename SET (column = value, ...) [WHERE expression];
# 删除数据;
DELETE FROM tablename [WHERE expression];
# 合并数据;
MERGE INTO <target table> AS T USING <source expression/table> AS S
ON <boolean expression1>
WHEN MATCHED [AND <boolean expression2>] THEN UPDATE SET <set clause list>
WHEN MATCHED [AND <boolean expression3>] THEN DELETE
WHEN NOT MATCHED [AND <boolean expression4>] THEN INSERT VALUES<value list>;

# 示例，更新数据;
update student1 set birthday = "1997-01-01" where id = 3;
# 示例，删除数据;
delete from student1 where id > 3;
# 示例，合并数据;
merge into student1 as T using student2 as S
on T.id = S.id
when matched and T.birthday = S.birthday then delete
when matched and T.birthday != S.birthday then update set birthday = S.birthday
when not matched then insert values(S.id,S.name,S.birthday,S.class,S.score,S.addr,S.contact,S.grade)
;
```

## 3、查询数据

- 我们可以使用以下语句查询数据，其中：
  - `DISTRIBUTE BY` 多用于分桶，当然我们首先需要设置分桶数量
  - `ORDER BY` 与 `SORT BY` 都可以进行排序，但前者给出整体排序的结果，而后者多用于分桶排序
  - `CLUSTER BY` 相当于 `DISTRIBUTE BY ... SORT BY ...` 的快捷语句，后者还可以使用不同的字段进行分桶与分桶排序

```hive
[WITH (CommonTableExpression, ...)]
SELECT [ALL | DISTINCT] (select_expr, ...)
  FROM table_reference
  [WHERE where_condition]
  [GROUP BY col_list HAVING having_condition]
  [ORDER BY col_list]
  [CLUSTER BY col_list | [DISTRIBUTE BY col_list] [SORT BY col_list]]
  [LIMIT [offset_rows,] limit_rows] | [LIMIT rows [offset rows]]

# 示例，查询各种类型的数据;
select name, class[0], score["语文"], addr.street, extract_union(contact).tag_0 from student;
# 示例，使用正则表达式选择字段;
set hive.support.quoted.identifiers = none;
select name, `(gr|bir).+` from student;
# 示例，使用distinct去重;
select distinct name, v.class from student t lateral view explode(class) v as class;
# 示例，使用having子句;
select addr.street, max(birthday) from student 
  group by addr.street having max(birthday) < '1998-01-01' 
  order by addr.street;
# 示例，使用分桶排序;
set mapreduce.job.reduces=3;
select name, birthday, grade from student 
  distribute by grade sort by grade asc, birthday desc;
# 示例，使用limit子句;
select * from student limit 1 offset 2;
```

## 4、JOIN 语句

- Hive中有六种连表方式，其中：
  - **inner join**（内连接），根据连接条件选择两个表中都有的数据
  - **full join**（全连接），选择两个表的全部数据，并根据连接条件匹配在一起（匹配不到则为NULL）
  - **left join**（左连接），选择左表全部数据，并根据连接条件选择右表中的数据（匹配不到则为NULL）
  - **right join**（右连接），选择右表全部数据，并根据连接条件选择左表中的数据（匹配不到则为NULL）
  - **left semi join**（半连接），根据连接条件选择左表中的数据，可以改写为`where ... in ...`或`where ... exists ...`语句
  - **cross join**（交叉连接），一般不指定连接条件，为左表中的每一条数据匹配右表全部的数据（反之亦然）
  
```hive
SELECT select_expression
FROM ((table|query), ...)
[WHERE join_condition]

join_table:
    table_reference [INNER] JOIN table_factor [join_condition]
  | table_reference {LEFT|RIGHT|FULL} [OUTER] JOIN table_reference join_condition
  | table_reference LEFT SEMI JOIN table_reference join_condition
  | table_reference CROSS JOIN table_reference [join_condition]
table_reference:
    table_factor
  | join_table
table_factor:
    tbl_name [alias]
  | table_subquery alias
  | ( table_references )
join_condition:
    ON expression  
  
# 示例，创建测试表;
create temporary table A (id int, name char(2));
create temporary table B like A;
insert into table A values (1, "a"), (2, "a"), (3, "c");
insert into table B values (1, "a"), (4, "d");
# 示例，在where子句中指定连表方式;
select A.id, A.name, B.name from A, B where A.id = B.id;
# 示例，内连接不指定连接条件时相当于交叉连接;
select * from A join B
# 示例，交叉连接在指定连接方式的情况下相当于内连接;
select * from A cross join B on A.id = B.id;
# 示例，可以用 where 语句改写半连接;
select * from A left semi join B on A.id = B.id;
select * from A where id in (select id from B);
select * from A where exists (select id from B where A.id = B.id);
# 示例，全连接时合并左右表中用于连接的字段;
select if(A.id is not NULL, A.id, B.id) as id, A.name, B.name from A full join B on A.id = B.id;
# 示例，连接有先后顺序，A直接左连接C，与A先内连接B再左连接C，产生的结果不同;
select * from A left join B on A.id = B.id;
select * from A join B on A.id = B.id left join B on A.id = B.id;
# 示例，左右全连接时，连接条件写在on子句与where子句中，产生的结果不同;
select * from A left join B on A.id = B.id;
select * from A left join B where A.id = B.id;
```

## 5、UNION 语句

- 我们可以使用`union`语句将两个查询结果合并起来，注意两个查询结果必须字段数量相同且字段类型相似。其中：
  - `union all`直接将查询结果合并，而直接使用`union`在合并时会去除重复的记录
  - 合并语句之后可以使用`order by`子句，对合并结果排序
  - Hive中合并语句时存在自动重命名字段和自动类型转换机制，自动类型转换只发生在数据类型相似的情况（如同属于数值型）
  
```hive
select_statement (UNION [ALL | DISTINCT] select_statement ...) [ORDER BY col_list]

# 示例，合并时会去除重复值、并对合并结果排序;
select * from A
union
select * from B
order by id;
# 示例，自动重命名字段、自动类型转换;
select * from B
union all
select 5, string("e");
```

## 6、LATERAL VIEW 语句

- `LATERAL VIEW` 常与表生成函数（如`explore`）一起使用，将原表中每条记录，与根据该记录生成的表交叉关联，最终生成包含两方数据的虚拟表。

```hive
lateralView: LATERAL VIEW udtf(expression) tableAlias AS (columnAlias, ...)
fromClause: FROM baseTable (lateralView ...)

# 示例，解析array、map类型的字段;
select name, B.col from student A 
  lateral view explode(class) B;
select name, B.* from student A 
  lateral view explode(score) B as class, score;
# 示例，可以嵌套使用 lateral view ;
select B.key, C.* from (
    select map("王五", map("英语",100,"物理",NULL), "赵六", map("英语",90,"物理",NULL)) as col
  ) A
  lateral view explode(A.col) B 
  lateral view explode(B.value) C as class, score;
# 示例，lateral view outer 可以进行全关联;
select name, B.class from student t 
  lateral view explode(class) B as class 
  lateral view outer explode(array()) C ;
```

## 7、TABLESAMPLE 语句

- 我们可以在where子句之后使用`TABLESAMPLE`子句对表进行抽样，抽样是根据分桶进行的，先将表分成y份，再从中取出第x份数据。我们可以随机分区（如使用随机函数`rand`），也可以使用非分区字段作为分桶依据。注意分桶不一定将数据严格的分成y等份。

```hive
table_sample: TABLESAMPLE (BUCKET x OUT OF y [ON colname])

# 示例，对表进行抽样;
select * from student tablesample (bucket 1 out of 2 on rand());
select * from student tablesample (bucket 1 out of 2 on name);
```

## 8、开窗&分析语句

- 开窗函数和分析函数，用于对窗口内的数据应用分析函数，并为每条记录匹配相应的结果。注意开窗函数中：
  - `PARTITION BY`表示进行分组开窗
  - `ORDER BY`表示进行组内排序
  - `range`则表示开窗范围，如根据当前行计算的（同一分组的）前m行到后n行

```hive
analytic_fun() OVER( [PARTITION BY cols] [ORDER BY cols] range )
range:
  (ROWS | RANGE) BETWEEN (CURRENT ROW | (UNBOUNDED | num) PRECEDING) AND (CURRENT ROW | (UNBOUNDED | num) FOLLOWING)
  | (ROWS | RANGE) BETWEEN (UNBOUNDED | num) PRECEDING AND num PRECEDING
  | (ROWS | RANGE) BETWEEN num FOLLOWING AND (UNBOUNDED | num) FOLLOWING

# 示例，使用 PARTITION BY ... ORDER BY ... 分组求行号;
select row_number() over(partition by name order by id), * from A;
# 示例，使用多个分析函数时，可以将开窗函数单独提取出来;
select name, avg(id) over w, sum(id) over w from A
  window w as (partition by name order by id range unbounded preceding);
# 示例，使用 BETWEEN ... AND ... 决定开窗范围。注意开窗范围大于1条记录时，需要使用聚合函数作为分析函数;
select count(distinct name) over(partition by name order by id ROWS BETWEEN 1 PRECEDING AND 1 FOLLOWING), * from A;
# 示例，开窗函数中使用聚合函数;
select row_number() over(order by count(distinct id)), name from A group by name;
```

## 9、GROUPING SETS 语句

- 我们可以在`group by`子句之后指定`grouping sets`，指定多个分组选项，相当于将每个分组选项处理的结果合并在一起。类似的，HIve中还有两个快捷语句，其中：
  - `WITH CUBE`表示根据分组字段的全排列组合形成分组选项
  - `WITH ROLLUP`表示根据分组字段的先后顺序，继承性的排列组合形成分组选项。即对于`group by`子句中的前后两个字段，包含后者的分组选项中，必须包含前者

```hive
# 示例，使用 union all 改写 grouping sets;
select id, name, count(*), GROUPING__ID from A group by id, name 
  grouping sets ( (id, name), id, name, ( ) );
select id, name, count(*), 0 from A group by id, name 
  union all select id, NULL, count(*), 1 from A group by id 
  union all select NULL, name, count(*), 2 from A group by name 
  union all select NULL, NULL, count(*), 3 from A;
# 示例，使用 grouping sets 改写 WITH CUBE;
select id, name, grade, count(*) from student group by id, name, grade WITH CUBE;
select id, name, grade, count(*) from student group by id, name, grade
  GROUPING SETS ( (id, name, grade), (id, name), (name, grade), (id, grade), (id), (name), (grade), ( ));
# 示例，使用 grouping sets 改写 WITH ROLLUP;
select id, name, grade, count(*) from student group by id, name, grade WITH ROLLUP;
select id, name, grade, count(*) from student group by id, name, grade
  GROUPING SETS ( (id, name, grade), (id, name), (id), ( ));
```

## 10、虚拟字段

- 我们可以在查询语句中使用以下虚拟字段，其具体含义如下：

| 虚拟字段                      | 作用                              
|:------------------------------|:----------------------------------
| INPUT__FILE__NAME             | 显示记录所在文件名
| BLOCK__OFFSET__INSIDE__FILE   | 显示当前块在文件中的偏移量（字节）
| ROW__OFFSET__INSIDE__BLOCK    | 显示当前记录在块中的偏移量（需要设置`set hive.exec.rowoffset=true`）
| RAW__DATA__SIZE               | 显示原始数据集的大小
| ROW__ID                       | 显示行标识（写入位置，分桶ID等）
| GROUPING__ID                  | 显示`GROUPING SETS`等子句中指定的第几个分组选项

---
参考：
[Hive DML](https://cwiki.apache.org/confluence/display/Hive/LanguageManual+DML)


