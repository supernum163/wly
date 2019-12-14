---
title: R语言数据整理利器——dplyr
date: 2019-12-30
categories:
  - R语言
tags:
  - R语言扩展包
keywords:
  - R语言
  - dplyr
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/12/14/Q2vm5V.png
---

这篇文章我们将介绍。

<!--more-->

<!-- toc -->

**dplyr**对于处理以行列关系表示的数据框（每一行是一个观测值，每一列是一个纬度）十分有效。首先**dplyr**与**SQL**语句十分类似，其包含了**select、filter、mutate、summarise**等几个关键的函数，可以帮助我们非常方便的筛选、修改、汇总数据。此外**dplyr**中引入了管道处理的概念（`x %>% f(y)`等同于`f(x, y)`），使我们可以将运算结果优雅的传递给下一个函数处理，避免了嵌套运用多个函数处理数据时，必须使用多层括号或多个临时变量的情形。

<br>

## 1、筛选、删除、添加、修改变量

我们可以使用{{< hl-text primary >}}select{{< /hl-text >}}函数，筛选变量、反选（删除）变量、调整变量位置。注意这里我们既可以使用变量名，也可以使用字符串来筛选变量；反选变量时需要使用负号，此时相当于筛选除了该变量之外的所有变量；我们可以在同一条命令中筛选多次，此时相当于先按照筛选条件的先后顺序进行筛选，再取筛选结果的并集，即使某些变量多次被选择，也只会在结果中出现一次。此外我们还可以在筛选语句中使用以下帮助函数以提高筛选效率。

| 函数                     | 解释说明                                                      
|:-------------------------|:-----------------------------------------------------------------
| starts_with、 ends_with  | 筛选变量名以某个字符串开头/结尾的变量（如`select(mtcars, ends_with("t"))`）
| contains                 | 筛选变量名中包含某个字符串的变量（如`select(mtcars, contains("ar"))`）
| matches                  | 筛选变量名中匹配某个正则表达式的变量（如`select(mtcars, matches("\\w{4}"))`）
| num_range                | 筛选从某个变量到某个变量之间的所有变量（如`select(mtcars, hp:am)`）
| one_of                   | 筛选变量名在某个字符串数组中出现的变量（如`select(mtcars, c("hp", "am"))`）
| everything               | 筛选所有变量（如`select(mtcars, -hp, everything())`）
| group_cols               | 筛选分组变量（如`group_by(mtcars, hp) %>% select(group_cols())`）

我们可以使用{{< hl-text primary >}}mutate{{< /hl-text >}}函数，转换现有变量生成新的变量，或者直接用新生成的变量替换现有变量。但这种方式既会保留新生成的变量，也会保留现有变量（除非我们使用**NULL**值来删除某个变量）。如果我们只希望保留新生成的变量，则可以使用{{< hl-text primary >}}transmute{{< /hl-text >}}函数。此外我们还可以使用{{< hl-text primary >}}mutate_all、mutate_at、mutate_if{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行转换。注意以上函数转换变量时，我们使用的函数需要返回与原始变量长度一致的变量，否则会重复使用。

```R
mtcars %>% mutate(wt = wt/mean(wt), newvar = .data[[1]], mpg = NULL)
starwars %>% mutate_at(c("height", "mass"), mean, na.rm = TRUE)
starwars %>% mutate_if(is.numeric, mean, na.rm = TRUE)
```

- 数学运算函数、逻辑运算函数（此时新生曾的变量是逻辑值）、位运算函数、字符串处理函数等
- **lead、lag**求前导、时滞
- **cumall、cumany、cummean**以累计的形式求**all、any、mean**，其它累计算法还有**cummax、cummin、cummean、cumsum**等

row_number      数组按从小到大的顺序排列之后对应的行号
ntile           将数组从小到大分为n个等级，如`ntile(euro, 5)`
min_rank        数组按从小到大的顺序排列之后对应的序号（大小一致的值取最小行号）
dense_rank      数组中的值，对应去重后从小到大排列的数组中的序号
percent_rank    比例化后的**min_rank**
cume_dist       数组按从小到大的顺序排列之后对应的序号（大小一致的值取最大行号），在进行比例化

between         判断数组中的值是否在某个范围内，如`between(euro, 1, 10)`
if_else         根据条件判断式，决定处理数组取值的方式
case_when       根据多个条件判断式，处理数组中的值
na_if           以**NA**值替换数组中的某个值
coalesce        以某个值替换数组中的**NA**值
recode          以某个值替换数组中的特定值
recode_factor   以某个值替换因子型数组中的特定因子


我们可以使用{{< hl-text primary >}}add_row、add_column{{< /hl-text >}}函数，添加观测值、添加变量。

我们可以使用{{< hl-text primary >}}rename{{< /hl-text >}}函数，重命名某个变量。

我们可以使用{{< hl-text primary >}}has_rownames、rownames_to_column、column_to_rownames、remove_rownames{{< /hl-text >}}函数，判断是否有行名、删除行名、将行名转化为变量、将变量转化为行名。



## 2、筛选、删除、添加观测值

我们可以使用{{< hl-text primary >}}filter{{< /hl-text >}}函数，根据一个或多个逻辑数组筛选观测值。

我们可以使用{{< hl-text primary >}}top_n{{< /hl-text >}}函数，筛选出前n条观测值。
我们可以使用{{< hl-text primary >}}distinct{{< /hl-text >}}函数，根据某些变量，或全部变量筛选出不重复的观测值。

我们可以使用{{< hl-text primary >}}sample_frac、sample_n{{< /hl-text >}}函数，随机筛选出一定比例或一定数量的观测值。

我们可以使用{{< hl-text primary >}}slice{{< /hl-text >}}函数，根据行号筛选、反选观测值。注意此时我们可以使用`n()`来表示最大行号。

```
slice(mtcars, -5:-n())
```

## 3、排序观测值

我们可以使用{{< hl-text primary >}}arrange{{< /hl-text >}}函数，将数据框中的观测值按照某一个或多个变量的取值大小进行排序。这些变量可以是连续变量，也可以是分类变量，如果变量是由字符构成的，则会按照字符编码进行排序。使用多个变量排序时，会先按照第一个变量的取值进行排序，如果取值相同则再按照第二个变量进行排序，依次类推，如果所有变量取值都一致，则保持观测值的位置不变。排序时我们还可以使用{{< hl-text primary >}}desc{{< /hl-text >}}函数，获取某个变量的逆序。

```R
arrange(data, var1, var2, ...)
arrange(data, desc(var), var2, ...)
```

## 4、分组与汇总观测值

我们可以使用{{< hl-text primary >}}group_by{{< /hl-text >}}函数，将数据框按某些变脸进行分组，对分组之后的数据框进行的任何操作，都相当于先在组内进行相应的操作，然后再依次合并操作结果。如果需要取消分组，则可以使用{{< hl-text primary >}}ungroup{{< /hl-text >}}函数。

我们可以使用{{< hl-text primary >}}summarise{{< /hl-text >}}函数，对数据框进行汇总。此外我们还可以使用{{< hl-text primary >}}summarise_if、summarise_at、summarise_all{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行汇总。注意汇总时需要使用的函数，必须只返回一个值。这些汇总函数可以是：

- **sum、mean、median、min、max、quantile、IQR、var、sd、mad**等函数
- **n、n_distinct**查询数组包含多个个值、多少个不同的值
- **first、last、nth**获取数组的第一个、最后一个、第n个值

我们可以使用{{< hl-text primary >}}count{{< /hl-text >}}函数，查询数据框中有多少观测值



## 5、交并合补与左右内外连接

我们可以使用{{< hl-text primary >}}bind_rows、bind_cols{{< /hl-text >}}函数，为数据框添加观测值、添加变量。

类似R语言系统函数中对数组进行交并合补，我们也可以使用{{< hl-text primary >}}intersect、union、setdiff{{< /hl-text >}}函数，取得两个数据框的交集、并集、补集。并使用{{< hl-text primary >}}setequal{{< /hl-text >}}函数判断两个数据框是否相同。此外，如果取并集时需要包含重复的观测值，则可以使用{{< hl-text primary >}}union_all{{< /hl-text >}}函数。

{{< image classes="fancybox center" src="https://s2.ax1x.com/2019/12/14/QRBhp4.png" >}}

我们可以使用{{< hl-text primary >}}left_join、right_join、inner_join、full_join、semi_join、anti_join{{< /hl-text >}}函数，将两个数据框按照一个或多个变量，进行左连接、右连接、内连接、外连接、半连接、反连接。

{{< image classes="fancybox center" src="https://s2.ax1x.com/2019/12/14/QRBWhF.png" >}}


获取更多速记手册，请前往 [这里](https://rstudio.com/resources/cheatsheets/)

<!--https://s2.ax1x.com/2019/12/14/Q2vuCT.png-->

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 函数**count**与**n**有何区别？
- `select(mtcars, -hp, everything())`与`select(mtcars, everything(), -hp)`有何不同？
- ？

{{< /note >}}

<br>
