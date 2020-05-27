---
title: "CSS"
date: 2020-02-01
categories:
  - web语言
tags:
  - web语言
keywords:
  - CSS
comments: false
thumbnailImagePosition: left
thumbnailImage: https
---

这篇文章我们将逐一介绍 **CSS** 的作用及使用方法。

<!--more-->

<!-- toc -->

<br>


```CSS
/* 导入其它CSS脚本 */
@import 'styles2.css';

/* 根据屏幕尺寸设置CSS */
@media (min-width: 30em) {
  /* CSS style */
}

/* 根据浏览器能否支持某项功能来设置CSS */
@support (display: flex) {
  div {
    float: right;
  }
}

/* CSS使用变量 */
:root{
    --base_color:#398bd0;
    --bg_color:#4a4a4a;
}
a {
  color:var(--base_color);
}
```

显示手机平面的真实尺寸，苹果手机可能会将浏览器尺寸设置为960px，使用户可以总揽按大屏幕尺寸设置的网站，然后放大其中的细节具体浏览

```CSS
<meta name="viewport" content="width=device-width,initial-scale=100">
```

```CSS
/* 设置表格中相邻单元格的边框合并 */
`border-collapse: collapse`

/* 设置有序列表编号类型 */
list-style-type: upper-roman;
/* 设置列表项的符号是在内容行内还是行外 */
list-style-position: inside;

```

```html
<!-- 控制有序列表编号从2开始倒数 -->
<ol start="2" reversed>
  <li> 列表项 1 </li>
  <li> 列表项 2 </li>
</ol>

<!-- 自定义有序列表编号 -->
<ol>
  <li value="2"> 列表项 1 </li>
  <li value="4"> 列表项 2 </li>
</ol>
```

## 1、属性覆盖与继承

层叠：写在后面的样式会覆盖之前的样式
优先级：选择越明确优先级越高，会覆盖优先级底的样式
  - 标签/属性 < 类 < id < 内联
  - 设置属性值`!important`的属性，优先级最高
继承：父元素的某些样式可以被子元素继承
  - inherit 继承父元素属性
  - initial 继承浏览器默认属性
  - unset 如果可以继承父元素属性，则等同于**inherit**，否则等同于**initial**
  - revert 重置几乎所有继承的属性（除文字方向等），少数浏览器支持

使用CSS中的**all**属性，可以设置当前元素所有样式的继承方式：`all: revert`  


<br>

## 3、盒子模型

我们可以通过**display**属性，设置元素的盒子类型

块级盒子**block**
  - 每个盒子都会换行
  - **width、height**属性可以发挥作用
  - 内边距、外边距、边框可以把其它元素从盒子周围推开
内联盒子**inline**
  - 盒子不会换行
  - **width、height**属性将不能发挥作用
  - 内边距、外边距、边框可以被应用，但不会把其它元素从盒子周围推开
**inline-block**
  - 盒子不会换行
  - **width、height**属性可以发挥作用
  - 内边距、外边距、边框可以把其它元素从盒子周围推开  
弹性盒子**flex**
  - 设置对外显示盒子是**block**
  - 设置内部显示盒子是**inline**
**inline-flex**
  - 设置内外显示盒子都是**inline**


盒模型可以设置**width、height、margin、border、padding**，我们可以通过**box-sizing**修改盒模型类型
  - **padding-box**标准盒模型计算长宽不包括内边距和边框
  - **border-box**替代盒模型包括内边距和边框

外边距为正数时可以推开其它盒子，为负数时可以拉近其它盒子（可能会发生重叠）
外边距折叠：两个外边距相接时将被折叠成一个外边距，即绝对值最大的外边距

内边距只能为零或正数，背景将显示在内边距区域

<br>

## 4、背景与边框

```CSS
/* 设置背景，可以有多幅背景，设置时用逗号隔开 
  background: <background-image> <background-attachment> <background-clip> <background-position> /  <background-size> <background-repeat>
*/
background: green, content-box radial-gradient(crimson, skyblue);
/* 设置背景颜色 */
background-color: rgba(229, 229, 229, 1);
/* 设置背景渐变色 */
background-image: linear-gradient(105deg, rgba(0,249,255,1) 39%, rgba(51,56,57,1) 96%);
/* 设置背景图像 */
background-image: url(image1.png), url(image2.png)
/* 设置背景相对固定位置
  取值为fixed时，表示固定在视窗区域
  取值为scroll时，表示固定在页面，可以随页面滚动
  取值为local时，表示固定在父容器，可以随容器滚动
*/
background-attachment: local
/* 设置背景盒模型 */
background-clip: content-box;
background-origin: border-box;
/* 设置背景图像左上角所在位置，偏移量 */
background-position: top 20px right 10%;
/* 设置背景大小，
  取值为cover时，表示以最长的边填充容器，超出部分忽略
  取值为contain时，表示以最短的边填充容器，不足部分留白
*/
background-size: 100px 10em;
/* 设置背景图像重复方式 */
background-repeat: no-repeat;

/* 设置边框 
  border: <border-width> <border-style> <border-color>; 
*/
border: 1px solid black; 
border-top: 2px dotted rebeccapurple;
/* 设置边框圆角 */
border-radius: 10px; 
border-top-right-radius: 1em 10%;
```

我们可以通过**object-fit**属性，设置图像等媒体元素占满父容器的方式
  - 取值为cover时，表示以最长的边填充容器，超出部分忽略
  - 取值为contain时，表示以最短的边填充容器，不足部分留白
  - 取值为fill时，可以同时占满容器宽高，但不能保持图像宽高比
  
<br>

## 5、文字排版方向

使用属性**block-size、inline-size**设置容器的换行方向、不换行方向的尺寸
使用**block-start、block-end、inline-start、inline-end**设置容器的边距等

```CSS
/* 设置文字排版方向 
    取值为horizontal-tb时，表示横排文字，从上到下
    取值为vertical-rl时，表示竖排文字，从右到左
    取值为vertical-lr时，表示竖排文字，从左到右
*/
writing-mode: vertical-rl;

/* 设置容器的换行方向、不换行方向的尺寸、边距 */
inline-size: 150px;
margin-inline-end: 10px;
margin-block-end: 10px;
```

<br>

## 6、溢出处理

我们可以通过**overflow**处理溢出的内容
  - **hidden**表示隐藏内容
  - **scroll**表示无论是否有溢出都显示滚动条
  - **auto**表示有溢出时显示滚动条

<br>

## 7、单位转化

`1in = 2.54cm = 96px`

| 单位  | 说明              
|:------|:------------------
| px    | 像素              
| cm    | 厘米 	            
| mm 	  | 毫米 	            
| Q 	  | 四十分之一厘米    
| in 	  | 英寸               
| pc 	  | 十六分之一英寸    
| pt 	  | 七十二分之一英寸  
| em 	  | 父元素的字体大小
| rem   | 根节点元素的字体大小
| ex 	  | 当前元素中字体**x**的高度
| ch 	  | 当前元素中字体**0**的宽度
| lh 	  | 当前元素的行高
| vw 	  | 视窗区域 1% 的宽度
| vh 	  | 视窗区域 2% 的高度
| vmin 	| 视窗区域宽高之间最小值的 1%
| vmax  | 视窗区域宽高之间最大值的 1%

通过属性**min-width、min-height、max-width、max-height**，设置容器最大、最小宽高

<br>

## 8、字体设置

网页安全字体

| 字体            | 字体类型              
|:----------------|:------------------
| Arial 	        | sans-serif
| Courier New 	  | monospace
| Georgia 	      | serif 	
| Times New Roman | serif
| Verdana         | sans-serif

系统默认字体

| 字体            | 字体类型              
|:----------------|:----------------------------------------------
| serif           | 有衬线字体（笔画开始、结束的地方有额外装饰）
| sans-serif      | 无衬线字体
| monospace       | 等宽字体（英文字母固定占半个中文字符的宽度）
| cursive         | 模拟手写字体
| fantasy         | 华丽的字体

```CSS
/* 从外部引入字体 */
@font-face {
  font-family: "myFont";
  src: url("myFont.woff");
}

/* 设置字体
  font: <font-style> <font-variant> <font-weight> <font-stretch> <font-size> <line-height> <font-family>
*/
/* 设置字体集，浏览器加载时会从左到右依次查找有效字体 */
font-family: "Trebuchet MS", Verdana, sans-serif;
/* 设置字体阴影，可以有多个阴影，设置时需要用逗号分割
  参数分别表示：水平方向偏移、垂直方向偏移、阴影范围、阴影颜色
*/
text-shadow: 1px 1px 1px black;
```

**font-style**属性，设置字体倾斜情况
  - **normal**，正常字体
  - **italic**，倾斜字体
  - **oblique**，伪倾斜，将正常字体倾斜书写
**font-weight**属性，设置字体加粗情况
  - **normal、bold**，正常、加粗字体
  - **lighter、bolder**，降低、增加当前字体比父元素的加粗等级
  - **100–900**，设置加粗等级
**text-transform**属性，设置字体转化
  - **none**，不做任何转化
  - **uppercase、lowercase**，大写、小写字体
  - **capitalize**，首字母大写
  - **full-width**，字母占用宽度相等
**text-decoration**属性，设置字体装饰
  - **none**，不做任何装饰
  - **underline、overline、line-through**，下划线、上划线、插入线
**text-align**属性，设置字体对齐方式
  - **left、right**，左、右对齐
   - **center**，居中对齐
   - **justify**，两端对齐
**text-indent**,设置段首缩进
**Line height**属性，设置行高
**letter-spacing**属性，设置字母之间的间隔
**word-spacing**属性，设置单词之间的间隔

<br>

## 9、布局

```CSS

/* 弹性盒子，子容器先按主轴方向依次排列，排不下时在按交叉轴方向排列（相当于换行） */
.container {
  display: flex;
  /* 设置弹性盒子弹力方向
    flex-flow: <flex-direction> <flex-wrap>; 
  */
  flex-direction: row;
  flex-wrap: wrap;
  /* 设置子容器大小
    flex: <flex-grow > <flex-shrink> <flex-basis>
    可以设置剩余尺寸分配权重，收缩尺寸权重，基础尺寸
  */
  flex: 1 200px;
  /* 设置交叉轴方向上子容器的对齐方式
    stretch，拉伸子容器以填满整个交叉轴
    center，保持子容器大小，居中对齐
    flex-start，保持子容器大小，靠交叉轴开始的地方对齐
    flex-end，保持子容器大小，靠交叉轴结束的地方对齐
  */
  align-items: center;
  /* 设置主轴方向上子容器的对齐方式
    flex-start，靠主轴开始的地方对齐
    flex-end，靠主轴结束的地方对齐
    center，居中对齐
    space-around，分散对齐
    space-between，分散对齐，但两端不留空隙
  */
  justify-content: space-around;
}

.container:first-child {
  /* 设置弹性盒子中子容器的优先排列顺序，默认顺序为0，值可以为负数，越大越往后排 */
  order: 1;
}


/* 网格布局，先定义网格，再将内容放入相应网格 */
.container {
    display: grid;
    /* 网格相对宽度 */
    grid-template-columns: 2fr repeat(3, 1fr);
    /* 网格高度 */
    grid-auto-rows: 10px;
    /* 设置网格宽高的最小值（最大值可以自适应）
      grid-template-columns: repeat(auto-fill, minmax(200px, 1fr));
      grid-auto-rows: minmax(100px, auto);
    */
    /* 网格间距 */
    grid-gap: 20px;
}

/* 将标题行置于网格的第1行，第1-3列 */
header {
  /* grid-column: <grid-column-start> <grid-column-end>; */
  grid-column: 1 / 3;
  grid-row: 1;
}
/* 将导航栏置于网格的第2行，第1列 */
aside {
  grid-column: 1;
  grid-row: 2;
}
/* 将正文置于网格的第2行，第2列 */
article {
  grid-column: 2;
  grid-row: 2;
}

/* 网格布局，先定义网格区域，再将内容与网格区域一一对应 */
.container {
  display: grid;
  grid-template-areas: 
      "header header"
      "sidebar content"
      "footer footer";
  grid-template-columns: 1fr 3fr;
  grid-gap: 20px;
}
header { grid-area: header; }
article { grid-area: content; }
aside { grid-area: sidebar; }
footer { grid-area: footer; }


/* 浮动布局，浮动元素位于父容器之上，但可以使父容器中的内容围绕浮动元素分布 */
.container {
  float: left;
  margin-right: 15px;
}

/* 清除左侧浮动，但可以围绕右侧的图像环绕分布 */
.box + * {
  clear: left;
}

/* 使得浮动元素的显示范围不超出其父容器， .wrapper 包含 .container*/
.wrapper {
  background-color: rgb(79,185,227);
  display: flow-root; 
}


/* 分栏布局 */
.container {
  /* 设置分栏数量 */
  column-count: 3;
  /* 设置分栏的最小宽度，column-count、column-width只需要指定一个 */
  column-width: 200px;
  /* 设置分栏间隔 */
  column-gap: 20px;
  /* 设置分栏间隔线 */
  column-rule: 4px dotted rgb(79, 185, 227);
}

/* 避免分栏布局时，子容器被截断 */
.container > * {
  break-inside: avoid;
  page-break-inside: avoid;
}
```

<br>

## 10、定位

我们可以通过**position**设置元素的应对位置
  - **static**，默认位置
  - **relative**，相对位置（相对于父容器），元素原本所占的位置仍会被保留，适合对位置进行微调
  - **absolute**，相对位置（相对于第一个拥有**relative**位置属性的父容器，或者视窗区域），元素原本所占的位置不会被保留

使用**top、bottom、left、right**属性，调整相对位置
使用**z-index**调整拥有相对位置的元素的 *z轴坐标* ，取值越大，元素被置于图层的越上层。

  - **fixed**，固定位置，将元素固定在父容器的某个位置，不随着父容器滚动
  - **sticky**,类固定位置，在元素被滚动到特定位置之后开始固定位置，遇到下一个**sticky**对象则取消固定

<br>
