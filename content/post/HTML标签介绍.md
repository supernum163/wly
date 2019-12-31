---
title: "HTML标签介绍"
date: 2020-01-01
categories:
  - web语言
tags:
  - web语言
keywords:
  - HTML
comments: false
thumbnailImagePosition: left
thumbnailImage: https
---

这篇文章我们将逐一介绍[^HTML标签]的作用及使用方法。

<!--more-->

<!-- toc -->

<br>

## 整体框架

|  标签               | 说明
|:--------------------|:---------------------------------------------------------------------
| `<!DOCTYPE html>`   | 定义文档类型
| `<!-- 注释 -->`     | 添加注释
| `<html>`            | 文档的根节点
| `<head>`            | 文档元数据的集合
| `<title>`           | 文档的标题，将显示在浏览器的标题栏或标签页上
| `<meta>`            | 定义其他 HTML 元素无法描述的元数据
| `<base>`            | 为页面内的所有以相对路径表示的链接规定前缀
| `<body>`            | 文档的内容区域
| `<div>`             | 网页中通用的容器，常用于网页布局

```html
<!DOCTYPE html>
<html>
    <head>
        <meta charset="utf-8">
        <title>网页标题</title>
        <link rel="icon" href="favicon.ico">
        <meta name='keywords' content='关键词1,关键词2'>
        <meta name='description' content='网页摘要'>
        <base href="https://example.com">
    </head>
    <body>
      <!-- 网页内容 -->
    </body>
</html>
```

<br>

## 插入CSS/JS

|  标签               | 说明
|:--------------------|:---------------------------------------------------------------------
| `<style>`           | 插入**CSS**代码块
| `<link>`            | 链接**CSS**脚本等文件
| `<script>`          | 插入**JS**代码块，或者链接**JS**脚本文件
| `<noscript>`        | 定义当浏览器不支持**JS**脚本时显示的替代文字
| `<template>`        | 通过**JS**在运行时实例化内容的容器

```html
<!-- 在HTML标签中设置CSS样式、JS事件 -->
<div style = "margin: 0px;"></div>
<button onclick = "alert('Hello')">点击这里</button>

<!-- 使用style、script标签插入CSS、JS代码块 -->
<style type="text/css">
  body { color:red; }
</style> 
<script type="text/css">
  function f() { alert('hello') }
</script> 

<!-- 使用link、script标签链接CSS、JS脚本文件 -->
<link src="stylesheet.css" type="text/css" rel="stylesheet">
<script src="javascript.js" type="text/javascript">
```

<br>

## 章节

|  标签               | 说明
|:--------------------|:---------------------------------------------------------------------
| `<header>`          | 文档或章节的头部，往往包含页面标题、目录等
| `<footer>`          | 文档或章节的尾部，往往包含版权信息、地址信息、脚注链接等
| `<main>`            | 文档中主要或重要的内容
| `<article>`         | 文章区域文档中可以仅包含一篇文章，也可以包含多篇文章（如论坛帖子）
| `<section>`         | 章节区域
| `<nav>`             | 导航栏
| `<aside>`           | 侧边栏
| `<address>`         | 地址栏

```html
<!-- 网页文章 -->
<body>
  <aside> </aside>
  <article>
    <header>
      <h2>文章标题</h2>
      <nav> </nav>
    </header>
    <main>
      <section>
        <h2>章节标题</h2>
        <h2>章节内容</h2>
      </section>
    </main>
    <footer>
      <address> </address>
    </footer>
  </article>
</body>

<!-- 文章列表 -->
<body>
  <main>
    <article>
      <h2>文章一 标题</h2>
      <h2>文章一 摘要</h2>
    </article>
    <article>
      <h2>文章二 标题</h2>
      <h2>文章二 摘要</h2>
    </article>
  </main>
</body>
```

<br>

## 文本

|  标签                           | 说明
|:--------------------------------|:---------------------------------------------------------------------
| `<h1> <h2> <h3> <h4> <h5> <h6>` | 1-6级标题
| `<hgroup>`                      | 标题组（结合多个标题）
| `<p>`                           | 段落，段首换行
| `<span>`                        | 一段没有特殊含义的文本，不会段首换行
| `<blockquote>`                  | 段落引用
| `<pre>`                         | 一段包含格式的文本
| `<hr>`                          | 分割线
| `<br>`                          | 表示换行
| `<wbr>`                         | 表示建议换行
| `<a>`                           | <a href="https://example.com">超链接</a>
| `<i>`                           | <i>倾斜</i> 文本
| `<b>`                           | <b>加粗</b> 文本
| `<em>`                          | <em>强调</em> 文本
| `<strong>`                      | <strong>特别重要</strong> 的文本
| `<q>`                           | <q>引用</q> 文本
| `<mark>`                        | <mark>高亮</mark> 文本
| `<u>`                           | <u>下划线</u> 文本
| `<ins>`                         | <ins>插入线</ins> 文本
| `<del>`                         | <del>删除线</del> 文本
| `<s>`                           | 表示 <s>不准确或不相关</s> 的文本
| `<sup>`                         | <sup>上标</sup> 文本
| `<sub>`                         | <sub>下标</sub> 文本
| `<small>`                       | <small>小号</small> 文本，用于注释、版权、免责声明等
| `<abbr>`                        | 表示 <abbr title="全写">简写</abbr> 文本
| `<dfn>`                         | 用于 <dfn>下定义</dfn> 的文本
| `<time>`                        | <time datetime="2001-01-01 01:01:01">时间</time> 文本
| `<cite>`                        | <cite>参考文献</cite> 文本
| `<var>`                         | <var>代码变量</var> 
| `<code>`                        | <code>代码</code> 文本
| `<kbd>`                         | 表示 <kbd>键盘输入</kbd> 的文本
| `<samp>`                        | 表示程序或电脑的 <samp>输出</samp> 文本
| `<data>`                        | 表示 取值 - <data value="取值">标签</data> 的文本
| `<bdo>`             | 设置 <bdo dir="rtl">文本书写方向</bdo> 
| `<bdi>`             | 摆脱 <bdo dir="rtl"> <bdi>父元素</bdi> 文本书写方向 </bdo> 
| `<ruby>`  | 表示被ruby注释标记的文本，如 <ruby> 汉 字 <rp>(</rp> <rt>han zi</rt> <rp>)</rp></ruby> 
| `<rt>`    | 表示ruby注释
| `<rp>`    | 定义当浏览器不支持ruby注释时显示的替代注释

<br>

## 列表

|  标签             | 说明
|:------------------|:---------------------------------------------------------------------
| `<ol>`            | 有序列表
| `<ul>`            | 无序列表
| `<li>`            | 列表中的一个列表项
| `<dl>`            | 定义列表
| `<dt>`            | 定义列表中的定义项
| `<dd>`            | 定义列表中的释义项

```html
<ol>
  <li>有序列表 列表项 1</li>
  <ol>
    <li>有序列表 子列表项 1</li>
    <li>有序列表 子列表项 2</li>
  </ol>
</ol>

<ul>
  <li>无序列表 列表项 1</li>
  <ul>
    <li>无序列表 子列表项 1</li>
    <li>无序列表 子列表项 2</li>
  </ul>
</ul>

<dl>
  <dt>定义列表中的定义项</dt>
  <dd>定义列表中的释义项</dd>
  <!-- 更多定义项、 释义项-->
</dl>
```

<br>

## 表格

|  标签             | 说明
|:------------------|:---------------------------------------------------------------------
| `<table>`         | 定义表格
| `<colgroup>`      | 表格中的一组串列，或多个列
| `<thead>`         | 表头
| `<tbody>`         | 表格主体
| `<tfoot>`         | 表尾
| `<th>`            | 表格中的头部单元格
| `<tr>`            | 表格中的行
| `<td>`            | 表格中的单元格

```html
<table>
  <caption>表格标题</caption>
  <thead>
    <tr> <th> 表头单元格 1 </th> <th> 表头单元格 2 </th> </tr>
  </thead>
  <tfoot>
    <tr> <td> 表尾单元格 1 </td> <td> 表尾单元格 2 </td> </tr>
  </tfoot>
  <tbody>
    <tr> <td> 单元格 1-1 </td> <td> 单元格 1-2 </td> </tr>
    <tr> <td> 单元格 2-1 </td> <td> 单元格 2-2 </td> </tr>
  </tbody>
</table>
```

<br>

## 表单

|  标签               | 说明
|:--------------------|:---------------------------------------------------------------------
| `<form>`            | 表示一个表单，由控件组成                    
| `<fieldset>`        | 控件祖
| `<legend>`          | 控件祖标题
| `<label>`           | 控件标题
| `<input>`           | 输入控件，如单选框、复选框、文本框等
| `<button>`          | 按钮
| `<select>`          | 下拉框
| `<datalist>`        | 选项组，提供给其他控件一组预定义的选项
| `<optgroup>`        | 选项分组
| `<option>`          | 单个选项，用于`<select>`或`<datalist>`
| `<textarea>`        | 段落文本输入控件
| `<keygen>`          | 表单中的密匙生成控件，已弃用
| `<output>`          | 输出计算值
| `<progress>`        | 进度条
| `<meter>`           | 温度计型进度条

```html
<!-- 输入控件示例-->

<form action="https://example.com" method="get">
  <fieldset>
    <legend> 控件祖标题 </legend>
    
    <p>
      <label for="name"> 输入文本 </label>
      <input type="text" name="name" required>
    </p>
    
    <select name="select">
      <optgroup label="下拉框组别 1">
        <option value="value1"> 下拉框选项 1 </option> 
        <option value="value2"> 下拉框选项 2 </option>
      </optgroup> 
      <optgroup label="下拉框组别 2">
        <option value="value3" selected> 下拉框选项 3 </option>
      </optgroup> 
    </select>
    
    <input list="datalist" name="autoFill" placeholder="自动填充项">
    <datalist id="datalist">
      <option value="自动填充项 1">
      <option value="自动填充项 2">
    </datalist>
    
    <textarea name="textarea" rows="5" cols="50"> 段落文本输入控件 </textarea>
  </fieldset>
  <button type="submit"> 点击提交 </button>
</form>


<!-- 输出控件示例-->

<form oninput="result.value=parseInt(a.value)+parseInt(b.value)">
  <input type="range" name="b" value="50" /> +
  <input type="number" name="a" value="10" /> =
  <output name="result"></output>
  <hr>
  <meter min="200" max="500" value="350">350 degrees</meter>
  <progress value="70" max="100"> 70 % </progress>
</form>


<!-- 可用的输入控件-->

<input type="button" value="普通按钮"> 
<input type="submit" value="点击提交">
<input type="reset" value="点击清空">

<input type="radio" value="单选选项">
<input type="checkbox" checked="复选选项 1"> 

<input type="number" value="41.2">
<input type="range" value="41.2" min="10" max="50"> 

<input type="date" value="2020-06-01">
<input type="time" value="13:30:01">
<input type="month" value="2020-06">
<input type="week" value="2020-W02">
<input type="datetime-local" value="2020-06-01T13:30:01">

<input type="text">
<input type="search" minlength="4" maxlength="8" size="10"> 
<input type="password" autocomplete="current-password">
<input type="email" pattern=".+@example.com">
<input type="tel" placeholder="123-4567-8901">
<input type="url" pattern="https://\w+.com">
<input type="hidden" value="隐藏的输入信息">

<input type="color" value="#ff0000">
<input type="image" width="50%">
<input type="file" name="file" multiple>
```

<br>

## 其它结构

|  标签                   | 说明
|:------------------------|:---------------------------------------------------------------------
| `<dialog>`              | 对话窗口
| `<menu>`              | 菜单栏
| `<menuitem>`          | 菜单栏中的选项
| `<details>`         | 折叠段落
| `<summary>`         | 折叠段落的标题
| `<figure>`        | 页面中独立的流内容
| `<figcaption>`    | 流内容标题

```html
<!-- 对话窗口 -->
<dialog open> 一个打开的对话窗口 </dialog>

<!-- 菜单栏 -->
<div contextmenu="popup-menu">
  点击右键展开菜单栏
</div>
<menu type="context" id="popup-menu">
  <menuitem type="checkbox" checked>勾选选项</menuitem>
  <!-- 更多 menuitem -->
</menu>

<!-- 折叠段落 -->
<details>
    <summary>折叠段落的标题</summary>
   折叠段落
</details>

<!-- figure 结构体 -->
<figure>
  <figcaption>流内容标题</figcaption>
  流内容文本、图像等
</figure>
```

<br>

## 嵌入内容

|  标签               | 说明
|:--------------------|:----------------------------------
| `<iframe>`          | 内联框架
| `<math>`            | 数学公式
| `<img>`             | 图像
| `<svg>`             | 矢量图
| `<canvas>`          | canvas 绘图区域
| `<map>`             | 与`<area>`元素共同定义图像映射区域
| `<area>`            | 定义`<map>`中的某个区域对应的超链接
| `<picture>`         | 图像，常用于响应式布局
| `<video>`           | 视频
| `<audio>`           | 音频
| `<source>`          | 为`<video>`或`<audio>`等媒体元素指定媒体源 
| `<eventsource>`     | 定义由服务器发送的，`<video>`或`<audio>`等媒体元素的媒体源 
| `<track>`           | 为`<video>`或`<audio>`等媒体元素指定字幕
| `<embed>`           | 嵌入外部资源，如应用程序、交互内容等
| `<object>`          | 嵌入外部资源，如图片、HTML文档、插件等。
| `<param>`           | 表示`<object>`元素所指定的插件的参数 

```html
<!-- 内联框架 -->
<iframe title="嵌入内联框架" src="https://example.com" width="300" height="200"></iframe>

<!-- 数学公式 -->
<math> 
  <msup> <mi>A</mi> <mn>2</mn> </msup> <mo>+</mo>
  <msup> <mi>B</mi> <mn>2</mn> </msup> <mo>=</mo>
  <msup> <mi>C</mi> <mn>2</mn> </msup>
</math>

<!-- 图像 -->
<img src="https://example.com/example.jpg" alt="图片无法加载时的替代文字">

<!-- 矢量图 -->
<svg width="150" height="100" viewBox="0 0 3 2">
  <rect width="1" height="2" x="0" fill="#008d46" />
  <rect width="1" height="2" x="1" fill="#ffffff" />
  <rect width="1" height="2" x="2" fill="#d2232c" />
</svg>

<!-- canvas 绘图区域 -->
<canvas id="canvas" width="300" height="300">
  抱歉，您的浏览器不支持 canvas
</canvas>

<!-- 图像与映射区域 -->
<img src="example.jpg"  usemap="#map">
<map id="map">
  <area shape="circle" coords="200,250,25" href="https://example.com">
  <area shape="default">
</map>

<!-- 图像 -->
<picture>
  <source media="(min-width: 1028px)" srcset="example1.jpg">
  <source media="(min-width: 480px)" srcset="example2.jpg">
  <img src="example.jpg">
</picture>

<!-- 视频 -->
<video controls width="250">
  <source src="example.webm" type="video/webm">
  <source src="example.mp4" type="video/mp4">
  抱歉，您的浏览器不支持内嵌视频文件
</video>

<!-- 音频 -->
<audio src="example.ogg">
  <track kind="captions" src="example.vtt" srclang="zh" label="中文字幕">
  抱歉，您的浏览器不支持内嵌音频文件
</audio> 

<!-- 外部资源 -->
<embed type="video/quicktime" src="movie.mov" width="640" height="480">

<!-- 外部资源 -->
<object type="application/pdf" data="example.pdf" width="250" height="200">
  <param name="name" value="value">
</object>
```

<br>

## 特殊字符

| 字符串          | 说明
|:----------------|:------------------------------------------------------
| `&nbsp;`        | 空格，宽度受字体影响
| `&emsp;`        | 全角空格，占据一个中文字符宽度（或两个英文字符宽度）
| `&ensp;`        | 半角空格，占据全角空格的一半
| `&thinsp;`      | 窄空格，占据全角空格的六分之一
| `&zwj;`         | 零宽连字，强制连字，多用于某些需要复杂排版的语言（如阿拉伯语、印地语）
| `&zwnj;`        | 零宽不连字，抑制连字现象

<br>

[^HTML标签]: https://developer.mozilla.org/zh-CN/docs/Web/Guide/HTML/HTML5/HTML5_element_list


