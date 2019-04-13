---
title: "使用R语言对数字进行数学运算"
date: 2019-04-03
lastmod: 2019-04-05
math: true
categories:
  - R语言
  - 数学运算
tags:
  - R语言数学运算
keywords:
  - R语言
  - 数学运算
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/xC6s1DJ7/R.png
---

**R语言**作为一门专为统计分析诞生的语言，数学运算自然是必不可少的。这篇文章将介绍R语言是如何对**数字**进行数学运算的。
<!--more-->

<!-- toc -->

<br>

# 1、什么是数字类型的对象  

我们这里说的数字类型的对象，指的是以单个数值的形式存储的对象，而非以更高级的数据形式（数组、矩阵等）存储的数值，它可以是一个整数、小数、分数、虚数、……。严格意义上来讲，R语言中并不存在这样的数据对象，因为R语言会以数组的形式存储这类对象，但这并不影响我们对数字进行数学运算。

> Note that R has no 0-dimensional, or scalar types. Individual numbers or strings, which you might think would be scalars, are actually vectors of length one.
>   -- Hadley Wickham

<br>

# 2、对数字进行数学运算

## 2.1、加减乘除

首先是最基本的加减乘除，R语言中分别定义了对应的运算符`+、-、*、/`，我们可以像写算式一样操作这些运算符。这些运算符除了可以计算数字，还可以对一些其它类型的对象进行运算，这一点我会在之后的文章中详细分析。

<br>

## 2.2、指数与对数运算

R语言中定义了符号`^`用于指数运算，我们可以使用`^`求一个数值的任意次方，或开任意次方。同时当我们需要求平方根时，还可以使用便捷函数`sqrt`。

$$ a \text{^} b = a ^ b, \quad a \text{^} (b / c) = \sqrt [c] {a ^ b} , \quad sqrt(x) = \sqrt x$$

在指数与对数运算的过程中，有时候我们会用到自然对数底`e`，R语言中并没有使用{{< hl-text red >}}初始变量{{< /hl-text >}}的形式来存储`e`的值，但是R语言中定义了一个`exp`函数用以对`e`进行指数运算，我们可以使用`exp(1)`来代替`e`。

$$ exp(1) = e, \quad exp(x) = e ^ x $$

我们可以使用`log(x, base)`的形式进行对数运算，当指定一个数值给`base`时，将会计算出以`base`为底数，`x`的对数。如果我们使用`log(x)`的形式，则可以直接计算出以`e`为底数，`x`的对数。同时R语言中还定义了两个快捷函数`log2、log10`，可以分别计算出以2、10为底数，`x`的对数。

$$ log(x, base) = \log _{base} x, \quad log(x) = \ln x, \quad log2(x) = \log _2 x, \quad log10(x) = \log _{10} x $$

对于自然对数底`e`，R语言中还定义了两个特殊的函数`log1p、expm1`，可以简便某些情况下的数学运算。

$$ log1p(x) = \ln (1 + x), \quad expm1(x) = e ^ x - 1 $$

<br>

## 2.3、三角函数与双曲函数

在R语言中，分别定义了`sin、cos、tan`用以计算某个**弧度**的正弦值、余弦值、正切值, 定义了`asin、acos、atan`计算正弦值、余弦值、正切值对应的弧度, 同时我们还可以使用`atan2(y, x)`来求解**四象限的反正切值**（即在二维坐标系内，由原点到指定`(x, y)`点组成的向量，与**x轴的正方向**之间的夹角弧度）。

有些时候我们需要计算**角度**而非弧度，R语言中无法直接输入角度，但是R语言中定义了一个{{< hl-text red >}}初始变量{{< /hl-text >}}`pi`， 因为}$ pi \approx \pi = 180 ^ 。 $, 所以我们可以使用`n /180 * pi`的形式来代表角度（其中`n`即角度对应的数值）。为了方便运算，R语言中还定义了`sinpi, cospi, tanpi`三个函数，可以直接输入`n /180`来计算角度的正弦值、余弦值、正切值。

$$ sinpi(x) = sin(\pi * x), \quad cospi(x) = cos(\pi * x), \quad tanpi(x) = tan(\pi * x) $$

对于双曲函数，我们可以分别使用`sinh、cosh、tanh`，计算双曲正弦值、双曲余弦值、双曲正切值，分别使用`asinh、acosh、atanh`，计算反双曲正弦值、反双曲余弦值、反双曲正切值。

$$ sinh(x) = \frac {e^x - e^{-x}} 2, \quad cosh(x) = \frac {e^x + e^{-x}} 2, \quad tanh(x) = \frac {e^x - e^{-x}} {e^x + e^{-x}} $$

<br>

## 2.4、取整、取余数、取正负号、取绝对值

在R语言中，我们可以分别使用`%%`、`%/%`、`sign`、`abs`·，来取整、取余数、取正负号、取绝对值。

$$ 7 \%\% 2 = 1, \quad 7 \%/\% 2 = 3, \quad sign(-7) = -1, \quad abs(-7) = 7  $$

对于小数而言，我们可以分别使用`ceiling(x)`、`floor(x)`、`round(x, n)`的形式，实现向上取整、向下取整、四舍五入取`n`位小数。

$$ floor(1.2345) = 1, \quad ceiling(1.2345) = 2, \quad round(1.2345, 2) = 1.23, \quad round(1.2345, 3) = 1.235  $$

此外我们还可以分别使用`trunc(x)`、`signif(x, n)`的形式，实现按绝对值向下取整、四舍五入取`n`位数字。

$$ trunc(1.5) = 1, \quad trunc(-1.5) = -1, \quad signif(1.2345, 3) = 1.23  $$

<br>

## 2.5、复数运算

在R语言中，可以使用数字加字母`i`的形式来表示复数，比如`1 + 1i`。我们可以分别使用`Re、Im、Mod, Arg, Conj`，来取复数的实部、虚部、模、弧度、共轭复数。

$$ re(2 + 1i) = 2, \quad Im(2 + 1i) = 1, \quad Mod(2 + 1i) = \sqrt 5, \quad Arg(1 + 1i) = \frac {\pi} 2 \quad Conj(2 + 1i) = 2 - 1i $$

复数也可以进行加减乘除、求指数、求对数、求三角函数等运算，不同的运算方式拥有不同的实际意义。

<br>

## 2.6、求阶乘、排列组合、beta函数、gamma函数

我们可以通过`factorial(x)`求`x`的阶乘，通过`choose(n, k)`的形式，求从`n`个样本中随机抽取`k`个有多少种不同的组合。

$$ factorial(x) = x! \quad choose(n, k) = \frac {n!} {k!(n-k)!} $$

我们还可以分别通过`gamma、digamma、trigamma`，来计算相应的gamma函数、gamma函数的一阶导数、amma函数的二阶导数， 通过`psigamma(x, deriv = 0)`来计算更高阶的gamma函数的导数，通过`beta(a, b)`来计算beta函数。

$$  gamma(x) = (x - 1)! \quad beta (a, b) = \gamma (a) * \gamma (b) / \gamma (a + b) $$

此外，R语言中还定义了一系列的快捷函数`lchoose、lfactorial、lgamma、lbeta`，可以分别求解`choose、factorial、gamma、beta`的对数。

<br>

# 3、结语

关于R语言中对数字进行数学运算的介绍到此就算结束了，其中一定有未概括或总结不当的地方，以后再作修改吧。下一篇我将介绍如何在R语言中对**数组**类型的对象进行数学运算。

{{< note "思考思考" "#e6e6ff" >}}
- 如何实现角度与弧度相互转换？
- 如何按绝对值向上取整？
- 如何求从`n`个样本中随机抽取`k`个有多少种不同的排列？
{{< /note >}}

<br>
