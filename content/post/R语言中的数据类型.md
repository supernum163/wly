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
thumbnailImage: https://i.postimg.cc/nhmB7j7T/image.png
---

在**R语言**中一切皆为**对象**，不同类型的对象，其表现形式却又千差万别。对于一个新手来讲，理清R语言中不同对象的区别与关联确实不易。这篇文章及后续系列将深入剖析R语言中的对象。
<!--more-->

<!-- toc -->

R语言中的底层代码都是由**C/C++**直接实现的，在R语言中所有的数据结构，无论是数组、列表，还是函数、操作符，本质上都是一个指针（**SEXP**）指向特定的数据（**SEXPREC**结构体）。

**SEXPREC**结构体由两大部分组成，一部分是_头信息_（**SEXPREC_HEADER**），另一部分是_数据_。

## 存储类型与数据结构

### typeof

### mode、storage.mode

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

{{< /note >}}

<br>
