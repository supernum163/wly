

```
# 列举所有函数 ;
list functions ;
# 查看函数定义 ;
desc function sum ;
# 查看带有示例的函数定义 ;
desc function extended sum ;
```


## 基础数学运算
format_number、trunc

cast : udftoboolean、udftobyte、udftoshort、udftolong、udftodouble、udftofloat、udftointeger、udftostring

regr_avgx、regr_avgy、regr_count、regr_intercept、regr_r2、regr_slope、regr_sxx、regr_sxy、regr_syy


# 窗口函数
row_number、dense_rank、first_value、last_value、ntile、cume_dist、percent_rank、lag、lead
rand、rank、percentile、percentile_approx

## 行列转换
collect_list、collect_set、explode、posexplode、inline、stack

## 非真则抛出错误
assert_true

## 约束
enforce_constraint

# 调用java方法
reflect（java_method）、reflect2


- `in_file`返回某个字符串是否在文件中出现，文件不存在时会报错（只返回false？），`in_file("张三", "student.csv") = false`

- `histogram_numeric`直方图统计信息
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



