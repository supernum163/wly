---
title: "Hive常用系统函数梳理"
date: 2021-03-20
categories:
  - 进军大数据
tags:
  - 大数据
keywords:
  - 大数据
  - Hive
comments: true
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/09/28/uQE3hF.png
---

Hive 中的系统函数，可以帮助我们更高效的进行数据操作，本章将根据这些函数的作用进行分类梳理。

<!--more-->

<!-- toc -->

<br>

## 1、常数、常数生成函数

- `true、false`真假值常数
- `e、pi`生成自然对属底、圆周率
- `current_date`生成当前日期
- `current_timestamp`生成当前时间戳
- `current_groups`生成当前系统中的所有用户组名称构成的列表
- `current_user`生成当前系统用户名称
- `current_database`生成当前使用的数据库名称
- `current_authorizer`生成当前Hive授权者的名称
- `logged_in_user`生成当前Hive登录者的名称
- `version`生成当前Hive版本号
- `uuid`生成通用唯一识别码
- `restrict_information_schema`生成逻辑值，指示数据库架构是否启用了restrict模式

```hive
select true, e(), current_date(), uuid();
```

## 2、基础数学运算函数

- `+、-、*、/（div）、%（mod）`对两个数值、两个字段、字段与数值之间，进行加减乘除、求余运算;

```hive
# 示例，以下两个查询结果不同，前者只有一条记录，而后者中的记录数与表A的相同;
select 1 + 1;
select 1 + 1 from A;
# 示例，字段与数值相加时，相当于字段中的每个值分别与这个数值相加;
select id + 1 from A;
select id + id from A;
```

- `pmod`求正余数，`pmod(-7, 3) = 2`
- `factorial`求从1开始到n为止的连乘积，`factorial(5) = 120`

- 最大、最小值运算
  - `greatest`求多个数值中最大的一个，`greatest(1, 2, 3) = 3`
  - `least`求多个数值中最小的一个，`least(1, 2, 3) = 1`

- 正反数运算
  - `sign`求正负号，`sign(-10) = -1`
  - `abs`求绝对值，`abs(-10) = 10`
  - `positive`求数值本身，`positive(-10) = -10`
  - `negative`求相反数，`negative(10) = -10`

- 舍入运算
  - `floor`向下求整，`round(4.5) = 4`
  - `ceil（ceiling）`向上求整，`ceil(4.4) = 5`
  - `round`按特定精度（保留几位小数），求四舍五入，`round(4.5) = 5`
  - `bround`按特定精度（保留几位小数），求[^银行家舍入]，`bround(1.45, 1) = 1.4`

- 指数运算
  - `pow（power）`指数运算，`pow(2, 3) = 8, pow(8, 1/3) = 2`
  - `exp`以e为底的指数运算，`exp(1) = e()`

- 求根运算
  - `sqrt`求平方根，`sqrt(4) = 2`
  - `cbrt`求立方根，`cbrt(8) = 2`

- 对数运算
  - `log`对数运算，`log(3, 9) = 2`
  - `log2`以2为底的对数运算，`log2(8) = 3`
  - `log10`以2为底的对数运算，`log10(100) = 2`
  - `ln`以e为底的对数运算，`ln(e()) = 1`

- 三角函数运算
  - `degrees`将弧度转化为角度，`degrees(pi() / 2) = 90`
  - `radians`将角度转化为弧度，`radians(180) = pi()`
  - `sin`求正弦，`sin(pi() / 2) = 1`
  - `cos`求余弦，`cos(pi() / 2) = 0`
  - `tan`求正切，`tan(pi() / 4) = 1`
  - `asin`求反正弦，`asin(1) = pi() / 2`
  - `acos`求反余弦，`acos(0) = pi() / 2`
  - `atan`求反正切，`atan(1) = pi() / 4`

- 按位运算
  - `&、|、~、^`按位求与、或、非、异或，`3 ^ 1 = 2`
  - `shiftleft`按位左移，`shiftleft(1, 2) = 4`
  - `shiftright`按位右移，`shiftright(-4, 2) = -1`
  - `shiftrightunsigned`按位右移（无符号），`shiftrightunsigned(-4, 2) = 1073741823`

- 进制转化
  - `conv`将数值（或字符串表示的数值）从一种进制模式转化为另一种进制模式，`conv(100, 2, 10) = 4, conv(15, 10, 16) = "F"`
  - `bin`将数值转化为2进制数值，`bin(4) = 100`
  - `hex`将2进制字节、10进制数值或字符串转化为16进制字符串，`hex(10) = "A"`
  - `unhex`将16进制字符串转化为2进制字节，`decode(unhex("61"), "UTF-8") = "a"`

- 比较运算
  - `<、<=、>、>=、==（=）、!=（<>）`小于、小于等于、大于、大于等于、等于、不等于比较
  - `<=>`不等于比较，双方都为NULL值时返回true
  - `between`比较是否在两个数值之间（左右都包含），`where id between 2 and 3`
  - `in`比较是否在某个数组中，`where id in ( select explode(array(2, 3)) )`
  - `isnull、istrue、isfalse`比较是否为NULL、true、false
  - `isnotnull、isnottrue、isnotfalse`比较是否不为NULL、true、false

- 逻辑运算
  - `and、or、not、!`求与、或、非、反，`!true = false`

- 聚合函数
  - `count、min、max、avg、sum`计数、求最小值、求最大值、求平均值、求和
  - `var_pop（variance）`计算方差，`var_pop(x) = sum(pow(x, 2)) / count(x) - pow(avg(x), 2)`
  - `var_samp`计算样本方差，`var_samp(x) = var_pop(x) * count(x) / ( count(x) - 1 )`
  - `stddev_pop（std、stddev）`计算标准差，`stddev_pop(x) = sqrt(var_pop(x))`
  - `stddev_samp`计算样本标准差，`stddev_samp(x) = sqrt(var_samp(x))`
  - `covar_pop`计算两个字段之间的协方差，`covar_pop(x, y) = sum(x * y) / count(x) - avg(x) * avg(y)`
  - `covar_samp`计算两个字段之间的样本协方差，`covar_samp(x) = covar_pop(x) * count(x) / ( count(x) - 1 )`
  - `corr`计算两个字段之间的相关系数，`corr(x, y) = covar_pop(x, y) / stddev_pop(x) / stddev_pop(y)`

## 3、字符串处理函数




## 4、日期时间处理函数









[^银行家舍入]: 四舍六入五考虑，五后非零就进一，五后为零看奇偶，五前为偶应舍去，五前为奇要进一

