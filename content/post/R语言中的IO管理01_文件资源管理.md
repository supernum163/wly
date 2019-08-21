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

绝对路径需要从文件系统**根目录**写起，写明需要从根目录开始依次向下查找的文件/文件夹的名称，并使用**路径分割符**将这些名称分割开来。对于linux系统而言，根目录与路径分割符都是英文斜杠——{{< hl-text red >}}/{{< /hl-text >}}，所以路径应该类似`/home/wly/Downloads/tmp.R`；而对于window系统而言，根目录是计算机中的某个磁盘，比如{{< hl-text red >}}C:\{{< /hl-text >}}，路径分割符是英文反斜杠——{{< hl-text red >}}\{{< /hl-text >}}，路径应该类似`C:\\Users\\wly\\Downloads\\tmp.R`（注意R语言的字符串中必须用两个反斜杠来表示一个反斜杠字符）。

相对路径指的是相对某个路径开始查找文件/文件夹。大部分语言都支持在文件中，以文件所在的文件夹为相对路径，但是R语言中的相对路径只能是当前**工作路径**。我们可以分别使用{{< hl-text primary >}}getwd、setwd{{< /hl-text >}}函数，来获取、设置R语言的工作路径。

此外，我们还可以使用以下方式快速定位文件路径：{{< hl-text blue >}}~/{{< /hl-text >}}表示当前**用户主目录**（仅用于linux），{{< hl-text blue >}}./{{< /hl-text >}}表示当前工作路径（可省略），{{< hl-text blue >}}../{{< /hl-text >}}表示某个路径的**上层目录**。

R语言中为了规避操作系统之间的差异，在程序启动时会自动装载一些系统变量，比如
{{< hl-text blue >}}.Platform{{< /hl-text >}}中记录了当前操作系统中的路径分割符等信息（此外还有{{< hl-text blue >}}.Machine{{< /hl-text >}}），所以我们可以使用{{< hl-text primary >}}file.path{{< /hl-text >}}函数拼接路径，此时路径分割符会根据特定的操作系统自动完善。

如果我们需要寻找R语言系统文件的路径，{{< hl-text primary >}}R.home{{< /hl-text >}}函数可以帮助我们找到R语言的安装目录，{{< hl-text blue >}}.Library{{< /hl-text >}}是程序包的默认安装位置，{{< hl-text blue >}}.Library.site{{< /hl-text >}}是本地程序包的寻找位置。当然我们也可以使用{{< hl-text primary >}}system.file(..., package){{< /hl-text >}}的形式，快速定位某个程序包中的文件。

<br>

## 2、file家族函数

| 函数            | 解释说明                                                      
|:----------------|:--------
| list.files      | 列举某个目录下的文件/文件夹，可以递归列举，可以使用正则表达式列举
| dir             | 同**list.files**
| list.dirs       | **list.files**的简洁版
| file.create     | 创建文件
| file.exists     | 判断文件/文件夹是否存在
| file.remove     | 删除文件/文件夹
| file.rename     | 重命名文件/文件夹
| file.append     | 将**第2个文件**中的内容追加到**第1个文件**中
| file.copy       | 复制文件/文件夹，可以复制并替换，可以复制整个目录
| file.symlink    | 创建指向文件/文件夹的**软链接**
| file.link       | 创建指向文件的**硬链接**，必须在同一个文件系统内创建
| file.info       | 文件/文件夹属性
| file.mode       | 文件/文件夹权限，同**file.info**中的**mode**
| file.mtime      | 文件/文件夹修改时间，同**file.info**中的**mtime**
| file.size       | 文件/文件夹占用空间（字节），同**file.info**中的**size**
| dir.exists      | 判断文件夹是否存在
| dir.create      | 创建文件夹，可以递归创建尚不存在的所有父文件夹
| Sys.chmod       | 修改文件/文件夹权限
| Sys.umask       | 设置文件/文件夹创建时的默认权限
| unlink          | 删除文件/文件夹，可以递归删除，可以强制删除
| basename        | 获取文件名，包含**文件扩展名**
| dirname         | 获取路径名
| path.expand     | 将路径中的**~/**替换为用户主目录
| normalizePath   | 将相对路径转化为绝对路径









<br>

## 4、压缩、解压缩


## 5、stdout、stderr、file

## 3、sink与io流

## 6、read、write

<br>

{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
