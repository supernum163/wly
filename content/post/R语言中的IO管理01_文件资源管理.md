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

绝对路径需要从文件系统**根目录**写起，写明需要从根目录开始依次向下查找的文件/文件夹的名称，并使用**路径分割符**将这些名称分割开来。对于linux系统而言，根目录与路径分割符都是英文斜杠——**/**，所以路径应该类似`/home/wly/Downloads/tmp.R`；而对于window系统而言，根目录是计算机中的某个磁盘，比如**C:\**，路径分割符是英文反斜杠——**\**，路径应该类似`C:\\Users\\wly\\Downloads\\tmp.R`（注意R语言的字符串中必须用两个反斜杠来表示一个反斜杠字符）。















```R

```

## 2、file家族函数

list.files(path = ".", pattern = NULL, all.files = FALSE,
           full.names = FALSE, recursive = FALSE,
           ignore.case = FALSE, include.dirs = FALSE, no.. = FALSE)

       dir(path = ".", pattern = NULL, all.files = FALSE,
           full.names = FALSE, recursive = FALSE,
           ignore.case = FALSE, include.dirs = FALSE, no.. = FALSE)

list.dirs(path = ".", full.names = TRUE, recursive = TRUE)

file.create(..., showWarnings = TRUE)
file.exists(...)
file.remove(...)
file.rename(from, to)
file.append(file1, file2)
file.copy(from, to, overwrite = recursive, recursive = FALSE,
          copy.mode = TRUE, copy.date = FALSE)
file.symlink(from, to)
file.link(from, to)

file.info(..., extra_cols = TRUE)
file.mode(...)
file.mtime(...)
file.size(...)

file.access
file.choose
util::file.edit 
file.show

file.path

dir.exists(paths)
dir.create(path, showWarnings = TRUE, recursive = FALSE, mode = "0777")
Sys.chmod(paths, mode = "0777", use_umask = TRUE)
Sys.umask(mode = NA)

## 4、压缩、解压缩


## 5、stdout、stderr、file

## 3、sink与io流

## 6、read、write

<br>

{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
