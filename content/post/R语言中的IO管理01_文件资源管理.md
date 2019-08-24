---
title: R语言中的文件资源管理
date: 2019-08-27
categories:
  - R语言
  - IO管理
tags:
  - R语言IO管理
keywords:
  - R语言
  - IO管理
  - 文件资源管理
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/08/17/muddIA.png
---

文件资源管理是一门计算机语言，通过对文件或文件夹的**查看**、**新建**、**修改**、**删除**，对资源的**连接**，**读写**，**关闭**等操作，管理自身输入输出的基础。这篇文章我们将介绍R语言中的**文件资源管理**。

<!--more-->

<!-- toc -->

<br>

## 1、文件/文件夹路径

在计算机中定位一个**文件/文件夹**，我们既可以使用**绝对路径**，也可以使用**相对路径**。

绝对路径需要从文件系统**根目录**写起，写明需要从根目录开始依次向下查找的文件/文件夹的名称，并使用**路径分割符**将这些名称分割开来。对于linux系统而言，根目录与路径分割符都是英文斜杠——{{< hl-text red >}}/{{< /hl-text >}}，所以路径应该类似`/home/wly/Downloads/tmp.R`；而对于window系统而言，根目录是计算机中的某个磁盘，比如{{< hl-text red >}}C:\{{< /hl-text >}}，路径分割符是英文反斜杠——{{< hl-text red >}}\{{< /hl-text >}}，路径应该类似`C:\\Users\\wly\\Downloads\\tmp.R`（注意R语言的字符串中必须用两个反斜杠来表示一个反斜杠字符），不过在最新版的R语言中，window操作系统下也支持用英文斜杠作为路径分割符。

相对路径指的是相对某个路径开始查找文件/文件夹。大部分语言都支持在文件中，以文件所在的文件夹为相对路径，但是R语言中的相对路径只能是当前**工作路径**。我们可以分别使用{{< hl-text primary >}}getwd、setwd{{< /hl-text >}}函数，来获取、设置R语言的工作路径。

此外，我们还可以使用以下方式快速定位文件路径：{{< hl-text blue >}}~/{{< /hl-text >}}表示当前**用户主目录**（仅用于linux），{{< hl-text blue >}}./{{< /hl-text >}}表示当前工作路径（可省略），{{< hl-text blue >}}../{{< /hl-text >}}表示某个路径的**上层目录**。

R语言中为了规避操作系统之间的差异，在程序启动时会自动装载一些系统变量，比如
{{< hl-text blue >}}.Platform{{< /hl-text >}}中记录了当前操作系统中的路径分割符等信息（此外还有{{< hl-text blue >}}.Machine{{< /hl-text >}}），所以我们可以使用{{< hl-text primary >}}file.path{{< /hl-text >}}函数拼接路径，此时路径分割符会根据特定的操作系统自动完善。

如果我们需要寻找R语言系统文件的路径，{{< hl-text primary >}}R.home{{< /hl-text >}}函数可以帮助我们找到R语言的安装目录，{{< hl-text blue >}}.Library{{< /hl-text >}}是程序包的默认安装位置，{{< hl-text blue >}}.Library.site{{< /hl-text >}}是本地程序包的寻找位置。当然我们也可以使用{{< hl-text primary >}}system.file(..., package){{< /hl-text >}}的形式，快速定位某个程序包中的文件。

<br>

## 2、文件/文件夹管理相关函数

在图形化界面中，我们一定会经常对文件/文件夹进行查看、新建、修改、删除等操作，相应的操作也可以在命令行中完成。R语言中融合了不同操作系统命令行下的文件/文件夹管理方式，比如文件/文件夹列举，在**bash**命令行中对应**ls**命令，在R语言中就有相应的**list.files**函数（R语言中的**ls**函数已被定义为列举执行环境中的变量）；在**cmd**命令行中对应**dir**命令，在R语言中就有相应的**dir**函数。注意R语言中名称以英文句点——{{< hl-text red >}}.{< /hl-text >}}开头的文件/文件夹会被认为是隐藏的，例举时默认不显示。我们需要设定列举函数中的参数`all.files = TRUE`来显示这些隐藏内容。

R语言中的文件/文件夹管理函数往往功能直观，使用起来非常简单。虽然部分功能还不是特别完善，比如打包/压缩管理中不能使用密码，但是已经足够应对日常的文件/文件夹管理了。

|                 | 函数            | 解释说明                                                      
|:----------------|:----------------|:-----------------------------------------------------------------------
| 文件/文件夹列举 | list.files      | 列举某个目录下的文件/文件夹，可以递归列举，可以使用正则表达式列举
|                 | dir             | 同**list.files**
|                 | list.dirs       | **list.files**的简洁版
|                 | Sys.glob        | 根据操作系统的模糊查找法，列举所有符合特定模式的文件/文件夹
| 文件/文件夹属性 | file.info       | 文件/文件夹属性
|                 | file.mode       | 文件/文件夹权限，同**file.info**中的**mode**
|                 | file.mtime      | 文件/文件夹修改时间，同**file.info**中的**mtime**
|                 | file.size       | 文件/文件夹占用空间（字节），同**file.info**中的**size**
| 文件/文件夹管理 | file.create     | 创建文件
|                 | file.exists     | 判断文件/文件夹是否存在
|                 | file.remove     | 删除文件/文件夹
|                 | file.rename     | 重命名文件/文件夹
|                 | file.append     | 将**第2个文件**中的内容追加到**第1个文件**中
|                 | file.copy       | 复制文件/文件夹，可以复制并替换，可以复制整个目录
| 超链接管理      | file.symlink    | 创建指向文件/文件夹的**软链接**
|                 | file.link       | 创建指向文件的**硬链接**，必须在同一个文件系统内创建
| 文件夹管理      | dir.create      | 创建文件夹，可以递归创建尚不存在的所有父文件夹
|                 | dir.exists      | 判断文件夹是否存在
|                 | unlink          | 删除文件/文件夹，可以递归删除，可以强制删除
| 权限管理        | Sys.chmod       | 修改文件/文件夹权限
|                 | Sys.umask       | 设置文件/文件夹创建时的默认权限
| 路径管理        | basename        | 获取文件名，包含**文件扩展名**
|                 | dirname         | 获取路径名
|                 | path.expand     | 将路径中的**~/**替换为用户主目录
|                 | normalizePath   | 将相对路径转化为绝对路径
|                 | file.path       | 将多个字符串拼接成路径
| 打包/压缩管理   | zip             | 将一个或多个文件/文件夹打包为zip压缩包
|                 | unzip           | 解压缩zip压缩包
|                 | tar             | 将一个或多个文件/文件夹打包为tar压缩包（.tar.gz、.tar.bz、.tar.xz等）
|                 | untar           | 解压缩tar压缩包

<br>

## 3、资源管理基础

### 3.1、资源管理权限

在建立资源管理链接之前，我们必须了解资源的管理权限，否则有可能无法建立链接或者出现意料之外的结果。一般而言，资源链接可以分为**字符流**链接和**字节流**链接，前者以单个字符为最小单位从资源中读写数据，后者则以单个字节为最小单位。其次，我们可以对资源进行**读取**、**写入**、**追加**等操作，不同的操作模式拥有各自潜在的规则，具体如下：

| 字符流          | 字节流          | 相应权限                                                      
|:----------------|:----------------|:-----------------------------------------------------------------------
| r 或 rt         | rb              | 读取，文件必须存在
| w 或 wt         | wb              | 写入，文件不存在则新建，文件已存在则删除文件中的内容
| a 或 at         | ab              | 追加，文件不存在则新建，文件已存在则从文档末尾开始写入
| r+              | r+b             | 读取与写入，文件必须存在
| w+              | w+b             | 读取与写入，文件不存在则新建，文件已存在则删除文件中的内容
| a+              | a+b             | 读取与追加，文件不存在则新建，文件已存在则写入时从文档末尾开始

<br>

### 3.2、建立资源链接

R语言中支持与多种类型的资源建立链接（见下表），如果使用第三方程序包，还可以建立更多类型的链接。不同类型的资源，相应的管理方式略有不同。比如函数url建立的网络资源（以**http**、**https**、**ftp**协议传输的文件）只能接受读取，以函数unz建立的资源（对zip压缩包中某个文件的链接）只能接受字节流形式的读取，以函数socketConnection建立的链接必须服务端与客户端同时在线才能读写。以下是这些函数中可能用到的关键参数：

- **description**参数，即资源的描述信息，比如文件路径、网络地址等
- **open**参数，即上文提到的资源管理权限
- **encoding**参数，用于指明输入输出时需要用到的编码，只在字符流形式的资源链接中有效，默认情况下会使用**本地编码**（**native.enc**），所以一般情况下不需要设置，除非读写与操作系统默认编码不同的资源（比如在window下读写linux中的文件）。


| 函数              | 解释说明                                                      
|:------------------|:-----------------------------------------------------------------------
| file              | 文件资源链接
| url               | 网路资源链接
| gzfile            | gz压缩文件资源链接
| bzfile            | bz压缩文件资源链接
| xzfile            | xz压缩文件资源链接
| unz               | 压缩文件中的某个文件资源链接
| pipe              | 标准IO流
| fifo              | 先入先出IO流
| socketConnection  | 网络套接字资源链接

For file the description is a path to the file to be opened or a complete URL (when it is the same as calling url), or "" (the default) or "clipboard" (see the ‘Clipboard’ section). U

se "stdin" to refer to the C-level ‘standard input’ of the process (which need not be connected to anything in a console or embedded version of R, and is not in RGui on Windows). See also stdin() for the subtly different R-level concept of stdin. See nullfile() for a platform-independent way to get filename of the null device.

If for a file or (on most platforms) a fifo connection the description is "", the file/fifo is immediately opened (in "w+" mode unless open = "w+b" is specified) and unlinked from the file system. This provides a temporary file/fifo to write to and then read from. 

重点介绍file函数

socket示例

<br>

### 3.3、管理资源链接

| 函数            | 解释说明                                                      
|:----------------|:-----------------------------------------------------------------------
| open            | 与某个资源建立链接
| close           | 关闭资源链接
| flush           | 将缓存的输出流写入资源
| isOpen          | 判断资源链接是否开启
| isIncomplete    | 判断资源链接中是否存在未完成的IO流

## 5、stdout、stderr、sink、gzcon

## 6、read、write

- readChar、writeChar
- readBin、writeBin

<br>

{{< note "思考思考" "#e6e6ff" >}}
- R语言中的打包/压缩管理函数大多是调用命令行完成的吗 ？

{{< /note >}}

<br>
