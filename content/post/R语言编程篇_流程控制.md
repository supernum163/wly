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

在介绍**判断语句**之前，我们需要了解R语言中的逻辑判断规则。R语言中可以产生逻辑型运算结果的操作符包括**比较操作符**、**逻辑操作符**等，其中：

- 比较操作符，{{< hl-text primary >}}<、>、<=、>=、==、!={{< /hl-text >}}分别表示：小于、大于、小于等于、大于等于、等于、不等于。其不仅可以比较数值型数据的大小，还可以根据字符编码比较字符串。

- 逻辑操作符，{{< hl-text primary >}}&、|、!{{< /hl-text >}}分别表示：与、或、非，{{< hl-text primary >}}&&、||{{< /hl-text >}}分别表示短路与、短路或，与`&、|`不同的是，当前一个表达式的值已经可以确定运算结果时，另一个表达式便不会被计算。R语言中没有表示**异或**的操作符，但是我们可以使用函数{{< hl-text primary >}}xor{{< /hl-text >}}替代。

```R
# 字符串比较大小，字符a的编码比字符b小
> "a" < "b"
[1] TRUE

# 短路与判断，("a" - 1)不会被执行
> FALSE && ("a" - 1)
[1] FALSE
```


我们在 [R语言中的数值](../../05/r语言中的数值)里介绍过R语言中数值与逻辑值之间的关系。简单来说，数值**0、1**可以与逻辑值相等，但不相同（数据类型不同）。关于这一点我们可以分别使用**==**操作符，与{{< hl-text primary >}}identical{{< /hl-text >}}函数进行判断。

如果我们不希望数值型数据被用作逻辑判断，则可以使用{{< hl-text primary >}}isTRUE、isFALSE{{< /hl-text >}}函数严格判断数据对象是否为**TRUE、FALSE**。

```R
# 数值1与逻辑值TRUE相等，但既不不等同于TRUE，也不等同于FALSE
> c(1 == TRUE, identical(1, TRUE), isTRUE(1), isFALSE(1))
[1]  TRUE FALSE FALSE FALSE
```

如果我们有一个逻辑值数组（或者生成逻辑值数组的表达式），需要判断数组中各元素是否**全部为真**或者**至少有一个为真**，则可以分别使用{{< hl-text primary >}}all、any{{< /hl-text >}}函数。

```R
# 数组中的元素全为真，则判断为真
> all(1:10 > 0)
[1] TRUE

# 数组中的元素只要有一个为真，就判断为真
> any(-1:1 == 1:-1)
[1] TRUE
```

此外，R语言中还有大量可以生成逻辑值的函数：判断数据类型的{{< hl-text blue >}}is.*{{< /hl-text >}}家族函数；强制将数据对象转换为逻辑值的{{< hl-text primary >}}as.logical{{< /hl-text >}}函数；以及某些看似不返回任何信息，实际上以逻辑值的形式返回是否执行成功的函数，比如{{< hl-text primary >}}require{{< /hl-text >}}函数；……

<br>

## 2、判断语句

R语言中{{< hl-text primary >}}if...else...{{< /hl-text >}}式的**判断语句**具有以下格式：首先在**if**子语句中判断**cond**为真，则执行**expr**并结束，否则进入**else if**子语句（可以有多条）进行判断-执行操作，若以上判断结果都为假，则执行**else**语句中的**expr**。注意这里的**else if**及**else**子语句都可以省略，所以我们也可以使用**if(cond) expr**的句式，表示满足某一条件则执行代码，否则什么也不做。

实际使用的过程中我们可能会经常用到**if(cond) expr else expr**的句式，表示满足某一条件则执行一段代码，否则执行另一段代码。为此R语言中定义了一个便捷函数{{< hl-text primary >}}ifelse{{< /hl-text >}}，其参数列表中的**yes**表示**cond**为真时需要执行的代码，**no**表示**cond**为假时需要执行的代码。

```R
if(cond) expr else if(cond) expr ... else expr
ifelse(cond, yes, no)
```

<br>

## 3、分支语句

**分支语句**完全可以使用上文介绍的条件语句替代，但条件语句每次判断只能处理表达式的两种状态，如果表达式可以对应多种状态，使用{{< hl-text primary >}}switch{{< /hl-text >}}函数可以使代码更加简洁。

**switch**函数有两种使用方式，取决于其第一个参数**EXPR**对应的值是数值还是字符串。若**EXPR**是一个数值，则返回**EXPR**之后的参数列表中相应位置上的值。若**EXPR**是一个字符串，则返回**EXPR**之后的参数列表中相应参数的值，此时我们可以不给某个分支指定对应的值，表示该分支对应的值与下一个分支相同（**合并分支**）；还可以提供一个无名参数作为**缺省值**。

```R
# EXPR对应的值为数字
switch(EXPR, expr1, expr2, expr3, ...)

# EXPR对应的值为字符串
switch(EXPR, 
  case1 = ,
  case2 = expr2,
  case1 = expr3,
  ...
  default
)
```

当我们不考虑合并分支及缺省值时，也可以使用从数组中筛选元素的形式实现分支语句：

```R
c(value1, value2, value3, ...)[EXPR]
c(case1 = value1, case2 = value2, case1 = value3, ...)[EXPR]
```

<br>

## 4、循环语句

R语言中**循环语句**的使用方式如下，需要注意的地方在于：

- **in**关键字只能用于{{< hl-text primary >}}for{{< /hl-text >}}循环中的**循环判断条件**，表示**var**将遍历**seq**（数组或列表）中的每一个元素，我们可以在**函数体**（**expr**）中调用**var**的值，也可以不掉用，循环次数取决于**seq**的长度。

- 对于{{< hl-text primary >}}while{{< /hl-text >}}循环，只要**cond**为真，就执行**expr**。如果**cond**是一个命令或变量，我们可以在函数体中操作其中的变量，从而达到控制循环过程的目的。

- 有时候我们会用到`while(TRUE) expr`的循环句式，通过函数体控制循环过程，而非通过循环判断条件。R语言中的{{< hl-text primary >}}repeat{{< /hl-text >}}函数，就是为了便利这种句式而设计的。

```R
for(var in seq) expr
while(cond) expr
repeat expr
```

为了在循环体内控制循环过程，我们可以使用{{< hl-text primary >}}break、next{{< /hl-text >}}函数，实现结束循环、进入下一次循环。这两个函数同时也是R语言中的关键字（参考`Reserved`帮助文档），所以使用时以调用函数的方式，或者以调用变量的方式是一样的。

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 如何用`if...else...`实现`goto`类型的语句？
- `case...when...`类型的分支语句与`switch`的本质区别是什么？
- R语言中如何实现`do...while...`循环？

{{< /note >}}

<br>
