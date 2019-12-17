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

R语言中以程序包**dplyr**为核心，外加**rlang、magrittr、tibble、tidyr**等程序包的实用函数，可以重新定义R语言中的数据整理模式。这篇文章我们将介绍这套数据整理模式下，如何对数据框进行增删改查、交并合补。

<!--more-->

<!-- toc -->

**dplyr**对于处理以行列关系表示的数据框（每一行是一个观测值，每一列是一个维度）十分有效。首先**dplyr**与**SQL**语句十分类似，其中**select、filter、mutate、summarise**等几个关键的函数，可以帮助我们非常方便的筛选、修改、汇总数据。此外**dplyr**还可以使我们非常便捷的对数据集进行交并合补。最后**dplyr**中还引入了**管道处理**的概念（如`x %>% f(y)`等同于`f(x, y)`），使我们可以将运算结果优雅的传递给下一个函数处理，避免了嵌套运用多个函数处理数据时，必须使用多层括号或多个临时变量的情形。

<br>

## 1、添加观测值、添加变量

我们可以使用{{< hl-text primary >}}add_row、add_column{{< /hl-text >}}函数，添加观测值、添加变量。类似于**rbind、cbind**函数，但这两个函数还可以在原数据框的任意位置插入行列。注意这两个函数是根据**tibble**类型的数据框实现的，不支持使用行名；此外**add_row**会对列名进行更加严格的检查，所以需要我们按照列名添加观测值。

```R
> df <- tibble(x = 1:3, y = 3:1)
# 添加观测值
> add_row(df, x = 4, y = 0)
# 添加变量
> add_column(df, z = -1:1, w = 0)
```

<br>

## 2、修改行名、列名

我们可以使用{{< hl-text primary >}}rename{{< /hl-text >}}函数，重命名数据框中的某个变量。此外我们还可以使用{{< hl-text primary >}}rename_all、rename_at、rename_if{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行重命名。

为了更好的在普通数据框与**tibble**类型的数据框之间转换，我们可以将行名转化为一个单独的变量。使用{{< hl-text primary >}}rownames_to_column、column_to_rownames{{< /hl-text >}}函数，将行名转化为变量、将变量转化为行名。此外我们还可以使用{{< hl-text primary >}}has_rownames、remove_rownames{{< /hl-text >}}函数，判断数据框是否有行名、删除行名。

```R
# 修改列名
> rename(mtcars, var1 = "cyl", var2 ="am")
# 将行名转化为变量
> rownames_to_column(mtcars)
```

<br>

## 3、筛选变量

我们可以使用{{< hl-text primary >}}select{{< /hl-text >}}函数，筛选变量、反选（删除）变量、重命名变量、调整变量位置。此外我们还可以使用{{< hl-text primary >}}select_all、select_at、select_if{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行筛选。注意筛选变量时我们既可以使用变量名，也可以使用字符串来筛选变量；反选变量时需要使用负号，此时相当于筛选除了该变量之外的所有变量；我们可以在同一条命令中筛选多次，此时相当于先按照筛选条件的先后顺序进行筛选，再取筛选结果的并集，即使某些变量多次被选择，也只会在结果中出现一次。此外我们还可以在筛选语句中使用以下帮助函数以提高筛选效率。

| 函数                     | 解释说明                                                      
|:-------------------------|:-----------------------------------------------------------------
| starts_with、 ends_with  | 筛选变量名以某个字符串开头/结尾的变量（如`select(mtcars, ends_with("t"))`）
| contains                 | 筛选变量名中包含某个字符串的变量（如`select(mtcars, contains("ar"))`）
| matches                  | 筛选变量名中匹配某个正则表达式的变量（如`select(mtcars, matches("\\w{4}"))`）
| num_range                | 筛选从某个变量到某个变量之间的所有变量（如`select(mtcars, hp:am)`）
| one_of                   | 筛选变量名在某个字符串数组中出现的变量（如`select(mtcars, c("hp", "am"))`）
| everything               | 筛选所有变量（如`select(mtcars, -hp, everything())`）
| group_cols               | 筛选分组变量（如`mtcars %>% group_by(hp) %>% select(group_cols())`）


```R
# 筛选变量
> select(mtcars, hp : am)
# 反选（删除）变量
> select(mtcars, -hp : -am)
# 重命名变量
> select(mtcars, var1 = "hp", var2 ="am")
# 调整变量位置
> select(mtcars, -hp, everything())
```

<br>

## 4、转化变量

我们可以使用{{< hl-text primary >}}mutate{{< /hl-text >}}函数转化变量，并将新生成的变量添加到数据框中，或者直接用新生成的变量替换现有变量。但这种方式既会保留新生成的变量，也会保留原有的变量（除非我们使用**NULL**值来删除某个变量）。如果我们只希望保留新生成的变量，则可以使用{{< hl-text primary >}}transmute{{< /hl-text >}}函数。此外我们还可以使用{{< hl-text primary >}}mutate_all、mutate_at、mutate_if{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行转化。注意以上函数转化变量时，我们使用的函数需要返回与原始变量长度一致的变量，否则返回值会被重复使用。

```R
# 转化变量
>  mutate(mtcars, wt = wt/mean(wt), am = NULL)
# 对所有变量进行转化
> mutate_all(mtcars, round, digits = 2)
# 对某些变量进行转化
> mutate_at(mtcars, vars(hp : am), round, digits = 2)
# 对满足特定条件的变量进行转化
> mutate_if(mtcars, is.numeric, round, digits = 2)
```

<br>

### 4.1、变量转化型函数

我们在使用**mutate**函数转化变量时，往往需要用到变量转化型函数。这样的函数往往需要接收一个（或多个）变量作为参数，并返回一个与其等长的新变量。这样的函数可以是数学运算函数（如**+、-、log**等）、逻辑运算函数（如**&、|、!**等）、位运算函数（如**bitwAnd、bitwOr**等）、字符串处理函数（如**paste、sprintf**等）。还可以是**dplyr**中提供的以下函数：

| 函数            | 解释说明                                                      
|:----------------|:-----------------------------------------------------------------
| lead            | 求数组的n阶前导，如`lead(co2, 12)`
| lag             | 求数组的n阶时滞
| cumany          | 以累计的形式求是否有真值
| cumall          | 以累计的形式求是否全为真值
| cummean         | 以累计的形式求平均值，其它 [累计算法](../../04/使用r语言对数组进行数学运算/index.html#5-2-时间序列的累计算法) 还有**cummax、cummin、cummean、cumsum**等
| row_number      | 数组按从小到大的顺序排列之后对应的行号，如`mutate(mtcars, index = row_number())`
| ntile           | 将数组从小到大分为n个等级，如`ntile(euro, 5)`
| dense_rank      | 数组中的值，对应去重后从小到大排列的数组中的序号
| min_rank        | 数组按从小到大的顺序排列之后对应的序号（大小一致的值取最小行号）
| percent_rank    | 数组按从小到大的顺序排列之后对应的序号（大小一致的值取最小行号），再进行比例化
| cume_dist       | 数组按从小到大的顺序排列之后对应的序号（大小一致的值取最大行号），再进行比例化
| between         | 判断数值是否在某个范围内，如`between(euro, 1, 10)`
| near            | 判断两个数值是否在某个可接收范围内近似相等，如`near(sqrt(2) ^ 2, 2)`
| if_else         | 根据条件判断式，决定处理数组取值的方式，如`if_else(euro > 10, "10+", "10-")`
| case_when       | 根据多个条件判断式，处理数组中取值，如`case_when(euro > 100 ~ "100+", euro > 10 ~ "10+", TRUE ~ "0+")`
| na_if           | 以**NA**值替换数组中的某个值，如`na_if(starwars$eye_color, "unknown")`
| coalesce        | 以某个值替换数组中的**NA**值，如`coalesce(c(1:10, NA), 0L)`
| recode          | 以某个值替换数组中的特定值，如`recode(1:10, "10" = 0L)`
| recode_factor   | 以某个值替换因子型数组中的特定因子，如`recode_factor(state.region, "Northeast" = "East")`

<br>

## 5、排序观测值

我们可以使用{{< hl-text primary >}}arrange{{< /hl-text >}}函数，将数据框中的观测值按照某一个或多个变量的取值大小进行排序。这些变量可以是连续变量，也可以是分类变量，如果变量是由字符构成的，则会按照字符编码进行排序。使用多个变量排序时，会先按照第一个变量的取值进行排序，如果取值相同则再按照第二个变量进行排序，依次类推，如果所有变量取值都一致，则保持观测值的位置不变。排序时我们还可以使用{{< hl-text primary >}}desc{{< /hl-text >}}函数，获取某个变量的逆序。

```R
# 排序观测值
> arrange(mtcars, desc(carb), wt)
```

<br>

## 6、筛选观测值

首先我们可以使用{{< hl-text primary >}}distinct{{< /hl-text >}}函数，根据某些变量，或全部变量筛选出不重复的观测值。即使我们只根据部分变量进行去重，也可以保留全部变量，此时保留的是第一条不重复的观测值。

其次我们可以使用{{< hl-text primary >}}top_n、top_frac{{< /hl-text >}}函数，根据某个变量取值的大小，筛选出排在 *前面* 的一定数量或一定比例的观测值。这里结合使用**row_number、desc**等函数，即可像**head、tail**函数一样，筛选出数据框的前n条、后n条值（或者按比例）。此外我们可以使用{{< hl-text primary >}}sample_n、sample_frac{{< /hl-text >}}函数，随机筛选出一定数量或一定比例的观测值。

再次我们还可以使用{{< hl-text primary >}}slice{{< /hl-text >}}函数，根据行号筛选、反选观测值。注意此时我们可以使用`n()`来表示最大行号。

最后我们可以使用{{< hl-text primary >}}filter{{< /hl-text >}}函数，根据一个或多个逻辑数组（或生成逻辑数组的判断函数）筛选观测值。此外我们还可以使用{{< hl-text primary >}}mutate_all、mutate_at、mutate_if{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量，按照特定的判断函数进行筛选。此时我们除了使用常规的比较运算函数（如**<、>、==**等）、逻辑运算函数（如**&、|、!**等）、数据类型判断函数（如**is.na**等）之外，还可以使用**between、near**函数，来判断数值型变量的取值是否在某个范围内。

```R
# 根据特定变量去重，保留第一条不重复的观测值
> distinct(mtcars, cyl, gear, .keep_all = TRUE)
# 筛选前10%的观测值
> top_frac(mtcars, 0.1, desc(row_number()))
# 随机抽取50条观测值（可重复抽取）
> sample_n(mtcars, 50, replace = TRUE, weight = mpg)
# 去除第5条至最后一条观测值
> slice(mtcars, -5:-n())
# 筛选满足特定条件的观测值
> filter(mtcars, hp > mean(hp), near(wt, 2.7, tol = .1))
```

<br>

## 7、汇总观测值

我们可以使用{{< hl-text primary >}}tally、count{{< /hl-text >}}函数，查询数据框中有多少条观测值。二者的区别在于：**tally**常被用于计算数据框整体包含了多少条观测值，而**count**则常被用于计算某个变量取特定值时对应有多少条观测值。

我们可以使用{{< hl-text primary >}}summarise{{< /hl-text >}}函数，对数据框进行汇总。此外我们还可以使用{{< hl-text primary >}}summarise_if、summarise_at、summarise_all{{< /hl-text >}}函数，对所有变量、对某些变量、对满足特定条件的变量进行汇总。注意汇总时需要使用的函数，往往只需要返回一个值作为汇总结果。

```R
# 汇总观测值数量
> summarise(mtcars, n())
# 汇总去重后的观测值数量
> distinct(mtcars, wt) %>% tally()
# 汇总某个变量取特定值时对应有多少条观测值
> count(mtcars, cyl)
```

<br>

### 7.1、变量汇总型函数

我们在使用**summarise**函数汇总变量时，往往需要用到变量汇总型函数。这样的函数往往需要接收一个（或多个）变量作为参数，并返回一个单一的值作为汇总结果。这样的函数可以是分位数计算函数（如**median、min、max、quantile**等）、特征值计算函数（如**sum、mean、IQR、var、sd、mad**等）、逻辑值汇总函数（如**any、all**等），还可以是**dplyr**中提供的以下函数：

| 函数            | 解释说明                                                      
|:----------------|:-----------------------------------------------------------------
| n               | 查询数组包含多个个值
| n_distinct      | 查询数组包含多少个不同的值
| first           | 获取数组的第一个值
| last            | 获取数组的最后一个值
| nth             | 获取数组的第n个值

<br>

## 8、分组

我们可以使用{{< hl-text primary >}}group_by{{< /hl-text >}}函数，将数据框按某些变脸进行分组，对分组之后的数据框进行的任何操作，都相当于先在组内进行相应的操作，然后再依次合并操作结果。如果需要取消分组，则可以使用{{< hl-text primary >}}ungroup{{< /hl-text >}}函数。

```R
# 分组转化变量
> mtcars %>% group_by(cyl) %>% mutate(wt = wt/mean(wt))
# 分组筛选最后一条数据
> mtcars %>% group_by(cyl) %>% top_n(1, row_number())
# 分组汇总
> mtcars %>% group_by(cyl) %>% count()
```

<br>

## 9、交并合补

我们可以使用{{< hl-text primary >}}bind_rows、bind_cols{{< /hl-text >}}函数，对两个数据框进行纵向、横向合并。类似于**rbind、cbind**函数，但这两个函数会对行列进行更加严格的检查，所以使用**bind_rows**纵向合并时，可以根据变量名合并数据；而使用**bind_cols**横向合并时，需要两个数据框拥有相同数量的观测值。

```R
> df <- tibble(x = 1:3, y = 3:1)
> df1 <- tibble(x = 4, y = 0)
> df2 <- tibble(z = -1:1, w = 0)
# 纵向合并
> bind_rows(df, df1)
# 横向合并
> bind_cols(df, df2)
```

类似R语言系统函数中对数组进行交并合补，我们也可以使用{{< hl-text primary >}}union、intersect、setdiff{{< /hl-text >}}函数，取得两个数据框的并集、交集、补集。并使用{{< hl-text primary >}}setequal{{< /hl-text >}}函数判断两个数据框是否相同。此外，如果取并集时需要包含重复的观测值，则可以使用{{< hl-text primary >}}union_all{{< /hl-text >}}函数。

{{< image classes="fancybox center" src="https://s2.ax1x.com/2019/12/14/QRBhp4.png" >}}

<br>

## 10、数据框连接

我们可以使用{{< hl-text primary >}}left_join、right_join、inner_join、full_join{{< /hl-text >}}函数，将两个数据框按照一个或多个变量，进行左连接、右连接、内连接、外连接。此时左右两个数据框用于连接的变量名称可以相同，也可以不同，我们可以使用**by**参数指定使用哪些同名变量进行连接，或者左右两个数据框的哪些变量应当一一对应；除此之外如果还包含其它同名变量，则连接后为了区分同名变量，默认会给左边数据框中的同名变量添加**.x**后缀，而给右边的添加**.y**后缀，我们可以使用**suffix**参数修改这一设定。

此外我们还可以使用{{< hl-text primary >}}semi_join、anti_join{{< /hl-text >}}函数，进行半连接、反连接。这两种方式分别与取差集、补集的形式十分类似，但可以通过数据框中的部分变量来决定差集、补集。

{{< image classes="fancybox center" src="https://s2.ax1x.com/2019/12/14/QRBWhF.png" >}}

```R
# 连接时左右数据框用于连接的变量名称相同
> band_members %>% left_join(band_instruments, by = "name")
# 连接时左右数据框用于连接的变量名称不相同
> band_members %>% right_join(band_instruments2, by = c("name" = "artist"))
```

<br>

最后，我们可以通过下面的速记手册，快速了解使用**dplyr**整理数据时的整体框架与各项细节。获取更多速记手册，请前往 [这里](https://rstudio.com/resources/cheatsheets/) 。

{{< image classes="fancybox fig-50" group="dplyr"  src="https" >}}
{{< image classes="fancybox fig-50 clear" group="dplyr" src="https" >}}

<br>

{{< note "思考思考" "#e6e6ff" >}}
- `select(mtcars, -hp, everything())`与`select(mtcars, everything(), -hp)`有何不同？
- 如何使用**dplyr**求7日移动平均？
- 函数**count**与**n**有何区别？

{{< /note >}}

<br>
