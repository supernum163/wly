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
  - 文件资源管理
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/08/04/eytzEn.png
---

这篇文章我们将介绍R语言中的**文件资源管理**。

<!--more-->

<!-- toc -->


<br>

## 1、文件路径

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

## 5、stdout、stderr、file

## 3、sink与io流

## 4、压缩、解压缩

## 6、read、write

<br>

{{< note "思考思考" "#e6e6ff" >}}
- ？

{{< /note >}}

<br>
