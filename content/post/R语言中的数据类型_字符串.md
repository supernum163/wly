---
title: "R语言与字符串处理"
date: 2019-05-31
categories:
  - R语言
  - 数据类型
tags:
  - R语言数据类型
keywords:
  - R语言
  - 数据类型
  - 字符串处理
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/fbdrXS6P/R.png
---

**文本信息**作为我们最常见的信息来源，当然也可以被用于数据分析。**文本分析**离不开强大的字符串处理能力，这篇文章将介绍如何在**R语言**中进行**字符串**处理。

<!--more-->

<!-- toc -->

## 1、字符串的基本操作

在R语言中，包含在两个英文**双引号**或者**单引号**之间的任意内容都会被视为字符串。如果我们想要输入一个包含字符**"**（或者**'**）的字符串，则需要使用转义符**\**作为前缀。同样如果我们包含字符**\**，也需要加入转义符前缀。注意转义符并不是一个单独的字符，它与被转义的字符共同组成一个字符，比如**\t**表示制表符。

我们可以使用{{< hl-text primary >}}print{{< /hl-text >}}函数（或者直接使用**变量**的形式），查看被转义之前的字符串。但这种方法有时候不容易区分出哪些是转义字符，哪些是真正的字符。想要查看字符串的转义结果，则可以使用{{< hl-text primary >}}cat{{< /hl-text >}}函数。

```R
> " 注意 \"\\t\" 与 \"\t \" 不同 "
[1] " 注意 \"\\t\" 与 \"\t \" 不同 "
> cat(" 注意 \"\\t\" 与 \"\t \" 不同 ")
 注意 "\t" 与 "	 " 不同 
```

<br>

### 1.1、字符串长度

我们可以使用命令{{< hl-text primary >}}nchar(x, type = c("bytes", "chars", "width")){{< /hl-text >}}，来查看字符串的长度。这里**type**参数的三个取值分别表示：查看字符串占用多少个字节；查看字符串包含多少个字符；查看输出字符串时需要占用的宽度。 注意一个英文字符（或ascii字符）的宽度总是为1，而一个中文字符的宽度总是为2。

```R
> nchar("abc\t中文")
[1] 6
> nchar("abc\t中文", "bytes")
[1] 10
> nchar("abc\t中文", "width")
[1] 8
```

<br>

### 1.2、截取字符串

在R语言中截取字符串的函数是{{< hl-text primary >}}substr、substring{{< /hl-text >}}。这两个函数都需要指明需要被截取的**原字符串**，以及截取的**起始位置**与**终止位置**，不同的是**substr**总是会生成一个与原字符串数组等长的数组，而**substring**会循环利用其参数，最终生成的结果总是与三个数组参数中最长的数组等长。

根据以上规则，我们不但可以截取一个字符串（或字符串数组）中的一部分，也可以对同一个字符串进行多次截取。对一个字符串数组中的不同元素使用不同的截取模式。此外我们还可以直接替换掉被截取的部分。

```R
> x <- c("abcdefg", "ghijkl")
> substr(x, 2, 4)
[1] "bcd" "hij"
> substring(x[1], 1:6, 1:6)
[1] "a" "b" "c" "d" "e" "f"
> substr(x, 2, 4:5)
[1] "bcd"  "hijk"
> substring(x, 2) <- c("..", "+++"); x
[1] "a..defg" "g+++kl" 
```

<br>

### 1.3、字符串拼接与分割

在R语言中我们可以分别使用{{< hl-text primary >}}paste、strsplit{{< /hl-text >}}函数进行字符串拼接与分割，它们的使用方式分别如下:

`paste (..., sep = " ", collapse = NULL)`

- **...**表示需要拼接的一个或多个字符串、字符串数组
- **sep**即拼接符，默认为一个空格，用于拼接多个参数
- **collapse**即拼接符，用于将一个字符串数组拼接成一个字符串

`strsplit(x, split, ...)`

- **x**表示需要分割的字符串或字符串数组
- **split**即分割符，可以是一个特定的字符或字符串，也可以使用[正则表达式](#正则表达式)

注意**strsplit**会生成一个列表，其中每个元素都是一个数组，代表被分割对象中相应元素的分割结果。R语言中拥有两个系统数组**LETTERS、letters**分别记录了26个大小写字母，我们可以使用这两个数组演示字符串的拼接与分割：

```R
> paste(LETTERS[1:7], letters[1:7], sep = " ")
[1] "A a" "B b" "C c" "D d" "E e" "F f" "G g"
> paste(letters, collapse = "")
[1] "abcdefghijklmnopqrstuvwxyz"
> strsplit("abcdefg", split = NULL)
[[1]]
[1] "a" "b" "c" "d" "e" "f" "g"
```

<br>

### 1.4、简单查找

有时候我们需要判断字符串是否以某个**前缀**开头，或者以某个**后缀**结尾，则可以分别使用{{< hl-text primary >}}startsWith、endsWith{{< /hl-text >}}函数

如果我们想要知道一个字符串数组（**查找表**）中，某个字符串（或包含某个前缀的字符串）所在位置，则可以分别使用{{< hl-text primary >}}match、pmatch、charmatch{{< /hl-text >}}函数。其中：

- **match**函数相当于全字查找，查找某个字符串在字符串数组中的位置
- **pmatch、charmatch**函数能以前缀查找，但全字查找的顺序优先于前缀查找。不同的是**pmatch**可以指定**duplicates.ok = FALSE**，表示当查找表中的某个元素被查找到一次之后就不再使用
- 三个函数中都可以指定参数**nomatch**的值，表示查找不到时应该返回的值
- 如果前缀在查找表中没有区分度，**charmatch**会返回0，而**pmatch**会返回查找不到
- **pmatch**不能查找空字符

R语言中正是大量使用了这里的字符查找模式，所以当我们调用函数时，很多情况下函数的参数名、参数取值都可以简写。

```R
> pmatch(c("", "ab", "ab"), c("abc", "ab"), dup = FALSE)
[1] NA  2  1
> charmatch(c("", "ab", "ab"), c("abc", "ab"))
[1] 0 2 2
```

<br>

### 1.5、字符替换

在R语言中我们可以分别使用{{< hl-text primary >}}toupper、tolower{{< /hl-text >}}函数，或者使用命令{{< hl-text primary >}}casefold(x, upper = c(TRUE, FALSE)){{< /hl-text >}}的形式，对英文字符进行大小写转换。类似的我们也可以使用{{< hl-text primary >}}chartr(old, new, x){{< /hl-text >}}的形式，将字符串**x**中的任意**old**字符替换为**new**字符，注意**old**与**new**中的字符需要一一对应。

```R
> c(toupper("aBcDeFg"), casefold("aBcDeFg"))
[1] "ABCDEFG" "abcdefg"
> chartr("大ABC", "小abc", "大写字母: ABC")
[1] "小写字母: abc"
```

<br>

## 2.正则表达式

正则表达式是一种模式（或规则），可以被用于查找、匹配或替换文本中相应的，或者说符合某种模式的内容。R语言中的正则表达式包含了普通的正则表达式、**扩展正则表达式**、**perl正则表达式**，参考`regex`帮助文档。此外R语言中使用正则表达式的函数，绝大部分都支持以下参数：

- **fixed**表示是否表示严格按照字符查找匹配，取值为**FALSE**时表示将字符作为正则表达式进行查找匹配
- **ignore.case**表示是否忽略大小写
- **perl**表示是否使用**perl**正则表达式
- **useBytes**表示按照**字节**或按照**字符**进行查找匹配

|                 | 正则表达式            | 解释说明                                                        |
|:----------------|:----------------------|:----------------------------------------------------------------|
| ascii字符       | \t、\n、\r、……        | 匹配**制表符**、**换行符**、**回车符**等特定ascii字符           |
| 字符编码        | \x09、\x0a、\0d、……   | 按照字符编码，匹配**制表符**、**换行符**、**回车符**等特定字符  |
| 特殊字符        | \\                    | 转义符                                                          |
|                 | \\\\d                 | 匹配任意数字（0-9）                                             |
|                 | \\\\D                 | 反向匹配任意数字                                                |
|                 | \\\\w                 | 匹配任意字符                                                    |
|                 | \\\\W                 | 反向匹配任意字符                                                |
|                 | \\\\s                 | 匹配任意空白字符                                                |
|                 | \\\\S                 | 反向匹配任意空白字符                                            |
|                 | .                     | 匹配除换行符之外的任意字符                                      |
|                 | ()                    | 标记一个子表达式                                                |
|                 | []                    | 匹配方括号内的任意字符                                          |
|                 | [n-m]                 | 匹配字符编码在字符n到m之间的任意字符                            |
|                 | n|m                   | 匹配字符n或字符m                                                |
|                 | ^                     | 匹配字符串开头，结合方括号时表示反向匹配某个字符                |
|                 | $                     | 匹配字符串结尾                                                  |
| 限定符          | ?                     | 匹配0次或1次                                                    |
|                 | +                     | 匹配1次或多次                                                   |
|                 | *                     | 匹配任意次数                                                    |
|                 | {n}                   | 匹配n次                                                         |
|                 | {n, m}                | 匹配n到m次（n或m其中一方可为空）                                |
| 扩展正则表达式  | [[:digit:]]           | 匹配十进制数字                                                  |
|                 | [[:xdigit:]]          | 匹配十六进制数字                                                |
|                 | [[:alpha:]]           | 匹配大小写字母                                                  |
|                 | [[:lower:]]           | 匹配小写字母                                                    |
|                 | [[:upper:]]           | 匹配大写字母                                                    |
|                 | [[:alnum:]]           | 匹配大小写字母和数字                                            |
|                 | [[:blank:]]           | 匹配空白字符（空格、\t）                                        |
|                 | [[:space:]]           | 匹配空白字符（空格、\t、\n、\r、\v、\f）                        |
|                 | [[:cntrl:]]           | 匹配不可打印的控制字符（\x00-\x1f、\x7f）                       |
|                 | [[:graph:]]           | 匹配可打印的非空白字符                                          |
|                 | [[:print:]]           | 匹配可打印字符                                                  |
|                 | [[:punct:]]           | 匹配标点符号                                                    |


<br>

### 2.1、正则查找

上文我们介绍了如何使用**\*match**家族的函数对字符串进行简单查找，如果我们需要使用正则表达式的形式，根据某种模式查找字符串（或字符串数组），则可以使用以下函数：

```R
grepl(pattern, x, ...)
grep(pattern, x, value = FALSE, invert = FALSE, ...)
grepRaw(pattern, x, value = FALSE, invert = FALSE, offset = 1L, all = FALSE, ...)
```

- **pattern**即需要查找的正则表达式
- **x**即需要被查找的字符串或字符串数组
- **value**表示是否直接返回查找到的值，取值为**FALSE**时表示返回查找到的字符串所在位置
- **invert**表示是否反向匹配**pattern**
- **offset**表示需要略过多少个字节
- **all**表示是否查找全部匹配项，取值为**FALSE**时表示只返回第一个查找到的值

其中**grepl**函数会返回逻辑值，表示是否查找到特定模式；**grep**函数会返回查找到的字符串，或者查找到的字符串所在字符串数组中的位置；**grepRaw**函数是按照字节查找，可以进行多次查找，但查找的模式与被查找的字符串都必须为单一的字符串，最终返回符合特定模式的内容在字符串中的位置（第多少个字节）。

```R
> grepl("[ab]", c("abc", "def"))
[1]  TRUE FALSE
> grep("[ab]", c("abc", "def"), value = TRUE)
[1] "abc"
> grep("[ab]", c("abc", "def"), invert = TRUE)
[1] 2
> grepRaw("[ab]", "abcabc", offset = 3L, all = TRUE)
[1] 4 5
```

<br>

### 2.2、正则匹配

如果我们需要以某种模式**pattern**从字符串（或字符串数组）**x**中匹配到特定的内容，并最终获得匹配的起始位置及匹配长度，则可以使用{{< hl-text primary >}}regexpr、regexec、gregexpr{{< /hl-text >}}等函数。注意：

- **regexpr、regexec**只对**x**中的每个元素匹配一次，而**gregexpr**则可以匹配所有符合**pattern**的内容
- **regexpr、regexec、gregexpr**返还的值与**x**中每个元素的匹配位置一一对应，匹配长度则存放在与匹配长度对应的**match.length**属性中
- **regexec**返回一个数组， **regexec**返回一个列表，列表中每个元素仅包含一个值，**gregexpr**也返回一个列表，但列表中每个元素可以包含多个值，

```R
> regexpr("ab", "abcabc")
[1] 1
attr(,"match.length")
[1] 2
> regexec("ab", "abcabc")
[[1]]
[1] 1
attr(,"match.length")
[1] 2
> gregexpr("ab", "abcabc")
[[1]]
[1] 1 4
attr(,"match.length")
[1] 2 2
```

<br>

### 2.3、正则替换

n为正整数，仅用于正则替换，表示引用正则表达式中第n个子表达式

如果我们需要将字符串（或字符串数组）**x**中符合特定模式**pattern**的内容，替换为另外的内容**replacement**，则可以使用函数{{< hl-text primary >}}sub、gsub{{< /hl-text >}}。其中**sub**只会对**x**中的每个元素替换一次，而**gsub**则会替换所有符合**pattern**的内容。此外如果我们在**pattern**中定义了子表达式，则可以使用`\\n`的形式，在**replacement**中引用第**n**个子表达式所对应的内容。

```R
> sub("(ab)c", "\\1" , "abc ABC")
[1] "ab ABC"
> gsub("ab", "C" , "abc abc")
[1] "Cc Cc"
```

<br>

### 2.4、取正则匹配结果

有时我们进行正则匹配并不是想要获取匹配的起始位置和匹配长度，而只是想要获取匹配的内容，或者替换匹配的内容。那么此时我们就可以使用{{< hl-text primary >}}regmatches{{< /hl-text >}}函数。**regmatches**需要以原始字符串、匹配结果作为参数，可以直接返回匹配的内容。

```R
> x <- "abc ABC"
> m <- regexpr("ab", x)
> regmatches(x, m)
[1] "ab"
> m <- gregexpr("ab", x, ignore.case = TRUE)
> regmatches(x, m)
[[1]]
[1] "ab" "AB"
> regmatches(x, m) <- "C"; x
[1] "Cc CC"
```

<br>

## 3、模糊查找匹配

模糊查找与模糊匹配可以从字符串（或字符串数组）中查找匹配与某个模式 *最相符* 的内容，但模糊查找与模糊匹配也需要遵守一定的规则，合理运用这些规则可以帮我们提高查找匹配的效率。

<br>

### 3.1、计算字符串相似度

假设字符串**x**最少需要插入**a**次、删除**b**次、替换**c**次才能与字符串**y**相同，则**x、y**之间的 *距离* 即**a、b、c**的加权总和。比如将"kitten"转化为"sitting"，需要把“k”替换为“s”，把“e”替换为“i”，并在尾部插入“g”，所以共需1次插入、0次删除、2次替换，按照默认权重两者之间 *距离* 英该为3。

在R语言中，我们可以使用{{< hl-text primary >}}adist(x, y = NULL, costs = NULL, counts = FALSE, ...){{< /hl-text >}}的形式，计算字符串之间的距离。其中：

- **costs**即插入（**insertions**）、删除（**deletions**）、替换（**substitutions**）次数的权重
- **counts**表示是否输出插入、删除、替换次数
- **partial**表示是否只进行局部匹配

```R
> drop(attr(adist("kitten", "sitting", counts = TRUE), "counts"))
ins del sub 
  1   0   2
> adist("lasy", "1 lazy 2", partial = TRUE)
     [,1]
[1,]    1
```

<br>

### 3.2、模糊查找

我们可以通过{{< hl-text primary >}}agrep、agrepl{{< /hl-text >}}函数，进行模糊查找，这两个函数支持的参数与**grep\***家族函数的参数类似，此外还拥有两个特有参数：

- **costs**即插入、删除、替换次数的权重，参考**adist**
- **max.distance**即可以接受的最大距离，可以是插入、删除、替换的最大次数，也可以是三者之和（**alll**）的最大值，还可以是三者加权总和（**cost**）的最大值

```R
> agrep("lasy", c(" 1 lazy 2", "1 lasy 2"), max = list(sub = 0))
[1] 2
> agrep("laysy", c("1 lazy", "1", "1 LAZY"), max = 2, value = TRUE)
[1] "1 lazy"
```

<br>

### 3.3、模糊匹配

上文我们已经介绍了使用正则表达式的匹配规则，以及 **agrep\***家族函数的模糊查找规则，类似的我们可以通过{{< hl-text primary >}}aregexec{{< /hl-text >}}函数，进行模糊匹配。

```R
> x <- c("1 lazy", "1", "1 LAZY")
> aregexec("laysy", x, max.distance = 2)
[[1]]
[1] 3
attr(,"match.length")
[1] 4

[[2]]
[1] -1
attr(,"match.length")
[1] -1

[[3]]
[1] -1
attr(,"match.length")
[1] -1
> m <- aregexec("(lay)(sy)", x, max.distance = 2)
> regmatches(x, m)
[[1]]
[1] "lazy" "la"   "zy"  

[[2]]
character(0)

[[3]]
character(0)
```

<br>

## 4、字符与编码

- **二进制字符**，计算机中的字符，本质上都是以一串二进制数据存储，通过特定的编码方式呈现在读者面前的。在R语言中，我们可以通过{{< hl-text primary >}}charToRaw、rawToChar{{< /hl-text >}}函数，在字符串与二进制数组之间互相转换。

- **字符编码**，有时候我们从外部读如字符串数据，有可能因为编码设置不正确而显示乱码。此时我们可以通过{{< hl-text primary >}}Encoding{{< /hl-text >}}函数，查看并设置字符的编码。

- **字符转码**，有时候我们遇到乱码不是因为字符编码设置的不正确，而是当前计算机操作系统不支持以特定的编码方式显示字符。此时我们可以使用{{< hl-text primary >}}iconv(x, from, to, ...){{< /hl-text >}}的形式，将字符从一种编码方式转化为另一种编码方式。

```R
> x <- "abc\xE7"
> charToRaw(x)
[1] 61 62 63 e7
> Encoding(x) <- "latin1"; x
[1] "abcç"
> iconv("abc\xE7", "latin1", "UTF-8")
[1] "abcç"
```

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 正则表达式`[^(ab)]`与`[^a^b]`有什么区别？
- `agrep(..., costs = 1, max = list(sub = 2, ins = 1, del = 3, cost = 2))`能够匹配的字符 *距离* 是多少？
- 修改字符串**x**的**Encoding**与对字符串进行转码（**iconv**）有什么区别？
{{< /note >}}

<br>
