---
title: "面向语言的编程——R语言中的命令与命令执行环境"
date: 2019-06-10
categories:
  - R语言
  - 数据类型
tags:
  - R语言数据类型
  - R语言面向语言编程
keywords:
  - R语言
  - 数据类型
  - 面向语言编程
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/SQXVYK02/1.png
---

**面向语言的编程**有时也被称作**元编程**，指的是一种计算机语言以另一种计算机语言（或自身）为**目标语言**，通过处理、执行目标语言来完成某项任务的过程。作为脚本语言的一种，**R语言**也拥有强大且便捷的元编程能力。这篇文章将介绍R语言中元编程的基础——命令与命令执行环境。

<!--more-->

<!-- toc -->

## 1、变量名

R语言中的变量名是一类被称为**symbol**（或者**name**）的对象，变量名本质上是一个字符串，但与字符串不同的是，变量名可以对应一个特定的值。比较特别的是，函数名或者操作符也是变量名的一种，它们的取值是一个特定的函数。对于系统函数名（参考**.Internal**、**.Primitive**帮助文档）而言，其对应的函数存储在变量名对象本身。

我们可以使用{{< hl-text primary >}}as.symbol、as.name{{< /hl-text >}}函数，将一个字符串转化为一个变量名，并使用{{< hl-text primary >}}eval{{< /hl-text >}}函数取出该变量名所对应的值。

```R
> a <- 123; x <- as.symbol("a")
> x         # x的取值是一个变量名
a
> eval(x)   # 将x的取值作为变量名执行
[1] 123
```

<br>

## 2、命令

命令是由字面值、变量名、及子命令构成的指令集，命令可以被解析为**指令树**，指令树的最顶层是需要最后被执行的指令，而最底层是需要最先被执行的指令。

比如`sum(a, 1)`被解析之后，函数**sum**在最顶层，变量名**a**及字面值**1**在最底层，所以命令执行时会先寻找**a**的取值，再将该值与**1**一同作为参数传给**sum**执行。

在R语言中直接输入命令会被立即执行，所以我们需要使用{{< hl-text primary >}}substitute、quote{{< /hl-text >}}等函数捕获未执行的命令，同样命令也可以使用**eval**函数执行。

此外，在R语言中，某些类型的命令拥有特定的称谓：

- **function call**指的是函数调用的命令，我们可以使用{{< hl-text primary >}}call{{< /hl-text >}}函数调用一个函数名与特定字符串相同的函数。

- **formula**指的是含有英文波浪号**～**的命令，常被用于表示数学模型。

```R
> substitute(a + 1)
a + 1
> call("sum", 1, 2)
sum(1, 2)
> y ~ a + b
y ~ a + b
```

<br>

## 3、命令集

expression


## 4、函数

closure/promise

closure
**formals**，**pairlist**参数
**body**，**langsxp**函数体
**env**，命令执行环境

```R
> typeof(.Primitive)
[1] "builtin"
> typeof(.Internal)
[1] "special"
> typeof(mean)
[1] "closure"
```


```R
> delayedAssign("x", {cat("promise 被执行\n"); 1})
> x
promise 被执行
[1] 1
> x
[1] 1
```

promise是表达式+执行环境，参考delayedAssign



## pairlist

**carval**当前值
**cdrval**下一个**pairlist**
**tagval**当前值的标签，即变量名

每个对象的**attributes**属性都是一个**pairlist**

## list

list中的值实际上是存储在**vecsxp**中的，取值的名称存储在**attr(x, "names")**

## 2、enviroment

**命令执行环境**由三部分组成

- **frame**是一个**pairlist**，由变量名和取值组成
- **enclos**是一个**enviroment**，表示上层命令执行环境
- **hashtab**是一个**list**，相当于**frame**的缓存，当某个值被删除时，占用的空间不会被清除，**truelength**即真正分配的列表长度

载入程序包时产生的命令执行环境都是缓存的，而新生城的命令执行环境是非缓存的。

<br>

<br>

{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
