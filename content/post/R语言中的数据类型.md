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

R语言中的底层代码都是由**C/C++**直接实现的，在R语言中所有的对象，无论是数组、列表，还是函数、操作符，本质上都是一个指针（**SEXP**）指向特定的数据（**SEXPREC**类型的结构体，对于**vector**（数组）类型的数据而言则是**VECTOR_SEXPREC**类型的结构体）。

**SEXP**指针指向的结构体由两大部分组成，其中一部分是_头信息_（**SEXPREC_HEADER**），包括一个**sxpinfo**结构体，和三个指向**SEXPREC**类型结构体的指针分别表示数据的属性、上一个、下一个**数据节点**，其作用在于标识数据类型，函数调试、内存管理等。R语言中所有底层数据对象的_头信息_结构都是相同的，因此可以说是_头信息_决定了R语言对象的共性。

**SEXP**的另一部分是_数据_，根据存储内容的不同，_数据_部分的结构也是不同的，比如R语言中**vector**类型的对象基本上都是存储在**vecsxp**结构体中，而**environment**类型的对象则是存储在**envsxp**结构体中。_数据_层面的差异是C语言中数据结构的差异，并不能直接体现在R语言层面。

## 数据的存储类型

在R语言的底层代码中，虽然**SEXP**的_数据_部分，会使用不同的结构体来存储相应的数据对象。但这里的结构体类型并不能作为区分不同数据存储类型的标准，最终决定数据对象会被作为哪种存储类型解读的是**sxpinfo**结构体中的**type**变量。比如R语言中**vector**类型对象的_数据_部分是一个**vecsxp**结构体，而它实际上可以分别存储**RAWSXP、CHARSXP、LGLSXP、INTSXP、REALSXP、CPLXSXP、STRSXP、VECSXP、EXPRSXP、WEAKREFSXP**类型的数据。

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
| "expression"  |	EXPRSXP	    | 19                 | 未执行的命令
| "language"    |	LANGSXP     | 6                  | 未执行的命令
| "promise"     |	PROMSXP     | 5                  | 未执行的命令与命令执行环境
| "closure"     |	CLOSXP	    | 3                  | 函数
| "special"     |	SPECIALSXP  | 7                  | 系统函数或操作号
| "builtin"     |	BUILTINSXP  | 8                  | 系统函数或操作号
| "bytecode"    |	BCODESXP    | 21                 | 字节码，用于寻找已编译生成的C语言函数
| "externalptr" |	EXTPTRSXP   | 22                 | 外部引用指针
| "weakref"     | WEAKREFSXP  | 23                 | 弱引用，用于内存管理
| (char *)NULL  | -1	        |                    | 无效type，TYPEOF返回-1，typeof返回空值

在以上表格中，某些存储类型是仅用于C语言层面的，还有些存储类型基本上可以对等（比如**symbol**与**name**）。所以R语言中定义了{{< hl-text primary >}}storage.mode、mode{{< /hl-text >}}等函数来精简**typeof**的输出，使用这些函数对我们而言更有意义的信息，比如| "closure"、 "special"、"builtin"类型的数据，在我们看来都是函数，所以**storage.mode、mode**会将它们归类为"function"。

## 数据的属性

我们已经知道，R语言中所有对象的_头信息_中都包含一个**attrib**指针用于表示数据的属性。数据的属性必须是一个**key-value**型的集合。我们可以使用{{< hl-text primary >}}attr(x, name){{< /hl-text >}}的形式，获取对象**x**的某个属性，也可以通过{{< hl-text primary >}}attribute{{< /hl-text >}}获取**x**的全部属性。

当然我们可以给对象设置任意属性，但某些属性（{{< hl-text primary >}}class、comment、dim、dimnames、names、row.names、tsp、levels{{< /hl-text >}}）拥有特殊的意义，它们甚至可以直接决定对象在R语言层面会以怎样的数据结构解读。这些属性除了可以通过**attr**函数获取，也可以直接通过相应的命令获取（比如class属性可以通过**class**函数获取）。

### class属性

class属性可以直接影响到数据的存储类型，比如下面的代码中，我们将一个整数数组**x**的class属性设置为"character"，可以看出**x**的存储类型也发生了相应的变化。因此我们可以直接通过修改数据的class属性来实现数据类型的转化。

```R
> x <- 1:10
> c(typeof(x), typeof(class(x) <- "character"))
[1] "integer"   "character"
```

class属性最主要的功能，是被用于**S3**类型函数的函数分发。比如下面的代码中，首先我们定义了一个**S3**类型的函数**f**，并为它指定了两个分发函数可以分别作用于class属性为**classA、classB**的对象。接下来我们调用{{< hl-text primary >}}structure{{< /hl-text >}}函数构建了一个class属性为**classA**的空列表，并对直接其使用**f**函数，可以看出**f.classA**被成功执行。数据的class属性也可以包含多个值，此时的数据可以分别从不同的**S3**函数中获得方法，比如最后一行代脉中我们构建了一个class属性既是"list"，又是"classB"的对象，可以看出**f**函数对其依然适用。

```R
> f <- function(x)UseMethod("f", x)
> f.classA <- function(x)print("f.classA executed !")
> f.classB <- function(x)print("f.classB executed !")
> f(structure(list(), class = "classA"))
[1] "f.classA executed !"
> f(structure(list(), class = c("list", "classB")))
[1] "f.classB executed !"
```

### dim属性

数据的dim属性决定了数据的维度。在R语言中，我们经常会使用到**matrix、data.frame**类型的数据，但是R语言的底层存储结构中并没有这些类型，因为它们的存储类型与**vector、list**类型的数据是一致的，这些数据类型之间很重要的一个区别就是dim属性。比如以下命令中我们生成了一个数组，将其dim属性修改为`c(2, 5)`之后，数组就被自动转化为了矩阵。

```R
> x <- 1:10
> dim(x) <- c(2, 5); x
     [,1] [,2] [,3] [,4] [,5]
[1,]    1    3    5    7    9
[2,]    2    4    6    8   10
```

下表我们按照维度与存储内容是同质数组（所有元素的数据类型必须相同），或异质数组（可以存储不同类型的元素），对这些数据结构做了一个区分。注意在R语言中，单维数据是没有dim属性的。此外原子类数据（**atomic**）一般指的是："logical"、"integer"、"numeric"、"complex"、"character"、 "raw"、 NULL等类型的数据。

|      | 同质数组       | 异质数组   |
|:----:|----------------|------------|
| 单维 | atomic vector  | list       |
| 二维 | matrix 	      | data.frame |
| 高纬 | array	        |            |

### names、row.names、dimnames

### levels属性

### tsp属性

### comment属性

## 数据的长度 length、lengths


## 数据的内存占用 object.size

<br>

{{< note "思考思考" "#e6e6ff" >}}
- `Sys.Date()`的存储类型是什么？
- **vector**类型的数据包含哪些存储类型？
- **factor**类型的数据是如何在数值与字符串之间转换的？
{{< /note >}}

<br>
