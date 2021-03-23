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

## 2、空值处理函数

  - `nvl`如果是空值则用特定的值替换，`nvl(NULL, 1) = 1`
  - `nullif`如果等于特定的值则替换为空值，`nullif(1, 1) = NULL`
  - `coalesce`返回多个参数中的第一个非空值，`coalesce(NULL, 1, 2) = 1`
  
## 3、逻辑运算函数

  - `and、or、not、!`求与、或、非、反，`!true = false`
  - `<、<=、>、>=、==（=）、!=（<>）`小于、小于等于、大于、大于等于、等于、不等于比较
  - `<=>`不等于比较，双方都为NULL值时返回true
  - `between`比较是否在两个数值之间（左右都包含），`where id between 2 and 3`
  - `in`比较是否在某个数组中，`where id in ( select explode(array(2, 3)) )`
  - `isnull、istrue、isfalse`比较是否为NULL、true、false
  - `isnotnull、isnottrue、isnotfalse`比较是否不为NULL、true、false  

## 4、基础数学运算函数

- `+、-、*、/（div）、%（mod）`对两个数值、两个字段、字段与数值之间，进行加减乘除、求余运算;

```hive
create temporary table A (id int);
insert into A values (1), (2), (2), (3), (4);

# 以下两个查询结果不同，前者只有一条记录，而后者中的记录数与表A的相同;
select 1 + 1;
select 1 + 1 from A;
# 字段与数值相加时，相当于字段中的每个值分别与这个数值相加;
select id + 1 from A;
# 两个数值型字段可以直接相加;
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
  - `bround`按特定精度（保留几位小数），求银行家舍入[^1]，`bround(1.45, 1) = 1.4`

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
  - `unhex`将16进制数值或字符串转化为2进制字节，`unhex(61) = binary("a")`

- 聚合函数
  - `count、min、max、avg、sum`计数、求最小值、求最大值、求平均值、求和
  - `percentile`计算序列的n分位数
  - `percentile_approx`为数值非常多的序列计算近似n分位数
  - `var_pop（variance）`计算方差，`var_pop(x) = sum(pow(x, 2)) / count(x) - pow(avg(x), 2)`
  - `var_samp`计算样本方差，`var_samp(x) = var_pop(x) * count(x) / ( count(x) - 1 )`
  - `stddev_pop（std、stddev）`计算标准差，`stddev_pop(x) = sqrt(var_pop(x))`
  - `stddev_samp`计算样本标准差，`stddev_samp(x) = sqrt(var_samp(x))`
  - `covar_pop`计算两个字段之间的协方差，`covar_pop(x, y) = sum(x * y) / count(x) - avg(x) * avg(y)`
  - `covar_samp`计算两个字段之间的样本协方差，`covar_samp(x) = covar_pop(x) * count(x) / ( count(x) - 1 )`
  - `corr`计算两个字段之间的相关系数，`corr(x, y) = covar_pop(x, y) / stddev_pop(x) / stddev_pop(y)`

- 线性回归相关聚合函数
  - `regr_count`将两个变量的取值一一对应，计算总共有多少对（如果一对取值中任意一个为空值，则忽略）
  - `regr_avgy`计算参数对中第一个参数的平均值
  - `regr_avgx`计算参数对中第二个参数的平均值
  - `regr_slope`计算参数对线性回归时的斜率，相当于`N*sum(x*y)-sum(x)*sum(y)) / (N*sum(x*x)-sum(x)*sum(x)`
  - `regr_intercept`计算参数对线性回归时的截距，相当于`sum(y)*sum(x*x)-sum(X)*sum(x*y) )  /  ( N*sum(x*x)-sum(x)*sum(x)`
  - `regr_sxx`用于计算regr_r2，相当于`sum(x*x)-sum(x)*sum(x)/N`
  - `regr_syy`用于计算regr_r2，相当于`sum(y*y)-sum(y)*sum(y)/N`
  - `regr_sxy`用于计算regr_r2，相当于`sum(x*y)-sum(x)*sum(y)/N`
  - `regr_r2`计算R2系数，用于评估线性回归拟合优度，相当于`power(regr_sxy(y, x), 2)  / regr_sxx(y, x) / regr_syy(y, x) `

## 5、字符串处理函数

- 字符串生成
  - `space`生成n个空格，`space(2) = "  "`
  - `repeat`生成n个指定字符/字符串，`repeat("a", 2) = "aa"`
  - `printf`按照C语言printf函数的模式生成字符串，`printf("%s: %d%%", "比率", 87) = "比率: 87%"`

- 字符串转化
  - `ascii`求字符对应的Ascii码，`ascii("a") = 97`
  - `chr`求Ascii码对应的字符，`chr(97) = "a"`
  - `binary`将字符转化为字节，`binary("abc") = hex("969798")`
  - `encode`将字符串按照特定的编码方式转化为字节，`encode("a", "ascii") = binary("a")`
  - `decode`将字节按照特定的编码方式转化为字符串，`decode(unhex("61"), "ascii") = "a"`
  
- 字符串长度计算
  - `length（char_length、character_length）`计算字符串长度，`length("abc 中文") = 6`
  - `octet_length`计算字符串长度（字节），`octet_length("abc 中文") = 10`

- 字符串转换
  - `lower（lcase）`将大写英文字符转化为小写，`lower("ABC") = "abc"`
  - `upper（ucase）`将小写英文字符转化为大写，`upper("abc") = "ABC"`
  - `initcap`将英文字符首字母大写，`initcap("abc def") = "Abc Def"`
  - `reverse`将字符串反转，`reverse("abc 中文") = "文中 cba"`
  
- 字符串补齐、替换前后空格
  - `lpad`将字符串长度调整为n，不足时在左侧添加指定字符串，超出时截取前n个字符，`lpad("abc", 5, " ") = "  abc"`
  - `rpad`将字符串长度调整为n，不足时在右侧添加指定字符串，超出时截取前n个字符，`rpad("abc", 5, " ") = "abc  "`
  - `trim`将字符串左右的空格删除，`trim("  abc  ") = "abc"`
  - `ltrim`将字符串左侧的空格删除，`ltrim("  abc  ") = "abc  "`
  - `rtrim`将字符串右侧的空格删除，`rtrim("  abc  ") = "  abc"`

- 字符串替换
  - `replace`将字符串中包含的某个子字符串替换为另一个字符串，`replace("abc", "b", " ") = "a c"`
  - `translate`将字符串中的某些字符逐一替换为对应的字符，`translate("abc", "ac", "13") = "1b3"`
  - `mask`将某个字符串的各个部分，如（A-Z、a-z、0-9、其它字符、数值、日、月、年）替换为指定字符，-1表示保留原字符，`mask("2021.03.04", -1,-1, -1,"-") = "2021-03-04"`
  - `mask_first_n`将某个字符串前n个字符中的各个部分，替换为指定字符
  - `mask_last_n`将某个字符串后n个字符中的各个部分，替换为指定字符
  - `mask_show_first_n`将某个字符串前n个字符除外的各个部分，替换为指定字符
  - `mask_show_last_n`将某个字符串后n个字符除外的各个部分，替换为指定字符
  
- 字符串截取
  - `substr（substring）`字符串截取，从某个位置开始，截取n个字符，`substr("abc 中文", 3, 4) = "c 中文"`
  - `substring_index`字符串截取，从第一个字符开始，截取到某个字符第n次出现的位置，`substring_index("a,b,c", ",", 2) = "a,b"`

- 字符串分割、拼接
  - `split`将字符串按某种模式切分为字符串数组，`split("ab ab  ab", " +") = array("ab","ab","ab")`
  - `concat`将多个字符串拼接为一个字符串，`concat("a", "b", "c") = "abc"`
  - `concat_ws`使用特定分隔符，将多个字符串或字符串数组拼接为一个字符串，`concat_ws(" ", array("a", "b"), "c") = "a b c"`
  
- 字符串查找
  - `locate`返回某个字符串在另一个字符串中的位置（可以从指定位置开始查找），`locate("b", "abcbc", 3) = 4`
  - `instr`返回某个字符串中另一个字符串首次出现的位置，`instr("abc", "b") = 2`
  - `field`返回某个字符串在之后的字符串参数（构成的列表）中的位置，`field("b", "a", "b", "c") = 2`
  - `elt`返回第n个字符串，`elt(2, "a", "b", "c") = "b"`

- 字符串相似性计算
  - `like`检查字符串是否符合某种模式
  ```hive
  # 返回true，"abc"能匹配模式"%b%" ;
  select "abc" like "%b%";
  # 返回false，"abc"不能匹配模式"%d%" ;
  select "abc" like all ("%b%", "%d%");
  # 返回true，"abc"只要匹配一种模式就为真 ;
  select "abc" like any ("%b%", "%d%");
  ```
  - `levenshtein`计算两个字符串的编辑距离（由一个字符串转化为另一个所需的最少**替换/插入/删除**次数），`levenshtein("kitten", "sitting") = 3`

- 正则表达式运算
  - `rlike（regexp）`检查字符串是否符合某种模式（正则表达式），`"abc" rlike "(b|d)+" = true`
  - `regexp_extract`将某个字符串中，正则表达式匹配到的，（全部或第几个子模式匹配到的内容）提取出来，`regexp_extract("a-b", "(\\w+).(\\w+)", 1) = "a"`
  - `regexp_replace`将某个字符串中，正则表达式匹配到的，替换为指定的字符串，`regexp_replace("a-1", "(\\w+)-", "A.") = "A.1"`

- 分词与词频统计
  - `sentences`将字符串按照句子及单词进行二级分割生成数组
  - `ngrams`计算字符串数组（或由字符串数组组成的数组）中，n个字符串同时出现频率最高的前k个组合
  - `context_ngrams`根据词频统计结果自动补全语句，给出跟在需要补全语句之后的，前k个最有可能的组合

  ```hive
  # 分词，结果是 [ ["Hello", "there"], ["I", "am", "a", "UDF"] ] ;
  select sentences("Hello there! I am a UDF.");
  
  # 词频统计，单个单词出现次数最多的前两名;
  # 结果是 [{"ngram":["are"],"estfrequency":2.0},{"ngram":["you"],"estfrequency":2.0}] ;
  select ngrams( array( array("How", "are", "you"), array("Where", "are", "you") ), 1, 2) ;
  
  # 词频统计，两个单词一起出现次数最多的组合;
  # 结果是 [{"ngram":["are","you"],"estfrequency":2.0}];
  select ngrams( array( array("How", "are", "you"), array("Where", "are", "you") ), 2, 1) ;
  
  # 自动补全语句，需要补全的语句必须以字符串数组的形式给出，其中NULL值表示必须填补的空词;
  # 结果是 [{"ngram":["you","do"],"estfrequency":1.0}] ;
  select context_ngrams(
    sentences(lower("How are you! How do you do.")), 
    array("how", "do", null, null), 2
  );
  ```

- 特征值计算
  - `hash`计算哈希值（散列值），`hash(123, "abc", true) = 3105178`
  - `murmur_hash`计算Murmur哈希值（非加密散列值），`murmur_hash(123, "abc", true) = -1738619680`
  - `mask_hash`计算字符串哈希值，`mask_hash("abc") = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"`
  - `base64`将字节转化为base64表示的字符串，`base64(binary("abc 中文")) = "YWJjIOS4reaWhw=="`
  - `unbase64`将base64表示的字符串转化为字节，`unbase64("YWJjIOS4reaWhw==") = binary("abc 中文")`
  - `aes_encrypt`将原文按照特定密匙进行**aes加密**，`base64(aes_encrypt('abc', '1234567890123456')) = "Iig1Q00eW0x+EAlVOUTDNw=="`
  - `aes_decrypt`将密文按照特定密匙进行**aes解密**，`aes_decrypt(unbase64("Iig1Q00eW0x+EAlVOUTDNw=="), "1234567890123456") = "abc"`
  - `soundex`计算**soundex code**（用于按英文发音索引姓名），`soundex("Miller") = "M460"`
  - `crc32`计算**CRC码**（循环冗余信息码），`crc32("abc") = 891568578`
  - `md5`计算**md5**，`md5("abc") = "900150983cd24fb0d6963f7d28e17f72"`
  - `sha（sha1）`计算**sha**，`sha("abc") = "a9993e364706816aba3e25717850c26c9cd0d89d"`
  - `sha2`计算**sha2**，可以选择输出多少个字节长度的结果，`sha2("abc", 256) = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"`
  
## 6、日期时间处理函数

- 日期时间转化
  - `from_unixtime`将时间戳（距**1970-01-01**过去了多少秒）转化为日期时间，`from_unixtime(1612310400) = "2021-02-03 00:00:00"`
  - `unix_timestamp（to_unix_timestamp）`将日期时间转化为时间戳，`unix_timestamp("2021-02-03 00:00:00") = 1612310400`
  - `from_utc_timestamp`将UTC日期时间，转化为特定时区的日期时间，`from_utc_timestamp("2021-02-03 00:00:00", "PRC") = "2021-02-03 08:00:00"`
  - `to_utc_timestamp`将特定时区的日期时间，转化为UTC日期时间，`to_utc_timestamp("2021-02-03 08:00:00", "PRC") = "2021-02-03 00:00:00"`
  - `date_format`将时间戳或日期时间转化为特定格式的字符串，`date_format("2021-02-03", "yyyy/M/d") = "2021/2/3"`
  - `to_date`获取日期时间对象中的日期部分，`to_date("2021-02-03 12:58:59") = "2021-02-03"`

- 获取日期时间中的特定部分
  - `year`获取年份，`year("2021-02-03") = 2021`
  - `quarter`获取季度，`quarter("2021-02-03") = 1`
  - `month`获取月份，`month("2021-02-03") = 2`
  - `weekofyear`获取一年中的第几个星期，`weekofyear("2021-02-03") = 5`
  - `day（dayofmonth）`获取一月中的第几天，`day("2021-02-03") = 3`
  - `dayofweek`获取一周中的第几天，`dayofweek("2021-02-03") = 4`
  - `last_day`获取当月的最后一天，`last_day("2021-02-03") = "2021-02-28"`
  - `next_day`获取从当天开始的下一个星期几，`next_day("2021-02-03", "Sunday") = "2021-02-07"`
  - `hour`获取小时，`hour("12:58:59") = 12`
  - `minute`获取小时，`minute("12:58:59") = 58`
  - `second`获取小时，`second("12:58:59") = 59`

- 日期时间向下取整
  - `floor_year`向下取整，精确到年份，`floor_year(cast("2021-02-03 12:58:59" as timestamp)) = "2021-01-01 00:00:00"`
  - `floor_quarter`向下取整，精确到季度，`floor_quarter(cast("2021-02-03 12:58:59" as timestamp)) = "2021-01-01 00:00:00"`
  - `floor_month`向下取整，精确到月份，`floor_month(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-01 00:00:00"`
  - `floor_week`向下取整，精确到周，`floor_week(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-01 00:00:00"`
  - `floor_day`向下取整，精确到日，`floor_day(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-03 00:00:00"`
  - `floor_hour`向下取整，精确到小时，`floor_hour(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-03 12:00:00"`
  - `floor_minute`向下取整，精确到分钟，`floor_minute(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-03 12:58:00"`
  - `floor_second`向下取整，精确到秒，`floor_second(cast("2021-02-03 12:58:59" as timestamp)) = "2021-02-03 12:58:59"`

- 日期时间加减
  - `datediff`计算两个日期之间差多少天，`datediff("2021-02-05", "2021-02-03") = 2`
  - `months_between`计算两个日期之间差多少月，`months_between("2021-03-05", "2021-02-03") = 1.06451613`
  - `date_add`将指定日期加n天，`date_add("2021-02-03", 2) = "2021-02-05"`
  - `date_sub`将指定日期减n天，`date_sub("2021-02-03", 2) = "2021-02-01"`
  - `add_months`将指定日期加n个月，`add_months("2021-02-28", 1) = "2021-03-31"`
  - 给日期时间加减特定单位的时间（多少秒、天等），`to_date("2021-02-03") - interval 10 second = "2021-02-02 23:59:50"`

## 7、复杂类型对象处理函数

- array类型对象操作函数
  - `array`生成数组，`array(1, 2, 3)`
  - `index`返回数组中的第n个元素，`index(array("a", "b", "c"), 2) = "c"`
  - `array_contains`查找数组中是否包含某个元素，`array_contains(array(1, 2, 3), 2) = true`
  - `find_in_set`查找某个字符串在字符串表示的数组（以**,**分割元素）中的位置，`find_in_set("ab", "abc,b,ab,c,def") = 3`
  - `sort_array`给数组排序，`sort_array(array("b", "c", "a")) = array("a", "b", "c")`
  - `sort_array_by`当数组由struct元素构成时，按照struct中的字段给数组排序，`sort_array_by(array(struct("b", 100), struct("a", 200)), "col1", "ASC") = array(struct("a", 200), struct("b", 100))`
  - `size`查询array、map中元素的个数，`size(array(1, 2, 3)) = 3`
  
  - `collect_list`将序列合并为一个数组
  - `collect_set`将序列合并为一个数组（不包含重复值）
  
  ```hive
  select collect_list(id) from A;
  # 结果是 [1,2,2,3,4];
  select collect_set(id) from A;
  # 结果是 [1,2,3,4];
  ```

- map类型对象操作函数
  - `map`生成有名数组，`map("英语", 90, "物理", NULL)`
  - `str_to_map`将字符串按照元素分隔符、键值分隔符切分成有名数组，`str_to_map("英语:90,物理:NULL", ",", ":")`
  - `map_keys`获取有名数组中的键，`map_keys(map("英语", 90, "物理", NULL)) = array("英语", "物理")`
  - `map_values`获取有名数组中的值，`map_values(map("英语", 90, "物理", NULL)) = array(90, NULL)`

- struct类型对象操作函数
  - `struct`生成结构体，默认字段名称为 col1、col2、 ...,`struct(90, NULL)`
  - `named_struct`生成结构体，`named_struct("英语",90,"物理",NULL)`

- union类型对象操作函数
  - `create_union`生成联合体,`create_union(1, cast(NULL as bigint), "8808-3124")`
  - `extract_union`将联合体解析为结构体，或者获取其中的某个字段,`extract_union(create_union(1, 13137218094, "8808-3124"), 0)`

- URL操作函数
  - `parse_url`获取URL中某一部分（**PROTOCOL、HOST、AUTHORITY、PATH、QUERY、REF、FILE、USERINFO**）
  - `parse_url_tuple`获取URL中的某些部分，并形成数组
    
  ```hive
  # 获取URL中某一部分信息;
  # 返回结果 张三;
  select parse_url("http://wly@localhost:3939/serv?id=1&name=张三#score", "QUERY", "name");
  
  # 获取URL中各部分信息;
  # 返回结果 http	wly@localhost:3939	wly	localhost	/serv?id=1&name=张三	/serv	id=1&name=张三	张三	score;
  select parse_url_tuple(
    "http://wly@localhost:3939/serv?id=1&name=张三#score",
    "PROTOCOL", "AUTHORITY", "USERINFO", "HOST", "FILE", "PATH", "QUERY", "QUERY:name", "REF"
  );
  ```

- XML操作函数
  - `xpath`使用xpath获取XML文档中的某些信息
  - `xpath_boolean、xpath_short、xpath_int、xpath_long、xpath_double、xpath_float、xpath_number、xpath_string`使用xpath获取XML文档中的特定类型的信息

  ```hive
  # 获取节点内部的文本, 返回结果 ["b1","b2","b3"];
  select xpath('<a attr="c"> <b>b1</b> <b>b2</b> <b>b3</b> </a>', '//b/text()');
  # 获取节点属性, 返回结果 ["c"];
  select xpath('<a attr="c"> <b>b1</b> <b>b2</b> <b>b3</b> </a>', 'a/@attr');
  # 获取是否有相应的xpath路径, 返回结果 true;
  select xpath_boolean('<a>b</a>','a/text()');
  # 获取xpath计算结果, 返回结果 3.0;
  select xpath_number('<a><b>1</b><b>2</b></a>','sum(a/b)');
  ```

- JSON操作函数
  - `get_json_object`获取json文档中，json路径对应的值
  - `json_tuple`获取json文档中，根目录下多个字段的值

  ```hive
  # 获取JSON数组中的值，返回结果 1;
  select get_json_object('{ "a": [1, 2], "b": {"c": "score", "d": 100} }', "$.a[0]");
  # 获取多个JSON中的值，并构成数组，返回结果 [1,2]	{"c":"score","d":100};
  select json_tuple('{ "a": [1, 2], "b": {"c": "score", "d": 100} }', "a", "b");
  ```

## 8、窗口&分析函数

- `first_value`获取序列中的第一个值
- `last_value`获取序列中的最后一个值
- `lag`将序列时滞n各周期
- `lead`将序列前导n各周期
- `row_number`获取序列号
- `rank`获取排名，与row_number不同点在于，排名相同时都取靠前的序号
- `dense_rank`获取排名，与rank不同点在于，排名相同的记录之后的排名，会紧接着上一个排名
- `percent_rank`计算(当前rank - 1) / (总记录数 - 1)
- `cume_dist`计算小于等于当前值的记录数 / 总记录数
- `ntile`将序列按照排序分成n组，返回组别编号

```hive
select first_value(id) over(order by id) from A;
# 结果是 1 1 1 1 1;
select last_value(id) over(order by id) from A;
# 结果是 4 4 4 4 4;
select lag(id, 1) over(order by id) from A;
# 结果是 NULL 1 2 2 3;
select lead(id, 1) over(order by id) from A;
# 结果是 2 2 3 4 NULL;
select row_number() over(order by id) from A;
# 结果是 1 2 3 4 5;
select rank() over(order by id) from A;
# 结果是 1 2 2 4 5;
select dense_rank() over(order by id) from A;
# 结果是 1 2 2 3 4;
select percent_rank() over(order by id) from A;
# 结果是 0.0 0.25 0.25 0.75 1.0;
select cume_dist() over(order by id) from A;
# 结果是 0.2 0.6 0.6 0.8 1.0;
select ntile(2) over(order by id) from A;
# 结果是 1 1 1 2 2;
```

## 9、表生成类函数

- `explode`将数组、结构体等对象的每个元素转化为一条记录
- `posexplode`将数组对象的每个元素转化为一条记录，包含元素在数组中的索引值
- `inline`将以结构体为元素组成的数组，转化为每个结构体为一条记录，结构体中的每个字段为一个字段
- `stack`将第2-k个参数，按照先行后列的方式转化为n条记录
- `parse_url_tuple、json_tuple`见上文

```hive
select name, B.* from student A 
  lateral view explode(score) B as class, score
  where A.id = 1;
result> name	b.class	b.score
result> 张三	语文	60
result> 张三	数学	70
result> 张三	英语	80

select name, B.* from student A 
  lateral view posexplode(class) B
  where A.id = 1;
result> name	b.pos	b.val
result> 张三	0	语文
result> 张三	1	数学
result> 张三	2	英语

select inline(array(named_struct("a", 1, "b", 2), named_struct("a", 3, "b", 4))) ;
result> a	b
result> 1	2
result> 3	4

select stack(2, 1, 2, 3) ;
result> col0	col1
result> 1	2
result> 3	NULL
```

## 10、其它常用函数

- `if`三目运算，如果第一个参数为真则返回第二个参数，否则返回第三个参数，`if(null, 1, 2) = 2`
- `case、when、else`多分支语句
- `assert_true`如果参数为真则返回NULL，否则抛出错误
- `rand`获取随机数
- `format_number`将数值转化为特定格式的字符串，`format_number(1234.567, 2) = format_number(1234.567, "#,###.##") = "1,234.57"`

- `trunc`将数值或日期时间向下取整
```hive
# 将数值保留最多两位有效小数，返回结果 1234.56;
select trunc(1234.567, 2);
# 将十位数以上的有效数字，返回结果 1200;
select trunc(1234.567, -2);
# 日期向下取整，精确到月份，返回结果 "2021-02-01";
select trunc("2021-02-03", "MM");
```

- `histogram_numeric`统计将序列等分为n个区间之后，每个区间的代表值和频数（参考直方图）
```hive
select histogram_numeric(id, 3) from A ;
# 结果是 [{"x":1.0,"y":1.0},{"x":2.333333333333333,"y":3.0},{"x":4.0,"y":1.0}];
```

<!--

- `in_file`返回某个字符串是否在文件中出现，文件不存在则报错（只返回false？），`in_file("张三", "student.csv") = false`

# 调用java方法
reflect（java_method）、reflect2

## 内部函数
udftoboolean、udftobyte、udftoshort、udftolong、udftodouble、udftofloat、udftointeger、udftostring
noop、noopstreaming、noopwithmap、noopwithmapstreaming
$sum0、grouping、bloom_filter、in_bloom_filter、sq_count_check
enforce_constraint、cardinality_violation、compute_stats、get_splits
matchpath、replicate_rows、to_epoch_milli、width_bucket、windowingtablefunction

-->


[^1]: 四舍六入五考虑，五后非零就进一，五后为零看奇偶，五前为偶应舍去，五前为奇要进一

