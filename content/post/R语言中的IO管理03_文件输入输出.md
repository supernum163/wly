---
title: R语言中的文件输入输出
date: 2019-09-23
categories:
  - R语言
  - IO管理
tags:
  - R语言IO管理
keywords:
  - R语言
  - IO管理
  - 文件输入输出
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/09/28/uQEJ1J.png
---

文件输入输出是一门计算机语言从存储设备中获取数据、将内存中的数据持久化的过程。这篇文章我们将介绍R语言中的文件输入输出。

<!--more-->

<!-- toc -->

## 1、二进制文件

我们可以分别使用{{< hl-text primary >}}readBin、writeBin{{< /hl-text >}}函数读写二进制文件。本质上所有文件都是以二进制的形式存储的，所以我们可以使用二进制的模式读写任意文件，但实际上大部分文件都需要按照特定的规则存储数据，如果不遵守相应的规则，读取到的内容对我们而言可能是没有意义的，写出的文件可能是无效的。

```R
readBin(con, what, n = 1L, size = NA_integer_, signed = TRUE, endian = .Platform$endian)
writeBin(object, con, size = NA_integer_, endian = .Platform$endian, useBytes = FALSE)
```

- **con**即需要被读写的文件资源链接或文件名
- **object**即需要被写入文件的二进制对象
- **what**即读取的内容需要被转化为哪种类型的R语言对象，可以是**numeric、double、integer、int、logical、complex、character、raw**
- **n**即需要从文件中读取多少个特定R语言对象的元素，**n**的值可以超出文件中能被读取的最大元素个数，此时以最大元素个数为准
- **size**即读写每个R语言元素需要对应多少个字节
- **signed**即读取到1至2个字节的整数时，是否认为该整数是带正负号的
- **endian**即字节存储次序，默认与系统设定相同。小端格式的子节序(**Little-endian**)会将低序字节存储在起始地址（**低位编址**）。与之相反的，大端格式的子节序(**Big-endian**)会将高序字节存储在起始地址（**高位编址**）。
- **useBytes**即是否以字节的形式读写字符串，如果`useBytes = FALSE`且R语言的系统编码与文件链接的编码不同，则读写字符串时会进行转码操作

<br>

我们可以分别{{< hl-text primary >}}readChar、writeChar{{< /hl-text >}}函数，从二进制文件（当然我们也可以将纯文本文件以二进制的模式打开）中读写字符串。

```R
readChar(con, nchars, useBytes = FALSE)
writeChar(object, con, nchars = nchar(object, type = "chars"), eos = "", useBytes = FALSE)
```

- **nchar**即需要读写多少个字符，注意一个字符可能对应多个字节
- **eos**即在每个字符串写入结束时，需要向文件中写入的字符串结束标志符），默认为空字符，取值为**NULL**时表示不写入字符串结束标志符

<br>

## 2、纯文本文件

纯文本文件是以单个字符为单位存储的文件，但某些字符在文本文件中拥有特定的含义（参考下表）。注意**空字符**（**\x00**）与**空白字符**（**\x20**）不同。

| 简称      | 全称            | 对应字符          | 解释说明
|:----------|:----------------|:------------------|:-------------------
| EOS       | End Of String   | **\x00**          | 字符串结束标志符
| EOL       | End Of Line     | **\r、\n、\r\n**  | 行结束标志符
| EOF       | End Of File     |                   | 文件结束标志符

我们可以分别{{< hl-text primary >}}readLines、writeLines{{< /hl-text >}}函数从纯文本文件中按行读写数据。这两个函数也可以读写标准输入，此时**readLines**与R语言中的{{< hl-text primary >}}readline{{< /hl-text >}}函数的功能十分类似。仅有的区别在于：**readline**可以临时修改命令提示符，从标准输入中读取一行内容；**readLines**不能临时修改命令提示符，需要自行提供读取多少行。
注意如果使用**readLines**读取标准输入时，指定了读取全部内容（`n = -1`），需要使用快捷键**Ctrl+D**输入文件结束标志符。

```R
readLines(con = stdin(), n = -1L, ok = TRUE, warn = TRUE, encoding = "unknown", skipNul = FALSE)
writeLines(text, con = stdout(), sep = "\n", useBytes = FALSE)
```

- **text**即需要被写入文件的字符串
- **n**即需要从文件中读取多少行内容，取值为负数时表示读取全部内容
- **ok**即是否允许实际行数小于需要读取的行数（**n**），取值为**FALSE**时会触发异常，并且不读取任何内容
- **warn**即是否显示警告信息（文件不存在、找不到行结束标志符、文件中含有空字符）
- **encoding**即标记文件中的字符编码，但不进行字符转码，参考**Encoding**函数
- **sep**即需要在一行结束时向文件中写入的行结束标志符（比如**\n、\r\n**）
- **skipNul**即是否忽略字符串中的空字符

<br>

## 3、纯文本表格类文件

R语言中的{{< hl-text primary >}}scan{{< /hl-text >}}函数可以按行读取文件，并且可以按照特定的分割符将每行中的内容切分成不同的元素，这对于读取表格类数据文件十分有帮助，下文介绍的**read.table**就调用了这一函数。

```R
scan(file = "", what = double(), nmax = -1, n = -1, sep = "",
     quote = if(identical(sep, "\n")) "" else "'\"", dec = ".",
     skip = 0, nlines = 0, na.strings = "NA",
     flush = FALSE, fill = FALSE, strip.white = FALSE,
     quiet = FALSE, blank.lines.skip = TRUE, multi.line = TRUE,
     comment.char = "", allowEscapes = FALSE,
     fileEncoding = "", encoding = "unknown", text, skipNul = FALSE)
```

- **file**即需要被读写的文件资源链接或文件名，空字符或字符串**stdin**可以表示系统输入
- **what**即需要读取的内容需要被转化为哪种类型的R语言对象，与读写二进制文件时的**what**参数类似，但这里的**what**参数还可以取值为`list(...)`，文件每一行被分割符（参考**sep**）分开的内容，会从左至右逐一转化为列表中相应类型的元素
- **nmax**或**n**即需要从文件中读取多少个特定R语言对象的元素，空值或非法值表示读取文件中的所有内容
- **sep**即文件中分别不同内容分割符（只能由单个字符构成），每一个被分割开的内容都可以转化为R语言中的一个元素，默认分割符为空格
- **quote**即文件中用于标识字符串类内容的左右引号（只能由单个字符构成），这些引号不会作为字符串的一部分转化为R语言对象
- **dec**即文件中数值类内容的小数点（只能由单个字符构成）
- **skip**即读取文件内容之前需要先跳过多少行
- **nlines**即最多从文件中读取多少行内容
- **na.strings**即文件中的哪些字符串对应R语言中的**NA**，空字符在数值类对象中默认为**NA**
- **flush**即读取完特定数量的对象后，是否将读写指针置于当前行某尾。这样可以允许在行尾添加注释，而不至于影响到该行各元素的位置
- **fill**即每行读取不足指定个数的元素时，是否加入空值
- **strip.white**即是否删除文件中字符串类内容的前后空格，但**quote**字符内的空格不会被删除，而且只有在指定了**sep**时才有效。其长度可以为1，表示删除所有字符串类内容的前后空格，也可以与**whar**对应，表示删除特定**字段**中的前后空格
- **quiet**即是否不打印读取统计信息，若取值为**FALSE**，**scan**函数会在返回读取结果之前，打印读取到了多少条内容（R语言特定对象的元素）。
- **blank.lines.skip**即读取时是否略过空行，但并不影响行数的计算，不影响**skip、nlines**参数
- **multi.line**即如果一行内读取不到指定数量的元素（一条**记录**），是否从接着下一行读取。只在**what**的取值类型为**list**，且**fill**取值为**FALSE**时有效。默认一条记录只能在同一行，但一行中可以有多条记录
- **comment.char**即行注释标识字符（只能由单个字符构成），比如R语言中的**#**，同一行中该字符及之后的内容会被忽略，除非该字符处于字符串引号内，也可以使用空字符关闭这项功能
- **allowEscapes**即是否对转义字符进行转义，若取值为**FALSE**则**\**会被当作普通字符而非转义符使用。注意这里可以转义**控制字符**（比如**\a、\b、\f、\n、\r、\t、\v**）、**八进制**或**十六进制**字符（比如**\040、\0x2A**），**unicode**字符（比如**\u6211**）不会被转义，其它字符被转义后还是字符本身。**\t、\n**如果不在字符串引号内，可能会被用作分割、换行
- **fileEncoding**即文件的编码方式，决定了**scan**函数以何种方式对文件中的内容进行转码
- **text**即需要从中读取内容的字符串或字符串资源链接，仅当**file**未被指定时有效

<br>

我们可以使用{{< hl-text primary >}}read.table、write.table{{< /hl-text >}}函数，将从文件中读写表格类数据。这两个函数可以读写形式（行分割符、字段分割符）各异的表格文件，因此以下介绍到的读写特定格式（**CSV、TSV、FWF**等）表格文件的函数，本质上都是按照特定格式调用这两个函数读写数据的。

```R
read.table(file, header = FALSE, sep = "", quote = "\"'",
           dec = ".", numerals = c("allow.loss", "warn.loss", "no.loss"),
           row.names, col.names, as.is = !stringsAsFactors,
           na.strings = "NA", colClasses = NA, nrows = -1,
           skip = 0, check.names = TRUE, fill = !blank.lines.skip,
           strip.white = FALSE, blank.lines.skip = TRUE,
           comment.char = "#",
           allowEscapes = FALSE, flush = FALSE,
           stringsAsFactors = default.stringsAsFactors(),
           fileEncoding = "", encoding = "unknown", text, skipNul = FALSE)
```

- **header**即是否将文件第一行最为标题行（列名），默认如果首行元素个数比其它行少一个，则将其设为标题行
- **numerals**即将文件中的数值转化为R语言对象（双精度浮点型）时是否允许精度损失，以及损失精度时是否触发异常
- **row.names**即表格的行名，可以是与行数相同的字符串数组，也可以是一个数值或字符串，指明将表格中的哪一列作为行名。如果首行元素个数比其它行少一个，则其它行中每行的首个元素作为行名。默认或设置`row.names = NULL`，表示使用 *行位序数* （从1开始自动编号的数字）作为行名
- **col.names**即表格的列名，可以是与列数相同的字符串数组，默认使用以**V**开头的 *列位序数* 作为列名
- **as.is**即哪些列不能被转化为因子型对象，可以是与列数相同的逻辑值数组，也可以是一个数值或字符串数组，指明哪些列不能被转化，注意文件中的行名或者读取是跳过的列都会被算作单独的一列
- **colClasses**即表格中的每一列分别需要被转化为什么类型的对象，可以是与列数相同的字符串数组；也可以是**NA**，表示使用默认的转化方式（参考**type.convert**）；还可以是**NULL**，表示略过某一行不读
- **check.names**即是否检查表格列名的合法性，若取值为**TRUE**，则列名重复时以数字后缀区分
- **stringsAsFactors**即是否将字符串转化为因子，可以被**as.is、colClasses**的设定覆盖

```R
write.table(x, file = "", append = FALSE, quote = TRUE, sep = " ",
            eol = "\n", na = "NA", dec = ".", row.names = TRUE,
            col.names = TRUE, qmethod = c("escape", "double"),
            fileEncoding = "")
```

- **append**即是否将输出结果附加到文件中，只有当**file**为文件名时有效
- **qmethod**即以何种方式处理字符串中的英文引号，**escape**表示进行字符转义，**double**表示用两个引号代替单个引号
- **eol**即需要在一行结束时向文件中写入的行结束标志符
- **na**即写出时以什么样的字符串表示R语言中的缺失值
- **row.names、col.names**即是否将行名、列名写入文件

<br>

与**write.table**相似的是{{< hl-text primary >}}write{{< /hl-text >}}函数，**write**函数本质上相当于调用了{{< hl-text primary >}}cat{{< /hl-text >}}函数，可以将R语言对象（通常是矩阵）写入文件，但只能写出数据部分，不能写出行列名称。此外**write**函数是按行写出的，但R语言矩阵中的元素是按列排列的，所以矩阵写出时相当于进行了行列互换。

```R
write(x, file = "data", append = FALSE, sep = " ",
      ncolumns = if(is.character(x)) 1 else 5)
```

- **ncolumns**即需要写出多少列内容，如果**x**的纬度属性与这里设置的不相符，则先修改纬度属性再写出。


<br>

### 3.1、CSV文件

**CSV**文件是默认以英文逗号（**,**）作为字段分割符的表格类数据文件，但有时候文件中表示小数点的符号也有可以能是英文逗号，此时就需要使用英文分号（**;**）作为分割符。我们可以使用以下函数读写**CSV**文件，注意函数{{< hl-text primary >}}read.csv、write.csv{{< /hl-text >}}中的字段分割符是英文逗号，而函数{{< hl-text primary >}}read.csv2、write.csv2{{< /hl-text >}}中的字段分割符是英文分号。比如**read.csv**中`dec = ".", sep = ","`,  **read.csv2*中`dec = ",", sep = ";"`。

```R
read.csv(file, header = TRUE, sep = ",", quote = "\"",
         dec = ".", fill = TRUE, comment.char = "", ...)

read.csv2(file, header = TRUE, sep = ";", quote = "\"",
          dec = ",", fill = TRUE, comment.char = "", ...)

write.csv(...)
write.csv2(...)
```         
            
### 3.2、TSV文件

**TSV**文件是默认以制表符（**\t**）作为字段分割符的表格类数据文件，我们可以使用{{< hl-text primary >}}read.delim、read.delim2{{< /hl-text >}}函数，读取**TSV**文件。注意两者最大的不同依然是表示小数点的符号存在差异， **read.delim**中`dec = "."`,  **read.delim2*中`dec = ","`。

```R
read.delim(file, header = TRUE, sep = "\t", quote = "\"",
           dec = ".", fill = TRUE, comment.char = "", ...)

read.delim2(file, header = TRUE, sep = "\t", quote = "\"",
            dec = ",", fill = TRUE, comment.char = "", ...)
```

<br>

### 3.3、FWF文件

我们可以使用{{< hl-text primary >}}read.fwf{{< /hl-text >}}函数，读取每个字段宽度相同的表格类数据文件。注意**FWF**文件与**TSV**文件的不同之处在于：**TSV**中每个字段需要以特定的分割符（**\t**等）隔开，所以每个字段的字段宽度可以是不同的；**FWF**中字段之间没有分割符，所以字段宽度必须是固定的。

```R
read.fwf(file, widths, header = FALSE, sep = "\t",
         skip = 0, row.names, col.names, n = -1,
         buffersize = 2000, fileEncoding = "", ...)
```

- **sep**即标题行的内容分割符，只能由一个字符构成，且不能出现在记录部分
- **widths**即每个字段对应的长度（参考**nchar**），可以是一个数值型数组，其中**0**表示添加一个空字段，该字段取值为**NA**，负数表示略过相应长度的内容
- **buffersize**即每次读取的最大行数，相当于缓存，不影响最终读取的行数

<br>

### 3.4、Fortran类文件

我们可以使用{{< hl-text primary >}}read.fortran{{< /hl-text >}}函数，以**Fortran**语法格式，读取字段宽度已知的表格类数据文件。注意**Fortran**文件与**FWF**文件的不同之处在于：**Fortran**文件中每个字段的宽度可以是不同的，所以读取时需要指明特定的格式（每个字段的宽度），以下是该函数的使用方法及需要注意的参数：

```R
read.fortran(file, format, ..., as.is = TRUE, colClasses = NA)
```

- **format**即以什么样的格式读取每个字段，可以使用的格式有：**rFl.d、rDl.d、rXl、rAl、rIl**，其中**F、D、I、A、X**分别表示将读取的内容转化为浮点型数值、双精度浮点型数值、整形数值、字符串、或者略过不读，**r**表示相应的操作需要重复的次数，**l**表示需要读取的字符串宽度，**d**表示小数部分的位数。**r、d**均可被省略，**l**只在**rX**格式下可以省略

### 3.5、ftable文件

R语言中的**ftable**类型的数据对象本质上是一个矩阵，但与矩阵不同的是，**ftable**对象可以有多个行列标签分别代表数据的不同纬度，其行列标签分别存储在**ftable**对象的数据属性**row.vars、col.vars**中，比如以下**ftable**对象的**col.vars**属性相当于`list("Class" = c("Lower", "Upper"), "Dead" = c("Yes", "No"))`

```text
                 "Class"  "Lower"    "Upper"    
                 "Dead"   "Yes" "No"
"Race"  "Gender"                           
"White" "Male"              43 134    3 177
        "Female"            26 149    6 175
"Black" "Male"              29  23    9  52
        "Female"            22  36    2  58
```

在R语言中，我们可以分别使用{{< hl-text primary >}}read.ftable、write.ftable{{< /hl-text >}}函数，从文件中读写**ftable**对象。需要注意的是，**ftable**文件本质上是一种拥有多个行名/列名的表格类文件，只用于保存R语言中的**ftable**对象，并没有严格的个是限制，所以写入和读取过程并不是完全可逆的，以下是这些函数的使用方法及需要注意的参数：

```R
read.ftable(file, sep = "", quote = "\"", skip = 0,
            row.var.names, col.vars)

write.ftable(x, file = "", quote = TRUE, append = FALSE,
             digits = getOption("digits"), ...)
```

- **row.var.names**即行标签的标签名
- **col.vars**即列标签
- **quote**即文件中标识字符串类内容的左右引号（英文双引号，或单个字符）
- **digits**即R语言中的数值写入文件时需要保留的精度

<br>

### 3.6、DIF文件

**DIF**是微软开发的一种数据交换格式，用于保存电子表格，以便于在不同应用程序之间导入导出，可以被**Excel、Access**等软件打开。

在R语言中我们可以使用{{< hl-text primary >}}read.DIF{{< /hl-text >}}函数，读取**DIF**文件。需要注意的是，**DIF**文件可以是按列存储的，也可以是按行存储的，所以我们可能需要使用**transpose**参数，指明是否将读取到的内容进行行列互换。当然，我们也可以直接使用R语言中的{{< hl-text primary >}}t{{< /hl-text >}}函数，进行行列互换。

<br>

## 4、其它统计软件的数据文件

使用R语言进行统计分析时，可能需要与**EpiInfo、Minitab、S-PLUS、SAS、SPSS、Stata、Systat**等统计软件进行数据交换，R语言中并没有完成这项任务的系统函数，但我们可以使用{{< hl-text purple >}}foreign{{< /hl-text >}}程序包，读写这些统计软件的数据文件。以下为**foreign**程序包中的函数及相应功能：

| 函数         | 相应统计软件 | 默认文件后缀 | 解释说明                                                      
|:-------------|:-------------|:-------------|:------------------------------------------
| read.arff    |          | .arff   | 读取 [arff](https://www.cs.waikato.ac.nz/~ml/weka/arff.html) 文件
| read.dbf     |          | .dbf    | 读取 [dbf](hhttps://www.clicketyclick.dk/databases/xbase/format/) 文件
| read.dta     | stata    | .dta    | 读取 **stata** 的数据文件（ [dta_113](https://www.stata.com/help.cgi?dta_113)、 [dta_114](https://www.stata.com/help.cgi?dta_114) ）
| read.spss    | SPSS     | .sav    | 读取  **SPSS** 的数据文件
| read.ssd     | SAS      |         | 读取  **SAS** 数据库中的某个文件
| read.xport   | SAS      | .xpt    | 读取  **SAS** 的数据文件
| lookup.xport | SAS      | .xpt    | 读取  **SAS** 的数据文件的 [文件信息](https://support.sas.com/techsup/technote/ts140.pdf)
| read.epiinfo | EpiInfo  | .rec    | 读取 [Epi Info](https://www.cdc.gov/epiinfo/) 及 [EpiData](http://www.epidata.dk/cn/index.htm) 文件
| read.mtp     | Minitab  | .mtp    | 读取 [mtp](http://www.minitab.com/) 文件
| read.octave  | Octave   | .octave | 读取 [Octave](https://www.gnu.org/software/octave/) 文件
| read.systat  | Systat   | .syd    | 读取  **Systat** 的数据文件
| read.S       | S-PLUS   |         | 读取 **S-PLUS** 的数据文件（二进制文件）
| data.restore | S-PLUS   |         | 读取 **S-PLUS** 的数据文件（文本文件）
| write.arff   |          | .arff   | 写入 **arff** 文件
| write.dbf    |          | .dbf    | 写入 **dbf** 文件
| write.dta    | stata    | .dta    | 写入 **stata**文件
| write.foreign | Stata、SPSS、SAS |    | 写入 **Stata、SPSS、SAS**文件

这里需要特别介绍的是{{< hl-text primary >}}write.foreign{{< /hl-text >}}函数，它不仅可以输出**SPSS、Stata、SAS**统计软件的数据文件，还可以输出代码文件，用于在相应的统计软件和总读入数据文集爱你，以下是其使用方式及需要注意的参数：

```R
write.foreign(df, datafile, codefile, package = c("SPSS", "Stata", "SAS"), ...)
```

- **datafile**即保存数据的文件
- **codefile**即保存代码的文件，用于在相应的统计软件中读入数据文件

<br>

## 5、Excel类文件

**Excel**可能是日常办公最常用的表格类文件了，R语言中也有可以直接与**xls、xlsx**等类型的**Excel**文件进行交互的方法。如果我们只是需要获取**Excel**文件中的数据，则可以使用{{< hl-text purple >}}readxl{{< /hl-text >}}程序包的{{< hl-text primary >}}read_excel{{< /hl-text >}}函数。**readxl**程序包中的底层函数调用了C语言，读取速度更快。如果我们需要读写**Excel**文件，或者操作**Excel**文件中的格式，则可以使用{{< hl-text purple >}}xlsx{{< /hl-text >}}程序包。**xlsx**程序包中的底层函数调用了**JAVA**，所以我们需要实现安装配置**rJava**程序包。

我们可以使用**xlsx**程序包中的{{< hl-text primary >}}read.xlsx、write.xlsx{{< /hl-text >}}函数，读写**Excel**文件。此外我们还可以直接修改**Excel**文件中的格式，比如使用{{< hl-text primary >}}addAutoFilter、addMergedRegion、autoSizeColumn{{< /hl-text >}}函数，插入筛选器、插入合并的单元格、自动调整列宽，使用{{< hl-text primary >}}setCellStyle{{< /hl-text >}}函数，修改单元格属性。以下为修改单元格格式时，常用的函数及其参数：

| 函数           | 解释说明                                                      
|:---------------|:----------------------------------------------------------------------------------
| DataFormat     | 数据格式，如`DataFormat("YYYY-MM-DD")`表示年月日、`DataFormat("0")`表示无格式文本
| Alignment      | 对齐，如`Alignment(horizontal="ALIGN_CENTER)"`，表示水平方向居中对齐
| Border         | 边框，如`Border(color="black", position="BOTTOM", pen="BORDER_THIN")`
| Fill           | 填充，如`Fill(backgroundColor="lightblue")`
| Font           | 填充，如`Font(wb, color="blue", isItalic=TRUE)`，表示设置工作簿**wb**的字体为蓝色斜体字
| CellProtection | 保护，如`CellProtection(locked=TRUE)`表示锁定单元格

- **rowIndex**即需要选择哪些行
- **colIndex**即需要选择哪些列
- **startRow**即从哪一行的单元格开始
- **endRow**即到哪一行的单元格结束
- **startColumn**即从哪一列的单元格开始
- **endColumn**即到哪一列的单元格结束

<br>

## 6、JSON文件

[JSON](http://www.json.org/)是一款轻量级的数据序列化标准，它在易于阅读和编辑的同时，也易于被计算机解析、生成。以下是一段标准的**JSON**语句：

```JSON
{
  "menu": {
    "doctype": "File",
    "menuitem": [
      {
        "value": "Open",
        "onclick": "OpenDoc()"
      },
      {
        "value": "Close",
        "onclick": "CloseDoc()"
      }
    ]
  }
}
```

我们可以使用{{< hl-text purple >}}rjson{{< /hl-text >}}程序包中的{{< hl-text primary >}}fromJSON、toJSON{{< /hl-text >}}函数读写**JSON**，以下为读写**JSON**时需要注意的参数：

- **simplify**即是否将只含有同一数据类型的**标量值**的json文本转化为数组而非列表
- **indent**即格式化json文本时，每一个 *子行* 需要缩进的空格数量


<br>

## 7、YAML文件

[YAML](https://yaml.org/)是一种面向所有计算机语言的、容易阅读的数据序列化标准，可以直接存储各种标量、数组、列表等类型的数据。**YAML**不是一种**标记语言**，但它可以通过换行与缩进等形式，以容易阅读的形式展示数据，所以被广泛用于各种配置文件、文件大纲等。以下是一段由**YAML**表示的**markdown**文章标题：

```YAML
title: "R语言文件输入输出"
date: !expr Sys.Date()
keywords:
  - R语言
  - IO管理
```

我们可以使用{{< hl-text purple >}}YAML{{< /hl-text >}}程序包中的{{< hl-text primary >}}read_yaml、write_yaml{{< /hl-text >}}函数读写**YAML** ，注意**read_yaml**函数会根据读取内容的类型（字符串或文件）分别调用{{< hl-text primary >}}yaml.load、yaml.load_file{{< /hl-text >}}函数，而**write_yaml**会调用{{< hl-text primary >}}as.yaml{{< /hl-text >}}函数。

- **eval.expr**即读取时是否执行**YAML**中的命令（命令格式必须为`!expr 命令`）
- **column.major**即数据框转化为**YAML**时，是否按列转化
- **omap**即列表转化为**YAML**时，是否在列表前写入**!omap**

<br>

## 8、DCF文件

**DCF**(**Debian Control File**)文件是一种用于**Debian**操作系统的控制文件，其格式类似**YAML**，但只能以键值对的形式存储信息。R语言程序包中的**DESCRIPTION**等文件，就使用了这种格式存储信息。以下为一个示例**DESCRIPTION**文件：

```
Package: myFirstPackage
Version: 1.0.0
Title: My First Package
Description: Not decided yet,
  problem shooting <somebody@email.com>
Built: R 3.6.1; x86_64-pc-linux-gnu; 2019-07-26 13:35:28 UTC; unix
```

我们可以使用R语言中的系统函数{{< hl-text primary >}}read.dcf、write.dcf{{< /hl-text >}}，读写**DCF**文件。当然我们也可以用读写**YAML**文件的方法，读写**DCF**。

```R
read.dcf(file, fields = NULL, all = FALSE, keep.white = NULL)

write.dcf(x, file = "", append = FALSE, useBytes = FALSE,
          indent = 0.1 * getOption("width"), width = 0.9 * getOption("width"),
          keep.white = NULL)
```

- **fields**即需要从文件中读取的字段，默认为全部字段
- **all**即当文件中包含两个同名字段时，是否将其内容合并为同一个字段（使用英文逗号分割）。若取值为**FALSE**，则只读取最后一个字段的值
- **keep.white**即哪些字段的前后空格需要被保留，可以是一个字符串数组，也可以是**NULL**表示所有字段的前后空格都不保留
- **indent**即字段换行时，需要在行首插入的空格数量
- **width**即写出文件时每一行的最大宽度

<br>

## 9、XML类文件

**XML**是一种用于标记电子文件使其具有结构性的标记语言，类似的语言还有**HTML**、**SGML**等。注意**HTML**与**XML**均被广泛的应用于互联网领域，两者最大的不同在于：**HTML**不允许用户自定义标签（节点）或属性，但**XML**中可以。以下是一段标准的**XML**语句：

```xml
<?xml version="1.0" encoding="ISO-8859-1"?>
<bookstore>
    <book category="CHILDREN">
        <title lang="en">Harry Potter</title>
        <price>29.99</price>
    </book>
    <book category="WEB">
        <title lang="en">Learning XML</title>
        <price>39.95</price>
    </book>
</bookstore>
```

我们可以使用{{< hl-text purple >}}XML{{< /hl-text >}}程序包读写**XML**类文件。首先我们可以使用{{< hl-text primary >}}xmlParse、htmlParse{{< /hl-text >}}函数，将**XML**或**HTML**文本转化为以R语言对象表示的**XML结构树**。接下来我们可以使用以下函数，在R语言中查看、修改、删除XML结构树中的内容。

| 函数              | 解释说明                                                      
|:------------------|:-----------------------------------------------------------------
| xmlRoot           | 获取XML结构树的根结点
| xmlChildren       | 获取或修改某个节点的子节点
| xmlParent         | 获取或修改某个节点的父节点
| xmlName           | 获取或修改某个节点的节点名称
| xmlAttrs          | 获取或修改某个节点的所有节点属性
| xmlGetAttr        | 获取或修改某个节点的某个节点属性
| xmlValue          | 获取或修改某个节点的节点内容
| addNode           | 添加节点
| addAttributes     | 添加节点属性
| addChildren       | 添加子节点
| replaceNodes      | 替换节点
| removeNode        | 删除节点
| removeAttributes  | 删除节点元素
| removeChildren    | 删除子节点

当然我们也可以分别使用{{< hl-text primary >}}xmlToList、xmlToS4{{< /hl-text >}}函数，直接将XML结构树转化为R语言中的列表、S4对象。如果我们只需要获取XML结构树中的列表、表格，还可以分别使用{{< hl-text primary >}}readHTMLList、readHTMLTable{{< /hl-text >}}函数。

此外我们还可以使用**xpath**，快速定位**XML**结构树中的内容，以下表格即**xpath**的语法格式。我们需要使用{{< hl-text primary >}}getNodeSet{{< /hl-text >}}函数，提取**xpath**对应的元素（可能是由节点对象构成的列表、数值、逻辑值、字符串）。为了更方便的处理**getNodeSet**函数返回的节点列表，我们还可以使用{{< hl-text primary >}}xmlApply{{< /hl-text >}}函数，以并发运算的方式处理节点对象组成的数组或列表。

| **xpath**         | 解释说明                                                      
|:------------------|:-----------------------------------------------------------------
| /                 | 从根节点开始查找，节点路径分割符，比如{{< hl-text blue >}}/bookstore/book{{< /hl-text >}}
| //                | 从当前节点下的任意位置开始查找，比如{{< hl-text blue >}}//book{{< /hl-text >}}
| .                 | 获取当前节点
| ..                | 获取当前节点的父节点，比如{{< hl-text blue >}}//title/..{{< /hl-text >}}
| node              | 获取d当前节点下的所有**node**节点
| [n]               | 筛选第**n**个节点，比如{{< hl-text blue >}}/bookstore/book[2]{{< /hl-text >}}
| [last()-n]        | 筛选倒数第**n**个节点，比如{{< hl-text blue >}}//book[last()]{{< /hl-text >}}，注意如果`//`之前的路径对应多个包含**book**的节点，则表示在每个节点中分别进行位置筛选
| [position() < n]  | 筛选前**n-1**个节点，比如{{< hl-text blue >}}//book[position() < 3]{{< /hl-text >}}
| @attr             | 筛选必须拥有**attr**属性，比如{{< hl-text blue >}}//book[@category{{< /hl-text >}}、{{< hl-text blue >}}//@category{{< /hl-text >}}
| @attr = 'value'   | 筛选**attr**属性必须等于**value**，比如{{< hl-text blue >}}//book[@category='WEB']{{< /hl-text >}}
| node > n          | 筛选**node**节点中的数值必须大于**n**，比如{{< hl-text blue >}}//book[price>35]{{< /hl-text >}}
| *                 | 匹配任意节点，比如{{< hl-text blue >}}//book[1]/*{{< /hl-text >}}
| @*                | 匹配任意属性，比如{{< hl-text blue >}}//book[@*]{{< /hl-text >}}、{{< hl-text blue >}}//book[1]/@*{{< /hl-text >}}
| node()            | 匹配任意节点，等同于{{< hl-text blue >}}*{{< /hl-text >}}
| text()            | 匹配任意节点内容，比如{{< hl-text blue >}}//title[1]/text(){{< /hl-text >}}
| expr1 \| expr2  | 获取匹配**expr1**或**expr2**的元素，比如{{< hl-text blue >}}//book[1] | //book[@category='WEB']{{< /hl-text >}}

<br>

## 10、图像类文件

R语言虽然自带强大的图形化工具，但大多用于绘制、保存图像。为了方便提取图像中的信息进行数据分析（如图像识别），我们可以使用{{< hl-text purple >}}png、jpep{{< /hl-text >}}等程序包中的函数，读写**PNG、JPEG**等图像文件。注意读入R语言的图像将以三维数组的形式表示，数组中的行列分别代表图片横向和纵向的像素点，数组第三个纬度上的四个元素分别表示相应像素点的RGB和透明度（均已被标量化，取值范围在0-1之间）。由于**PNG、JPEG**等图像文件以压缩的形式存储图像信息，读入内存后图像是以位图的形式表示的，所以占用的空间远大于存储时占用的空间。

R语言中图像处理、大数据分析的方法并不是很丰富，但我们可以在R语言中使用第三方工具完成这些任务，参考{{< hl-text purple >}}TensorFlow、keras、sparklyr{{< /hl-text >}}等程序包。

<br>

## 11、阅读文档类文件

*阅读文档类文件* 指的是为便于阅读、展示而产生的各种类型的文档，与**纯文本文件** 不同的是，阅读文档类文件中除了要包含文本内容，还要包含文本的展示样式。所以读写这类文件往往需要特定的编辑器或者程序，否则很容易破坏文档的结构，从而导致文档实效。

在R语言中，我们可以使用{{< hl-text purple >}}knitr、rmarkdown{{< /hl-text >}}程序包，结合R语言与**markdown**语法，输出**HTML、PDF、Word、PowerpPint**文档。上文已经介绍了如何读取**HTML**文档中的内容，此外我们还可以使用{{< hl-text purple >}}officer{{< /hl-text >}}程序包，读写**Word、PowerpPint**等文档中的内容。读取**PDF**文档中的内容，我们可以使用{{< hl-text purple >}}pdftools{{< /hl-text >}}程序包，注意如果pdf文档中含有加密信息，我们需要提供相应的密码才能读取，还有一些pdf文档实际上是以图片的形式存储信息的，所以不能读取其中的文字。

<br>


{{< note "思考思考" "#e6e6ff" >}}
- R语言如何写出**FWF**类文件？
- **xpath**——`//@attr='value'`有什么作用？
- R语言中可以读写音频、视频类文件吗？

{{< /note >}}

<br>
