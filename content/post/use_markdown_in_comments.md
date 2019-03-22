---
title: "在评论区使用markdown语法"
date: 2019-03-22
categories:
- markdown
- 评论区
tags:
- markdown
thumbnailImagePosition: left
thumbnailImage: 
---

**markdown**是一款轻量级网页内容生成语法，使用markdown语法，你可以轻松生成图文并茂的网页内容。这篇文章将带你了解如何在评论区使用markdown语法。
<!--more-->

<!-- toc -->

# 1、markdown语法

不同的**markdown语法解释器**对于markdown语法的支持会略有不同，但基本语法都大体相似。这里我们使用的**gitment评论系统**使用的是**github**的markdown语法解释器，你可以在[这里](https://guides.github.com/features/mastering-markdown/)查看github对其markdown语法解释器的官方说明。以下内容是根据我个人的理解对markdown语法的归纳总结。

## 1.1、标题语法

{{< codeshow >}}
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
{{< /codeshow >}}

## 1.2、文字、段落语法
``
你可以使用**粗体字**或者__粗体字__的形式加粗字体，使用*斜体字*或者_斜体字_的形式使字体倾斜，使用-~~删除线~~的形式在文字中`插入一条删除线`。使用[超链接](https://wly.supernum.tech)的形式插入超链接
``

{{< codeshow >}}
**粗体字**, __粗体字__
*斜体字*, _斜体字_
~~删除线~~
`行内代码`
[超链接](https://wly.supernum.tech)
{{< /codeshow >}}


## 1.3、引用语法

{{< codeshow >}}
> 引用书记中的名言或网页内容
> ——引用来源
{{< /codeshow >}}

## 1.4、代码块语法

{{< codeshow >}}
```
<html>
  <head>
    <meta charset="UTF-8">
    <title>Document</title>
  </head>
  <body>
    Hello World！
  </body>
</html>
```
{{< /codeshow >}}

## 1.5、图片、超链接语法

{{< codeshow >}}
![插入图片](https://octodex.github.com/images/yaktocat.png)
{{< /codeshow >}}

## 1.6、列表语法

### 1.6.1、有序列表

{{< codeshow >}}
1. 列表内容1
2. 列表内容2
3. 列表内容3
{{< /codeshow >}}

### 1.6.2、无序列表

{{< codeshow >}}
- 列表内容1
  - 子列表内容1
  - 子列表内容2
{{< /codeshow >}}

### 1.6.3、任务列表（gihub特有）

{{< codeshow >}}
- [x] 已完成任务
- [ ] 未完成任务
{{< /codeshow >}}

## 1.7、表格语法

{{< codeshow >}}
|   第一列   |    第二列    |
|:-----------|:------------:|
| 使用左对齐 | 使用居中对齐 |
|            | 占位符       |
{{< /codeshow >}}

## 1.8、其它github特有的markdown语法

### 1.8.1、回应某人或某条评论

你可以在评论区中@某人，或者#某个评论编号，你指名的内容将自动成为超链接。

### 1.8.2、使用Emojj表情

你可以使用`:[emojj名称]:`的格式插入Emojj表情，比如使用`see_no_evil`, `hear_no_evil`, `speak_no_evil`分别插入非礼勿视:see_no_evil:、非礼勿听:hear_no_evil:、非礼勿言:speak_no_evil:三个表情。你可以在[这里](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md)查看评论区支持的所有Emojj名称。

## 1.9、语法结合

{{< codeshow >}}
- [刷新页面](/)
- [返回列表测试](#列表测试)
{{< /codeshow >}}

# 2、使用html标签

{{< codeshow >}}
H<sub>2</sub>O
{{< /codeshow >}}

# 3、结语

至此评论区的markdown语法基本上已经介绍完了，如果有遗漏或者介绍不当的地方，欢迎直接反馈给我。评论编辑器支持实时查看输入的markdown语法的展示结果，快来试试吧。




