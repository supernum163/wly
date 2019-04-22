---
title: "使用R语言对矩阵进行数学运算"
date: 2019-04-28
math: true
categories:
  - R语言
  - 数学运算
tags:
  - R语言数学运算
keywords:
  - R语言
  - 数学运算
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/Pf69QcfK/R.png
---

**R语言**作为一门专为统计分析诞生的语言，数学运算自然是必不可少的。这篇文章将介绍R语言是如何对**矩阵**进行数学运算的。
<!--more-->

<!-- toc -->

<br>

# 1、什么是矩阵  

在R语言中，**Matrix**（矩阵）是一个由行列结构组成的数据对象。与[数组](https://wly.supernum.tech/2019/04/使用R语言对数组进行数学运算/#1-什么是数组 )不同的是，矩阵是二维数据对象，而数组是一维数据对象。所以我们可以结合使用矩阵的**行下标**、**列下标**，来筛选出矩阵中的特定元素。

在R语言中除了[数字](https://wly.supernum.tech/2019/04/使用R语言对数字进行数学运算)（0维）、[数组](https://wly.supernum.tech/2019/04/使用R语言对数组进行数学运算)（1维）、矩阵(#)（2维），还存在更高维度的数据对象——**Array**（高纬矩阵）。高纬矩阵在其每一个维度上都拥有相应的**维度下标**和取值，我们可以通过特定维度的下标获取相应的取值。

注意R语言中的矩阵与纯数学意义上的矩阵有所不同，在R语言中矩阵仅是一种数据对象的存储方式，它除了可以存储数字，还可以存储字符串、逻辑值等各种元素。这一点我们会在之后总结R语言中的数据对象时再详细介绍。

<br>

# 取对角矩阵、上下三角
diag, diag<-, isSymmetric, isSymmetric.matrix, lower.tri, upper.tri, 

使用`diag(1, n)`生成**单位矩阵**

# 矩阵内积、外积、交叉
%*%, %o%, crossprod, tcrossprod,  %x%, .kronecker, kronecker, outer, 

# 解矩阵 （A %*% X = B, 求B）
solve, solve.default, solve.qr, 

## 求矩阵的逆

$AB = BA = M$, 其中M为单位矩阵， 则A、B互为**逆矩阵**。`solve(A, diag(1, nrow(A)))`。

# 计算特征值、特征矩阵、行列式
eigen, det, determinant, determinant.matrix,

# qr分解
qr, qr.coef, qr.default, qr.fitted, qr.Q, qr.qty, qr.qy, qr.R, qr.resid, qr.solve, qr.X, 

# svd分解
La.svd, svd, 

# Choleski分解
chol, chol.default, chol2inv,

# 矩阵条件数、范数
.kappa_tri, kappa, kappa.default, kappa.lm, kappa.qr, norm, 

# 6、结语

至此我们已经分别总结了R语言中如何对各种由数字组成的**数据对象**进行数学运算。当然R语言中还可以对一些其它类型的数据对象进行数学运算，这点我们会在之后总结相应的数据对象时介绍到。

{{< note "思考思考" "#e6e6ff" >}}

{{< /note >}}

<br>
