

```
# 列举所有函数 ;
list functions ;
# 查看函数定义 ;
desc function sum ;
# 查看带有示例的函数定义 ;
desc function extended sum ;
```

## 当前系统信息
restrict_information_schema
current_database、current_user、current_groups、current_authorizer、logged_in_user
uuid、version

## 基础数学运算
+、-、*、/（div）、^（pow、power）、%（mod）、pmod
e、pi、exp、ln、log、log2、log10、factorial
sign、abs、positive、negative、round、floor、ceil（ceiling）、bround、format_number、trunc
lag、lead
## 进制转化
conv、hex、unhex、bin
## 三角函数
degrees、radians、sin、tan、cos、asin、acos、atan
## 比较运算
<、<=、>、>=、=、==、!=、<>、<=>、between、in
isnull、istrue、isfalse、isnotnull、isnottrue、isnotfalse
## 按位运算
~、&、|、shiftleft、shiftright、shiftrightunsigned
## 逻辑运算
and、or、not、!
## 统计函数
count、min、max、avg、sum、sqrt、cbrt、percentile、percentile_approx
corr、covar_pop、covar_samp、std（stddev、stddev_pop）、stddev_samp、variance（var_pop）、var_samp
rand、rank

# 窗口函数
row_number、dense_rank、first_value、last_value、ntile、cume_dist、percent_rank

## 筛选日期时间中的特定部分
year、month、weekofyear、day、dayofmonth、dayofweek、last_day、next_day、hour、quarter、minute、second
## 日期时间向下取整
floor_year、floor_month、floor_week、floor_day、floor_hour、floor_quarter、floor_minute、floor_second
current_date、current_timestamp
## 日期时间加减函数
datediff、months_between、date_add、date_sub、add_months
internal_interval
- 计算时间差
select current_timestamp() - INTERVAL 10 second
## 日期时间 - 时间戳 转化函数
unix_timestamp、from_unixtime、from_utc_timestamp、to_unix_timestamp、to_utc_timestamp
## 日期时间 - 字符串 转化函数
date_format、to_date

## 字符串操作函数
length（char_length、character_length）、octet_length
lower（lcase）、upper（ucase）、reverse、initcap
space、lpad、rpad、trim、ltrim、rtrim
substr（substring）、substring_index、replace、translate、split、concat、concat_ws、coalesce、repeat、printf
elt、field、locate、instr、in_file
like、likeall、likeany、rlike、levenshtein
regexp、regexp_extract、regexp_replace
mask、mask_first_n、mask_last_n、mask_show_first_n、mask_show_last_n
sentences、ngrams、context_ngrams
- 从movies.reviw中查找10个最常见的2个单词组成的词组
SELECT context_ngrams(sentences(lower(review)), array("i", "love", null, null), 10) FROM movies ;
## 字符 - ascii数值 转化函数
ascii、chr
## 字符串转化
encode、decode
str_to_map、base64、unbase64
udftoboolean、udftobyte、udftoshort、udftolong、udftodouble、udftofloat、udftointeger、udftostring

## XML操作函数
xpath、xpath_boolean、xpath_short、xpath_int、xpath_long、xpath_double、xpath_float、xpath_number、xpath_string

## json 操作函数
get_json_object、json_tuple

## url 操作函数
parse_url、parse_url_tuple

## 特征值计算
hash、murmur_hash、mask_hash、soundex、md5、sha、sha1、sha2
## aes加密解密
aes_encrypt、aes_decrypt
## 计算CRC码（循环冗余信息码）
crc32

## array操作函数
array、array_contains、find_in_set、index、sort_array、sort_array_by

## map操作函数
map、map_keys、map_values
regr_avgx、regr_avgy、regr_count、regr_intercept、regr_r2、regr_slope、regr_sxx、regr_sxy、regr_syy

## struct操作函数
struct、named_struct

# 查询array、map中的元素个数
size

## 结构操作函数
create_union、extract_union

## 分支语句
if、case、when、else
## 非真则抛出错误
assert_true

## NULL 值处理
nullif、nvl

## 多个参数生成唯一结果类函数
greatest、least

## 行列转换
collect_list、collect_set、explode、posexplode、inline、stack

## 约束
enforce_constraint

# 调用java方法
reflect（java_method）、reflect2

histogram_numeric
- 直方图统计信息
SELECT histogram_numeric(val, 3) FROM src ;

## 内部函数
$sum0、grouping、bloom_filter、in_bloom_filter、sq_count_check
cardinality_violation、compute_stats、get_splits

noop
noopstreaming
noopwithmap
noopwithmapstreaming

matchpath
replicate_rows
to_epoch_milli
width_bucket
windowingtablefunction



