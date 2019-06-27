---
title: "R语言编程篇——流程控制"
date: 2019-07-03
categories:
  - R语言
  - 编程
tags:
  - R语言编程
keywords:
  - R语言
  - 流程控制
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/Y9XvNgPJ/image.png
---

判断、循环等**流程控制**过程是编程语言必不可少的一部分，对于不同的编程语言，流程控制的设计理念往往是类似的，但流程控制的具体使用方式可能会稍有不同。这篇文章我们将总结R语言中的流程控制技巧。

<!--more-->

<!-- toc -->

## 1、逻辑判断

在介绍**判断语句**之前，我们需要了解R语言中的逻辑判断规则。R语言中可以产生逻辑型运算结果的**函数**包括**比较操作符**、**逻辑操作符**等，其中：

- 比较操作符，{{< hl-text primary >}}<、>、<=、>=、==、!={{< /hl-text >}}分别表示：小于、大于、小于等于、大于等于、等于、不等于。其不仅可以比较数值型数据的大小，还可以根据字符编码比较字符串。

- 逻辑操作符，{{< hl-text primary >}}&、|、!{{< /hl-text >}}分别表示：与、或、非，{{< hl-text primary >}}&&、||{{< /hl-text >}}分别表示短路与、短路或，与`&、|`不同的是，当前一个表达式的值已经可以确定运算结果时，另一个表达式便不会被计算。R语言中没有表示**异或**的操作符，但是我们可以使用函数{{< hl-text primary >}}xor{{< /hl-text >}}替代。

我们在 [R语言中的数值](../../05/r语言中的数值)里介绍过R语言中数值与逻辑值之间的关系，如果我们不希望数值型数据被用作逻辑判断，则可以使用{{< hl-text primary >}}isTRUE、isFALSE{{< /hl-text >}}函数严格判断数据对象是否为**TRUE、FALSE**。

```R
# 字符串比较大小，字符a的编码比字符b小
> "a" < "b"
[1] TRUE
# 短路或判断，(b <- FALSE)不会被执行
(a <- TRUE) || (b <- FALSE)
# 严格判断真假，数值1可以被当作TRUE，但不等同于TRUE
> c(isTRUE(1), isFALSE(1))
[1] FALSE FALSE
```

<br>

## 2、判断语句

```R
if(cond) expr else if(cond) expr ... else expr
ifelse(cond, TRUE_expr, False_expr)
```

## 3、分支语句

switch

## 4、循环语句

for(var in seq) expr
while(cond) expr
repeat expr
break
next


<br>


{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
