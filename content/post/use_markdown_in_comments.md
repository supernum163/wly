---
title: "在评论区使用markdown语法"
date: 2019-03-22
categories:
  - markdown
  - 评论区
tags:
  - markdown
keywords:
  - markdown
thumbnailImagePosition: left
thumbnailImage: https://i.postimg.cc/jq8Hrrt6/Markdown-01.png
---

**markdown**是一款轻量级网页内容生成语法，使用markdown语法，你可以轻松生成图文并茂的网页内容。这篇文章将带你了解如何在评论区使用markdown语法。
<!--more-->

<!-- toc -->

<br>

# 1、markdown语法

不同的**markdown语法解释器**对于markdown语法的支持会略有不同，但基本语法都大体相似。这里我们使用的**gitment评论系统**使用的是**github**的markdown语法解释器，你可以在[这里](https://guides.github.com/features/mastering-markdown/)查看github对其markdown语法解释器的官方说明。

以下内容是根据我个人的理解对markdown语法的归纳总结。其中，在**代码与效果对比框**中，背景色为灰色的部分是markdown语法格式，背景色为白色的部分是markdown语法效果。  

<br>

## 1.1、标题语法

你可以使用{{< hl-text primary >}}# 标题名称{{< /hl-text >}}的格式插入标题，其中{{< hl-text primary >}}#{{< /hl-text >}}的数量代表标题级别，这里仅支持一至六级标题。

{{< codeshow >}}
# 一级标题
## 二级标题
### 三级标题
#### 四级标题
##### 五级标题
###### 六级标题
{{< /codeshow >}}

<br>

## 1.2、文字、段落语法

你可以使用{{< hl-text primary >}}**粗体字**{{< /hl-text >}}或者{{< hl-text primary >}}__粗体字__{{< /hl-text >}}的格式加粗字体，使用{{< hl-text primary >}}*斜体字*{{< /hl-text >}}或者{{< hl-text primary >}}_斜体字_{{< /hl-text >}}的格式使字体倾斜，使用{{< hl-text primary >}}~~删除线~~{{< /hl-text >}}的格式在文字中插入一条删除线，使用{{< hl-text primary >}}`行内代码`{{< /hl-text >}} 的格式插入行内代码，使用{{< hl-text primary >}}[超链接](链接地址){{< /hl-text >}}的格式插入超链接。

对于段落而言，如需新开一行必须在上一行末尾插入两个空格，如需新开一个段落则需要先插入一个空行，注意markdown不支持通过换行符插入多个空行。

{{< codeshow >}}
- **粗体字**, __粗体字__
- *斜体字*, _斜体字_
- ~~删除线~~
- `行内代码`
- [超链接](https://wly.supernum.tech)
{{< /codeshow >}}

<br>

## 1.3、引用语法

你可以使用{{< hl-text primary >}}> 应用内容{{< /hl-text >}}的格式插入引用的内容，引用的时候请注明来源。

{{< codeshow >}}
> 引用他人的言论或网页、书籍中的内容
> ——引用来源
{{< /codeshow >}}

<br>

## 1.4、代码块语法

如果你需要插入多行代码，可以使用{{< hl-text primary >}}```{{< /hl-text >}}作为代码的首行和尾行，如需高亮代码，则可以在首行的{{< hl-text primary >}}```{{< /hl-text >}}之后标明代码类型。

{{< codeshow >}}
```html
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

<br>

## 1.5、图片语法

你可以使用{{< hl-text primary >}}![图片Alt](图片链接地址){{< /hl-text >}}的格式插入一幅图片，注意图片与超链接的语法区别。你也可以直接拖放一张图片至评论区，图片代码将会自动生成。

{{< codeshow >}}
![图片Alt](https://i.postimg.cc/CLzjh6x3/Markdown-02.png)
{{< /codeshow >}}

<br>

## 1.6、列表语法

你可以使用{{< hl-text primary >}}数字编号. 列表内容{{< /hl-text >}}的格式插入有序列表，使用{{< hl-text primary >}}- 列表内容{{< /hl-text >}}的格式插入无序列表，使用{{< hl-text primary >}}- [ ] 列表内容{{< /hl-text >}}的格式插入任务列表，如需表示任务已完成，可以在方括弧内输入一个英文字母{{< hl-text primary >}}x{{< /hl-text >}}。如需插入多级列表，则需要在子列表之前输入两个空格。

- 有序列表

{{< codeshow >}}
1. 列表内容1
2. 列表内容2
3. 列表内容3
{{< /codeshow >}}

- 无序列表

{{< codeshow >}}
- 列表内容1
  - 子列表内容1
  - 子列表内容2
{{< /codeshow >}}

- 任务列表（gihub特有）

{{< codeshow >}}
- [x] 已完成任务
- [ ] 未完成任务
{{< /codeshow >}}

<br>

## 1.7、表格语法

如需插入表格，则需要以{{< hl-text primary >}} | {{< /hl-text >}}来区分不同的列，以换行来区分不同的行，以多个{{< hl-text primary >}}-{{< /hl-text >}}来区分表头与表格内容，以{{< hl-text primary >}}:--{{< /hl-text >}}、{{< hl-text primary >}}--:{{< /hl-text >}}、{{< hl-text primary >}}:--:{{< /hl-text >}}来分别表示左对齐、右对齐和剧中对齐。

{{< codeshow >}}
| 第一列 | 第二列 |
|:--------|:-------:|
| 使用左对齐 | 使用居中对齐 |
|             | 占位符       |
{{< /codeshow >}}

<br>

## 1.8、其它github特有的markdown语法

### 1.8.1、回应某人

你可以使用{{< hl-text primary >}}@github账户名{{< /hl-text >}}的格式，来特指某人。这种方式本质上只是生成了一个指向某个github用户主页的超链接，所以你也可以直接使用超链接的格式达到相同的效果。

<br>

### 1.8.2、使用Emojj表情

你可以使用{{< hl-text primary >}}:Emojj名称:{{< /hl-text >}}的格式插入Emojj表情，比如使用**see_no_evil**、 **hear_no_evil**、 **speak_no_evil**三个Emojj名称，分别插入{{< hl-text red >}}非礼勿视{{< /hl-text >}}:see_no_evil:、{{< hl-text red >}}非礼勿听{{< /hl-text >}}:hear_no_evil:、{{< hl-text red >}}非礼勿言{{< /hl-text >}}:speak_no_evil:。你可以在[这里](https://github.com/ikatyang/emoji-cheat-sheet/blob/master/README.md)查看评论区支持的所有Emojj名称。

<br>

## 1.9、语法结合

你可以结合使用不同的markdown语法，比如这里我们使用文字加粗、文字倾斜、超链接、以及列表语法，可以手动生成一个目录。

{{< codeshow >}}
- [**返回顶部**](#)
  - [*返回文字、段落语法*](#1-2-文字-段落语法)
  - [*返回列表语法*](#1-6-列表语法)
{{< /codeshow >}}

<br>

# 2、使用html标签

markdown本质上只是将你输入的内容转化为**html**语言，如果你觉得现有的markdown语法不够丰富，则完全可以直接通过html标签来实现更多功能。

{{< codeshow >}}
2H<sub>2</sub> + O<sub>2</sub> = 2H<sub>2</sub>O
{{< /codeshow >}}

<br>

# 3、结语

至此评论区的markdown语法基本上已经介绍完了，如果有遗漏或者介绍不当的地方，欢迎直接反馈给我。评论编辑器支持实时查看输入的markdown语法的展示结果，快来试试吧。

<br>
