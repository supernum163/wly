---
title: "R语言与日期时间管理"
date: 2019-06-01
categories:
  - R语言
  - 数据类型
tags:
  - R语言数据类型
keywords:
  - R语言
  - 数据类型
  - 日期时间管理
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/wxS2XdHW/4.png
---

**日期时间**作为日常生活中必不可少的一类信息，在数据分析中也有着非常重要的意义（尤其对于**时序分析**而言）。这篇文章将介绍**R语言**中的**日期时间**管理。

<!--more-->

<!-- toc -->

## 1、日期时间类对象

首先我们可以分别通过{{< hl-text primary >}}Sys.Date、Sys.time{{< /hl-text >}}函数，获取系统当前**日期**与当前**时间**。其中时间类的显示结果总是以某些特定的英文缩写作为后缀，代表的是时区（比如**GST**代表的是本地时间，**GMT**代表的是**格林威治时间**）。

在R语言中，日期类对象本质上是以数值的形式存储的（数值的含义是当前日期距离**1970-01-01**差多少天），拥有的类属性（class属性）为**Date**。

时间类对象则可以分为两类：其中拥有类属性**POSIXct**的对象,本质上是以数值的形式存储时间对象，数值代表当前时间距离**1970-01-01 00:00:00 GMT**差多少秒；而拥有类属性**POSIXlt**的对象，本质上是以列表的形式存储时间对象，列表中的元素**sec、min、hour、mday、mon、year、wday、yday、isdst、zone、gmtoff**分别代表秒、分、时、日、月、年（距离**1900**年差多少年）、星期、一年中的第几天、是否为夏令时、时区、当前时间距离格林威治时间差多少秒。两类对象都拥有类属性**POSIXt**，所以两者在R语言中是可以通用的。

注意因为R语言中重写了**POSIXlt**类对象的**print、str、as.list**等函数，所以我们必须通过特别的函数才能取出**POSIXlt**类对象的各个元素，比如筛选数据框元素的**[]**符号，或者{{< hl-text primary >}}[、unclass、unlist{{< /hl-text >}}等函数。

```R
> Sys.Date()
[1] "2019-06-01"
> Sys.time()
[1] "2019-06-01 09:26:27 CST"
> cat(Sys.Date(), Sys.time())
18048 1559352387
> x <- as.POSIXlt(Sys.time()); as.data.frame(unclass(x), row.names = "")
     sec min hour mday mon year wday yday isdst zone gmtoff
 27.0458  56   13   31   4  119    5  150     0  CST  28800
```

<br>

