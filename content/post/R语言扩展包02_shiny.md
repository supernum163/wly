---
title: R语言搭建交互式网页应用——shiny
date: 2019-12-30
categories:
  - R语言
tags:
  - R语言扩展包
keywords:
  - R语言
  - 搭建网页应用
  - shiny
thumbnailImagePosition: left
thumbnailImage: https://s2.ax1x.com/2019/12/14/Q2vuCT.png
---

**shiny**是R语言中的一个可交互式的网页应用框架，可以非常便利的使我们从使用者那里接收输入、控制信息，并给使用者展示、反馈需要的信息，这篇文章我们将介绍如何使用**shiny**搭建网页应用。

<!--more-->

<!-- toc -->

<br>

## 1、整体框架

一个简单的**shiny**网页程序框架可以由两部分组成：其中**ui**主要负责网页前端展示，包括定义网页布局、定义接收用户输入的html控件、定义响应用户时输出信息的html控件、定义输出静态信息的html控件等；而**server**则主要负责处理用户输入并返回相应信息，包括即时相应和事件性相应。

因此，**ui**可以是由R语言对象表示的任意tml内容（通常会被放置在**<body>**或**<head>**标签内部），**shiny**中有很多函数都可以生成这样的对象，这些函数往往都是可以嵌套使用的，类似html中的标签。而**server**必须是一个至少能接受两个参数（**input、output**）的函数，这两个参数分别对应以R语言列表表示的用户输入和网页输出信息，在函数中我们只需要处理**input**中传来的信息，并将处理结果返还给**output**。

最后我们只需要将定义好的**ui、server**传递给{{< hl-text primary >}}shinyApp{{< /hl-text >}}函数，即可启动网页应用。

当然我们也可以将以下代码保存到R语言文件（**app.R**）中，通过执行文件，或者使用命令`shinyAppFile(appFile)`，也可以启动网页应用。

```R
library(shiny)
ui <- fluidPage()
server <- function(input, output){}
shinyApp(ui = ui, server = server)
```

此外我们也可以新建一个**shiny**网页应用工程目录，并在**ui.R**和**server.R**文件中，定义**ui、server**，最后再使用命令`shinyAppDir(appDir)`，也可以启动网页应用。此时工程目录中还可以包含以下内容：

- **global.R**文件，用于定义**ui.R**和**server.R**文件中共同使用到的对象
- **DESCRIPTION**文件，当网页应用以***showcase**模式下运行时，展示在页面底部的APP标题、作者等信息。比如：

  ```text
  Title: Hello Shiny!
  Author: RStudio, Inc.
  AuthorUrl: http://www.rstudio.com/
  License: MIT
  DisplayMode: Showcase
  ```
- **README.md**文件，当网页应用以***showcase**模式下运行时，展示在页面底部的说明信息
- **www**文件夹，用于存放网页前端使用的文件（如图片、**CSS、JS**文件等）
- 其它文件/文件夹。如html文件，可以通过URL地址访问到

<br>

## 2、网页布局

**shiny**中提供了一系列函数，可以帮助我们快速实现网页布局。当然我们也可以使用**shiny**中生成html标签的函数（参考**tags**对象），结合HTML与CSS语言，自定义网页布局。

- {{< hl-text primary >}}fluidPage、fluidRow、fixedPage、fixedRow、flowLayout{{< /hl-text >}}，生成宽度自适应，高度由内部元素决定的html容器（**div**元素）。这些函数除了html样式之外，作用是相同的，生成的容器宽度总是固定的（占满整个父容器整个宽度），宽度不足时会将右侧的元素放入下方。

- {{< hl-text primary >}}column{{< /hl-text >}}，生成宽度固定，高度由内部元素决定的html容器。此外该函数还可以指定与同一个父容器中上一个元素之间的间隔。注意这里的宽度和间隔都是将父容器12等分之后相应的比例。

- {{< hl-text primary >}}fillPage{{< /hl-text >}}，设置html页面（**body**标签对应区域）占满整个屏幕。注意在其它布局函数内使用该函数可能会造成歧义。

- {{< hl-text primary >}}fillRow、fillCol{{< /hl-text >}}，生成占满整个（或一定比例）父容器高度、宽度的html容器，并分别按一定比例（默认均分）分配给子元素宽度、高度,将子元素按行、按列并排放置。注意如果父容器宽度、高度需要依赖子元素确定，这两个函数可能会生成高度、宽度为零的容器。

- {{< hl-text primary >}}verticalLayout、splitLayout{{< /hl-text >}}，分别生成横向分割、纵向分割的html容器。这两个函数功能上分别与**fillRow、fillCol**类似，不同点在于生成的容器宽度总是占满整个父容器，而高度则是根据子元素决定的。

- {{< hl-text primary >}}sidebarLayout{{< /hl-text >}}，生成一个由**sidebarPanel、mainPanel**构成的html容器。

- {{< hl-text primary >}}titlePanel、headerPanel{{< /hl-text >}}，生成用于展示网页应用标题的html容器。注意**title、windowTitle**参数分别对应展示在网页内部、展示在标签页的标题。

- {{< hl-text primary >}}sidebarPanel、mainPanel{{< /hl-text >}}，分别生成宽度固定，高度由内部元素决定的侧边栏、主栏。特别适合分别用作输入、输出面板。

- {{< hl-text primary >}}inputPanel{{< /hl-text >}}，生成适用于展示网页输入内容的html容器。

- {{< hl-text primary >}}wellPanel{{< /hl-text >}}，生成适用于混合展示网页输入、输出内容的html容器。

- {{< hl-text primary >}}absolutePanel、fixedPanel{{< /hl-text >}}，生成宽度、高度固定的html容器。二者的区别在于，**absolutePanel**的位置默认会根据父容器自动调整，而**fixedPanel**的位置默认是相对于屏幕固定的。此外我们还可以通过**draggable**参数，设置二者可以被托放至网页任意位置。

- {{< hl-text primary >}}conditionalPanel{{< /hl-text >}}，生成在特定条件下（通常是某个用户输入信息取特定值）出现的html容器。

- {{< hl-text primary >}}navbarPage{{< /hl-text >}}，生成一个分页容器。，其中既可以放置**tabPanel**元素，也可以放置**navbarMenu**等元素。

- {{< hl-text primary >}}navbarMenu{{< /hl-text >}}，生成**navbarPage**中的下拉菜单栏，其中既可以放置**tabPanel**元素，也可以放置其它元素。

- {{< hl-text primary >}}navlistPanel、tabsetPanel{{< /hl-text >}}，生成一个分页容器。二者的区别在于，**navlistPanel**以竖排的形式依次放置分页标签（类似**sidebarPanel**），除了**tabPanel**还可以放其它元素；**tabsetPanel**以横排的形式放置分页标签，只能放置**tabPanel**元素

- {{< hl-text primary >}}tabPanel{{< /hl-text >}}，生成分页容器的一个分页页面。

<br>

## 3、插入html、css、JS代码

tags

tags$style
tags$script

## 4、输入输出

checkboxInput、checkboxGroupInput、
dateInput、dateRangeInput、
fileInput、
numericInput、
passwordInput、
selectInput、selectizeInput、
sliderInput、
snapshotPreprocessInput、
textInput、textAreaInput、
varSelectInput、varSelectizeInput、
registerInputHandler、removeInputHandler、restoreInput、updateCheckboxGroupInput、updateCheckboxInput、updateDateInput、updateDateRangeInput、updateNumericInput、updateSelectInput、updateSelectizeInput、updateSliderInput、updateTextAreaInput、updateTextInput、updateVarSelectInput、updateVarSelectizeInput

textOutput、verbatimTextOutput、tableOutput、dataTableOutput、plotOutput、imageOutput、uiOutput、htmlOutput、snapshotPreprocessOutput、getCurrentOutputInfo
renderText、renderPrint、renderTable、renderDataTable、renderPlot、renderImage、renderUI、renderCachedPlot

## 5、事件响应

isolate、observeEent、reactive、eventReactive


updateNavlistPanel、updateNavbarPage、updateTabsetPanel

## 6、session

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 在**fluidPage**函数中使用**fillRow**会产生怎样的效果？
- ？
- ？

{{< /note >}}

<br>
