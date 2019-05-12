---
title: "R语言中的数据类型"
date: 2019-05-09
categories:
  - R语言
  - 数据类型
tags:
  - R语言数据类型
keywords:
  - R语言
  - 数据类型
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/fbdrXS6P/R.png
---

在**R语言**中一切皆为**对象**，不同类型的对象，其表现形式却又千差万别。对于一个新手来讲，理清R语言中不同对象的区别与关联确实不易。这篇文章及后续系列将深入剖析R语言中的对象。
<!--more-->

<!-- toc -->

R语言中的底层代码都是由**C/C++**直接实现的，在R语言中所有的对象，无论是数组、列表，还是函数、操作符，本质上都是一个指针（**SEXP**）指向特定的数据（**SEXPREC**结构体）。

**SEXPREC**结构体由两大部分组成，其中一部分是_头信息_（**SEXPREC_HEADER**），包括一个**sxpinfo**结构体，和三个指向**SEXPREC**对象的指针分别表示数据的属性、上一个、下一个**数据节点**，其作用在于标识数据类型，函数调试、内存管理等。R语言中所有底层数据对象的_头信息_结构都是相同的，因此可以说是_头信息_决定了R语言对象的共性。

**SEXPREC**结构体的另一部分是由联合体**u**组成的_数据_，根据存储内容的不同，_数据_部分的结构也是不同的，比如R语言中**scalar**类型的对象基本上都是存储在**listsxp**结构体中，而**environment**类型的对象则是存储在**envsxp**结构体中。_数据_层面的差异是C语言中数据结构的差异，并不能直接体现在R语言层面。

## 存储类型与数据结构

在R语言的底层代码中，虽然**SEXP**的_数据_部分**u**，会使用不同的结构体来存储相应的数据对象。但**u**的结构体类型并不能作为区分不同数据存储类型的标准，最终决定数据对象会被作为哪种存储类型解读的是**sxpinfo**结构体中的**type**变量。

在。在R语言中，我们可以使用{{< hl-text primary >}}typeof{{< /hl-text >}}来查看底层数据的存储类型，**typeof**是对C语言中{{< hl-text primary >}}TYPEOF{{< /hl-text >}}函数的包裹，**TYPEOF**可以直接获取**sxpinfo**结构体中**type**所对应的数值，而**typeof**则会以文本的形式输出这个数值所对应的含义。以下是这两个函数输出结果的对照表：

|  R语言typeof  | C语言TYPEOF | TYPEOF实际对应的值 | 解释说明 
|:-------------:|-------------|--------------------|------------------
| "NULL"        | NILSXP      | 0                  | NULL值
| "char"        | CHARSXP 	  | 9                  | 字符串，仅用于C语言层面
| "character"   |	STRSXP	    | 16                 | 字符串数组
| "logical"     |	LGLSXP      | 10                 | 逻辑值数组
| "integer"     |	INTSXP      | 13                 | 整数数组
| "double"      | REALSXP	    | 14                 | 浮点型数组
| "numeric"     |	REALSXP	    |                    | 浮点型数组
| "complex"     |	CPLXSXP	    | 15                 | 复数数组
| "raw"         | RAWSXP      | 24                 | 二进制数组
| "list"        | VECSXP      | 20                 | 列表
| "pairlist"    |	LISTSXP	    | 2                  | 列表
| "S4"          | S4SXP       | 25                 | S4对象
| "any"         | ANYSXP	    | 18                 | 任意类型的数组
| "..."         | DOTSXP	    | 17                 | 不定长数组，仅用于函数
| "environment" |	ENVSXP      | 4                  | 命令执行环境
| "symbol"      | SYMSXP      | 1                  | 变量名
| "name"        | SYMSXP	    |                    | 变量名
| "expression"  |	EXPRSXP	    | 19                 | 未执行的公式
| "language"    |	LANGSXP     | 6                  | 未执行的命令
| "promise"     |	PROMSXP     | 5                  | 未执行的命令
| "closure"     |	CLOSXP	    | 3                  | 函数
| "special"     |	SPECIALSXP  | 7                  | 系统函数或操作号
| "builtin"     |	BUILTINSXP  | 8                  | 系统函数或操作号
| "bytecode"    |	BCODESXP    | 21                 | 字节码，用于寻找已编译生成的C语言函数
| "externalptr" |	EXTPTRSXP   | 22                 | 外部引用指针
| "weakref"     | WEAKREFSXP  | 23                 | 弱引用，用于内存管理
| (char *)NULL  | -1	        |                    | 无效type，TYPEOF返回-1，typeof返回空值

在以上表格中，某些存储类型是仅用于C语言层面的，还有些存储类型基本上可以对等（比如**symbol**与**name**）。所以R语言中定义了{{< hl-text primary >}}storage.mode、mode{{< /hl-text >}}等函数来精简**typeof**的输出，使用这些函数对我们而言更有意义的信息，比如| "closure"、 "special"、"builtin"类型的数据，在我们看来都是函数，所以**storage.mode、mode**会将它们归类为"function"。

## 数据的属性

### attr、attribute

### class

### dim

### names、row.names、col.names、dimnames

### level

### comment

## 数据的长度 length、lengths


## 数据的内存占用 object.size

<br>

{{< note "思考思考" "#e6e6ff" >}}
- `Sys.Date()`的存储类型是什么？
- **vector**类型的数据包含哪些存储类型？
- **factor**类型的数据是如何在数值与字符串之间转换的？
{{< /note >}}

<br>
