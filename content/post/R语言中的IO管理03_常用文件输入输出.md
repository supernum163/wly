---
title: R语言常用文件输入输出
date: 2019-09-27
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
thumbnailImage: https://s2.ax1x.com/2019/08/17/muddIA.png
---

这篇文章我们将介绍R语言常用文件输入输出。

<!--more-->

<!-- toc -->

## 1、二进制文件

我们在之前的文章中介绍过使用{{< hl-text primary >}}readBin、writeBin{{< /hl-text >}}函数读写二进制文件

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

```R
readChar(con, nchars, useBytes = FALSE)
writeChar(object, con, nchars = nchar(object, type = "chars"), eos = "", useBytes = FALSE)
```

- **nchar**即需要读写多少个字符，注意一个字符可能对应多个字节
- **eos**即在每个字符串写入结束时，需要向文件中写入的字符串结束标志符），默认为空字符，取值为**NULL**时表示不写入字符串结束标志符

<br>

## 2、文本文件

**空字符**（**\x00**）与**空白字符**（**\x20**），**\r、\n、\r\n**都会（统一被替换为**\n**）被当作行结束标志符

| 简称      | 全称            | 解释说明                                                      
|:----------|:----------------|:-------------------
| EOS       | End Of String   | 字符串结束标志符
| EOL       | End Of Line     | 行结束标志符
| EOF       | End Of File     | 文件结束标志符

<br>

**readline**从系统输入中读取一行内容，可以临时修改命令提示符。**readLines**需要手动提供需要读取多少行，注意此时可以使用**Ctrl+D**输入文件结束标志符，不能临时修改命令提示符

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

## 3、DCF类文件

R语言程序包中的**DESCRIPTION**文件

```
Package: myFirstPackage
Version: 1.0.0
Title: My First Package
Description: Regression spline functions and classes,
  problem shooting <somebody@me.com>
Built: R 3.6.1; x86_64-pc-linux-gnu; 2019-07-26 13:35:28 UTC; unix
```

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

## 3、纯文本表格类文件

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

     
read.table(file, header = FALSE, numerals = c("allow.loss", "warn.loss", "no.loss"),
           row.names, col.names, as.is = !stringsAsFactors, colClasses = NA, nrows = -1,
           check.names = TRUE, stringsAsFactors = default.stringsAsFactors(), ...)
            
- **header**即是否将文件第一行最为标题行（列名），默认如果首行元素个数比其它行少一个，则将其设为标题行
- **numerals**即将文件中的数值转化为R语言对象（双精度浮点型）时是否允许精度损失，以及损失精度时是否触发异常
- **row.names**即表格的行名，可以是与行数相同的字符串数组，也可以是一个数值或字符串，指明将表格中的哪一列作为行名。如果首行元素个数比其它行少一个，则其它行中每行的首个元素作为行名。默认或设置`row.names = NULL`，表示使用 *行位序数* （从1开始自动编号的数字）作为行名
- **col.names**即表格的列名，可以是与列数相同的字符串数组，默认使用以**V**开头的 *列位序数* 作为列名
- **as.is**即哪些列不能被转化为因子型对象，可以是与列数相同的逻辑值数组，也可以是一个数值或字符串数组，指明哪些列不能被转化，注意文件中的行名或者读取是跳过的列都会被算作单独的一列
- **colClasses**即表格中的每一列分别需要被转化为什么类型的对象，可以是与列数相同的字符串数组；也可以是**NA**，表示使用默认的转化方式（参考**type.convert**）；还可以是**NULL**，表示略过某一行不读
- **check.names**即是否检查表格列名的合法性，若取值为**TRUE**，则列名重复时以数字后缀区分
- **stringsAsFactors**即是否将字符串转化为因子，可以被**as.is、colClasses**的设定覆盖

write.table(x, file = "", append = FALSE, qmethod = c("escape", "double"),
            eol = "\n", na = "NA", row.names = TRUE, col.names = TRUE, ...)

- **append**即是否将输出结果附加到文件中，只有当**file**为文件名时有效
- **qmethod**即以何种方式处理字符串中的英文引号，**escape**表示进行字符转义，**double**表示用两个引号代替单个引号
- **eol**即需要在一行结束时向文件中写入的行结束标志符
- **na**即写出时以什么样的字符串表示R语言中的缺失值
- **row.names、col.names**即是否将行名、列名写入文件

与**write.table**相似的是**write**函数，**write**函数本质上相当于调用了**cat**函数，可以将R语言对象（通常是矩阵）写入文件，但只能写出数据部分，不能写出行列名称

write(x, file = "data", append = FALSE, sep = " ",
      ncolumns = if(is.character(x)) 1 else 5)
      
- **ncolumns**即需要写出多少列内容，如果**x**的纬度属性与这里设置的不相符，则先修改纬度属性再写出。**write**函数是按行写出的，但R语言矩阵中的元素是按列排列的，所以矩阵写出时相当于进行了行列互换


<br>

### 3.1、csv文件

注意 **read.csv**中`sep = ",", dec = "."`,  **read.csv2*中`sep = ";", dec = ","`

read.csv(file, header = TRUE, sep = ",", quote = "\"",
         dec = ".", fill = TRUE, comment.char = "", ...)

read.csv2(file, header = TRUE, sep = ";", quote = "\"",
          dec = ",", fill = TRUE, comment.char = "", ...)

write.csv(...)
write.csv2(...)
            
            
### 3.2、tsv文件

注意 **read.delim**中`dec = "."`,  **read.delim2*中`dec = ","`

read.delim(file, header = TRUE, sep = "\t", quote = "\"",
           dec = ".", fill = TRUE, comment.char = "", ...)

read.delim2(file, header = TRUE, sep = "\t", quote = "\"",
            dec = ",", fill = TRUE, comment.char = "", ...)

<br>

### 3.3、fwf文件

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

```R
read.fortran(file, format, ..., as.is = TRUE, colClasses = NA)
```

- **format**即以什么样的格式读取每个字段，可以使用的格式有：**rFl.d、rDl.d、rXl、rAl、rIl**，其中**F、D、I、A、X**分别表示将读取的内容转化为浮点型数值、双精度浮点型数值、整形数值、字符串、或者略过不读，**r**表示相应的操作需要重复的次数，**l**表示需要读取的字符串宽度，**d**表示小数部分的位数。**r、d**均可被省略，**l**只在**rX**格式下可以省略

### 3.5、ftable文件

R语言中的**ftable**类型的数据对象本质上是一个矩阵，但与矩阵不同的是，**ftable**对象可以有多个行列标签分别代表数据的不同纬度，其行列标签分别存储在**ftable**对象的数据属性**row.vars、col.vars**中，比如以下**ftable**对象的**col.vars**属性相当于`list("Class" = c("Lower", "Upper"), "Dead" = c("Yes", "No"))`

```
                 "Class"  "Lower"    "Upper"    
                 "Dead"   "Yes" "No"
"Race"  "Gender"                           
"White" "Male"              43 134    3 177
        "Female"            26 149    6 175
"Black" "Male"              29  23    9  52
        "Female"            22  36    2  58
```

read.ftable(file, sep = "", quote = "\"", skip = 0,
            row.var.names, col.vars)

write.ftable(x, file = "", quote = TRUE, append = FALSE,
             digits = getOption("digits"), ...)

- **row.var.names**即行标签的标签名
- **col.vars**即列标签
- **quote**即文件中标识字符串类内容的左右引号，写入时只能选择不用，或使用英文双引号
- **digits**即R语言中的数值写入文件时需要保留的精度

<br>

## 4、其它统计软件的数据文件

使用**foreign**程序包，可以读写**EpiInfo、Minitab、S-PLUS、SAS、SPSS、Stata、Systat**等统计软件的数据文件

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


write.foreign(df, datafile, codefile, package = c("SPSS", "Stata", "SAS"), ...)
              
- **datafile**即保存数据的文件
- **codefile**即保存代码的文件，用于在相应的统计软件中读入数据文件

<br>

## 5、带格式表格类文件

### 5.1、DIF文件

```
TABLE
0,1
"EXCEL"
VECTORS
0,5
""
TUPLES
0,2
""
DATA
0,0
""
-1,0
BOT
1,0
"Var1"
1,0
"Var2"
-1,0
BOT
0,2.7
V
1,0
"A"
-1,0
EOD
```


```R
read.DIF(file, header = FALSE,
         dec = ".", numerals = c("allow.loss", "warn.loss", "no.loss"),
         row.names, col.names, as.is = !stringsAsFactors,
         na.strings = "NA", colClasses = NA, nrows = -1,
         skip = 0, check.names = TRUE, blank.lines.skip = TRUE,
         stringsAsFactors = default.stringsAsFactors(),
         transpose = FALSE, fileEncoding = "")
````

- **transpose**即是否将文件中的内容行列互换

### 5.2、Excel类文件

使用**readxl**程序包的{{< hl-text primary >}}read_excel{{< /hl-text >}}函数读取**xls、xlsx**类型的**Excel**文件。

使用**xlsx**程序包中的{{< hl-text primary >}}read.xlsx、write.xlsx{{< /hl-text >}}函数，读写**xlsx**文件。使用{{< hl-text primary >}}addMergedRegion{{< /hl-text >}}函数，插入合并的单元格；使用{{< hl-text primary >}}CellStyle{{< /hl-text >}}函数，修改单元格属性。

- **rowIndex**即需要选择哪些行
- **colIndex**即需要选择哪些列
- **startRow**即从哪一行的单元格开始
- **endRow**即到哪一行的单元格结束
- **startColumn**即从哪一列的单元格开始
- **endColumn**即到哪一列的单元格结束

| 函数           | 解释说明                                                      
|:---------------|:----------------------------------------------------------------------------------
| DataFormat     | 数据格式，如`DataFormat("YYYY-MM-DD")`表示年月日、`DataFormat("0")`表示无格式文本
| Alignment      | 对齐，如`Alignment(horizontal="ALIGN_CENTER)"`，表示水平方向居中对齐
| Border         | 边框，如`Border(color="black", position="BOTTOM", pen="BORDER_THIN")`
| Fill           | 填充，如`Fill(backgroundColor="lightblue")`
| Font           | 填充，如`Font(wb, color="blue", isItalic=TRUE)`，表示设置工作簿**wb**的字体为蓝色斜体字
| CellProtection | 保护，如`CellProtection(locked=TRUE)`表示锁定单元格


<br>

## 6、输入/输出JSON文件

使用**rjson**程序包中的**fromJSON、toJSON**读写 [json](http://www.json.org/)

```R
> fromJSON('[1,2,3]', simplify=TRUE)
[1] 1 2 3
> toJSON(1:3)
[1] "[1,2,3]"
```

- **simplify**即是否将只含有同一数据类型的**标量值**的json文本转化为数组而非列表
- **indent**即格式化json文本时，每一个 *子行* 需要缩进的空格数量


<br>

## 7、YAML文件

使用**yaml**程序包中的**read_yaml、write_yaml**函数读写 [yaml](https://yaml.org/)，**read_yaml**函数会根据读取内容的类型（字符串或文件）分别调用**yaml.load、yaml.load_file**函数，**write_yaml**会调用**as.yaml**函数。

```R
> fromJSON('[1,2,3]', simplify=TRUE)
[1] 1 2 3
> toJSON(1:3)
[1] "[1,2,3]"
```
- **error.label**即解析出错时，错误信息的标签
- **eval.expr**即是否执行yaml中的命令

- **column.major**即数据框转化为yaml时，是否按列转化
- **omap**即列表转化为yaml时，是否在列表前写入**!omap**

<br>


## 8、xml类文件

使用**XML**程序包读写XML文件，参考 [xpath](https://www.w3school.com.cn/xpath/xpath_syntax.asp)

```xml
<?xml version="1.0" encoding="ISO-8859-1"?>
<bookstore>
  <book>
    <title lang="eng">Harry Potter</title>
    <price>29.99</price>
  </book>
  <book>
    <title lang="eng">Learning XML</title>
    <price>39.95</price>
  </book>
</bookstore>
```

| **xpath**  | 解释说明                                                      
|:-----------|:----------------------------------------------------------------------------------
| nodename   | 选取此节点的所有子节点
| /          | 从根节点选取
| //         | 从匹配选择的当前节点选择文档中的节点，而不考虑它们的位置
| .          | 选取当前节点
| ..         | 选取当前节点的父节点
| @          | 选取属性
| @*         | 匹配任何属性节点
| *          | 匹配任何元素节点
| node()     | 匹配任何类型的节点


htmlParse     将xml或html文本转化为以R语言对象表示的XML结构树
xmlRoot       获取根结点
xmlChildren   获取子节点
xmlAttrs      获取节点属性

getNodeSet    寻找节点
xmlApply      并发处理节点对象组成的数组或列表


addNode           添加节点
addAttributes     添加节点属性
addChildren       添加子节点

replaceNodes      替换节点

removeNode        删除节点
removeAttributes  删除节点元素
removeChildren    删除子节点

readHTMLList      从html文件中读取列表
readHTMLTable     从html文件中读取表格

<br>

## 9、图像类文件

使用**png、jpep**程序包

<br>

## 10、html、pdf、word、powerpoint

使用**rmarkdown**程序包，结合R语言与**markdown**语法，输出**html、pdf、word、powerpoint**文件。

<br>


{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
