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

一个简单的**shiny**网页程序框架可以由两部分组成：其中**ui**主要负责网页前端展示，包括定义网页布局、定义静态HTML展示信息、定义接收用户输入的HTML控件、定义响应用户时输出信息的HTML控件；而**server**则主要负责处理用户输入并返回响应信息，包括即时响应和事件性响应。

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
- **www**文件夹，网站根目录，用于存放图片、网页、CSS、JS等文件
- 其它文件/文件夹。如R语言脚本、数据文件等

<br>

## 2、网页布局

**shiny**中提供了一系列函数，可以帮助我们快速实现网页布局。此外如果借助其它程序包（如**shinydashboard**），还可以用到更多不同的布局函数、布局理念。当然我们也可以使用**shiny**中生成html标签的函数（参考**tags**对象），结合HTML与CSS语言，自定义网页布局。

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

- {{< hl-text primary >}}conditionalPanel{{< /hl-text >}}，生成只在特定条件下（比如某个用户输入信息取特定值）出现的html容器。

- {{< hl-text primary >}}navbarPage{{< /hl-text >}}，生成一个分页容器，其中既可以放置**tabPanel**元素，也可以放置**navbarMenu**等元素。

- {{< hl-text primary >}}navbarMenu{{< /hl-text >}}，生成**navbarPage**中的下拉菜单栏，其中既可以放置**tabPanel**元素，也可以放置其它元素。

- {{< hl-text primary >}}navlistPanel、tabsetPanel{{< /hl-text >}}，生成一个分页容器。二者的区别在于，**navlistPanel**以竖排的形式依次放置分页标签（类似**sidebarPanel**），除了**tabPanel**还可以放其它元素；**tabsetPanel**以横排的形式放置分页标签，只能放置**tabPanel**元素

- {{< hl-text primary >}}tabPanel{{< /hl-text >}}，生成分页容器的一个分页页面。

<br>

## 3、插入HTML、CSS、JS等内容

**shiny**中的**tags**对象保存了几乎所有HTML标签对应的函数，要了解这些标签的功用，请参考 [HTML5 标签列表](https://developer.mozilla.org/zh-CN/docs/Web/Guide/HTML/HTML5/HTML5_element_list) 。上文已经提到，我们可以在**ui**中直接使用HTML标签。插入相应的标签可以使用**tags**中相应的函数，比如插入超链接可以使用`tags$a("超链接", href = "https://example.com", ...)`，自定义网页布局可以使用`tags$div(style = "margin: 0px;", ...)`等。这些函数中有名参数会被用作标签属性，无名参数会被用作标签内容，而且绝大部分都可以嵌套使用。

在HTML中插入CSS、JS代码的方式大致有三种：首先我们可以在某些HTML标签中，通过**style**属性设置该标签的CSS样式，设置JS事件处理函数（如**onclick**事件）；其次我们可以在**style、script**标签的标签内容中分别插入CSS、JS代码片段；最后我们还可以使用**link、script**标签分别链接CSS、JS代码文件，注意此类直接生成HTML标签的函数，在HTML代码寻找文件时，会以当前**shiny**工程目录下的**www**文件夹作为根目录。当然我们还可以分别使用{{< hl-text primary >}}addResourcePath、removeResourcePath、resourcePaths{{< /hl-text >}}函数，添加、删除、查询网站资源目录，并在**shiny**网页中使用这些网站资源目录的**preifx**（参考**addResourcePath**函数），访问到其中的内容。

```R
# 在HTML标签中设置CSS样式、JS事件
> tags$div(style = "margin: 0px;")
> tags$button("点击这里", onclick = "alert('Hello')")

# 使用style、script标签插入CSS、JS代码片段
> tags$style("div { margin: 0px; }")
> tags$script("function f() { alert('hello')")

# 使用link、script标签链接CSS、JS代码文件
> tags$link(href="example.css", type="text/css", rel="stylesheet")
> tags$script(src="example.js", type="text/javascript")
```

此外**shiny**中还定义了{{< hl-text primary >}}includeCSS、includeScript、includeHTML、includeMarkdown、includeText{{< /hl-text >}}函数，可以方便我们将CSS文件、JS文件、HTML文件、排版后的MarkDown文件、文本文件中的内容插入到HTML中。文本文件与HTML中的纯文本，格式上可能会有所不同（比如即使输入多个空格，HTML中也只会显示一个空格），为了保持文本文件中原有的格式，我们可以使用**pre**标签包裹**includeText**函数。注意此类函数会先从特定文件中读取相应的内容，再使用合适的HTML标签将这些内容转化为HTML，所以文件路径是相对R语言工作目录而言的。

<br>

## 4、输入输出

我们可以在**ui**中插入以下控件来获取用户的输入信息。这些控件都必须设置**inputId**参数，而且必须具有唯一性。我们可以在**server**中使用`input$inputId`的形式，获取某个控件收集到的用户输入信息。

| 输入函数                  | 解释说明                                                      
|:--------------------------|:-----------------------------------------------------------------
| checkboxInput             | 单选框输入控件（单个选项中选择是否选中）
| checkboxGroupInput        | 复选框输入控件（多个选项中选择多个选项）
| radioButtons              | 单选按钮输入控件（多个选项中选择单个选项）
| selectInput               | 选择输入控件（可以单选也可以多选）
| varSelectInput            | 选择输入控件（从数据框中选则变量）
| numericInput              | 数值输入控件
| sliderInput               | 滑动条输入控件（数值输入控件的另一种展示形式，必须指定输入范围）
| dateInput                 | 日期输入控件
| dateRangeInput            | 起止日期输入控件（返回长度为2的日期型数组）
| passwordInput             | 密码输入控件
| textInput                 | 单行文本输入控件
| textAreaInput             | 多行文本输入控件
| fileInput                 | 文件输入控件
| actionButton              | 动作按钮（默认值为0，每点击一次值加1）

如果我们需要在网页中输出动态信息，则可以在**ui**端使用**Output**家族的函数，定义一个信息输出区域；并在**server**端使用**render**家族的函数，将信息传递到相应的区域。二者需要相互结合、一一对应。因此**Output**家族的函数都必须设置**outputId**参数，而且必须具有唯一性，**render**家族的函数需要将结果返回给相应的**outputId**，比如`output$outputId <- renderText(...)`。

| 输出函数（**ui**端）| 输出函数（**server**端）| 解释说明     
|:--------------------|:------------------------|:----------------
| textOutput          | renderText              | 输出纯文本
| verbatimTextOutput  | renderPrint             | 输出格式化纯文本
| tableOutput         | renderTable             | 输出表格
| dataTableOutput     | renderDataTable         | 输出可交互的表格
| imageOutput         | renderImage             | 输出图片
| plotOutput          | renderPlot              | 输出R语言绘制的图像
| htmlOutput          | renderUI                | 输出HTML
| uiOutput            | renderUI                | 输出UI

注意以上仅是**shiny**程序包中的输入输出函数，如果我们借助其它程序包，还可以用到更多类似的函数。比如我们可以使用**plotly**程序包中的{{< hl-text primary >}}plotlyOutput、renderPlotly{{< /hl-text >}}函数，输出可交互的图像。

<br>

## 5、事件响应



submitButton                  提交按钮
downloadLink                  下载链接
downloadButton                下载按钮
bookmarkButton                分享链接获取按钮
showModal、modalDialog、modalButton  网页弹窗

isolate、observeEent、reactive、eventReactive

updateNavlistPanel、updateNavbarPage、updateTabsetPanel
snapshotPreprocessInput


onFlush(fun, once = TRUE, session = getDefaultReactiveDomain())
onFlushed(fun, once = TRUE, session = getDefaultReactiveDomain())
onSessionEnded(fun, session = getDefaultReactiveDomain())

<br>

{{< image classes="fancybox fig-50" group="shiny"  src="https://s2.ax1x.com/2019/12/21/Qj8UZF.jpg" >}}
{{< image classes="fancybox fig-50 clear" group="shiny" src="https://s2.ax1x.com/2019/12/21/Qj8BGR.jpg" >}}

上方的的速记手册，可以帮助我们快速了解**shiny**的整体框架与各项细节。获取更多速记手册，请前往 [这里](https://rstudio.com/resources/cheatsheets/) 。

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 在**fluidPage**函数中使用**fillRow**会产生怎样的效果？
- ？
- ？

{{< /note >}}

<br>
