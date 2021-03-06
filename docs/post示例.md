---
# post标题
title: "文章标题"
# post文件名及网络路径
slug: who-is-using-tranquilpeak-hugo-theme
# 展示post的： date 生成日期，publishDate 发布日期、lastmod 修改日期、expiryDate 过期日期
date: 2019-02-28

# post分类
categories:
  - 一级分类
  - 二级分类

# post标签
tags:
  - 标签一
  - 标签二
  
# post的关键字
keywords:
  - 关键字一
  - 关键字二
  
# 是否展示post生成日期
showDate: true
# 是否展示post的meta信息（发布更新时间）
showMeta: true
# 是否展示post标签
showTags: true
# 是否展示评论区
comments: true
# 是否展示分享按钮
showSocial: true
# 是否展示翻页按钮
showPagination: true
# 是否展示所有底部按钮
showActions: true
# 是否默认将post的第一张图作为展示图
autoThumbnailImage: false

# post展示图的位置、可以是left、right、top、bottom
thumbnailImagePosition: left
# post展示图的地址
thumbnailImage: //d1u9biwaxjngwg.cloudfront.net/elements-showcase/vintage-140.jpg

# post封面图
coverImage: //d1u9biwaxjngwg.cloudfront.net/cover-image-showcase/city.jpg
# post的meta信息展示位置 in展示在封面图中， out展示在封面图下
coverMeta: out
# post的meta信息（文章标题、日期等）展示位置
metaAlignment: center

# 在文章末尾展示图片画廊
gallery:  
  - //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-31.jpg "Mercedes"
  - //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-9.jpg "图片标题"
  - //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-10.jpg 
---

这里是摘要，100至300字的摘要会使页面布局更好看。 

<!--摘要与正文分界线-->
<!--more-->


# 标题测试 1

## 标题测试 2

### 标题测试 3

#### 标题测试 4

##### 标题测试 5

###### 标题测试 6

<!--插入目录-->
<!-- toc -->

## 段落测试

[远程链接测试](https://www.baidu.com), [本地链接测试](#翻页代码块测试),  **粗体字测试** ,  *斜体字测试* , <u>下划线测试</u>, ~~删除线测试~~ , `行内代码测试`，:smile:.

<sup>上标文字测试</sup>, <sub>下标文字测试</sub> , 键盘文本测试<kdb>ctrl + c</kdb>, <cite>行内引用测试</cite>
， 缩写测试<acronym title="National Basketball Association">NBA</acronym>，简写测试<abbr title="Avenue">AVE</abbr>


## 超链接测试

This is an [example link](http://example.com/)

### 引用链接

I get 10 times more traffic from [Google][1] than from [Yahoo][2] or [MSN][3].  

[1]: http://google.com/        "Google" 
[2]: http://search.yahoo.com/  "Yahoo Search" 
[3]: http://search.msn.com/    "MSN Search"

### 脚注链接

这是一个链接到谷歌的[^脚注]。

[^脚注]: http://www.google.com


## 列表测试

### 定义列表 (dl)

<dl>
  <dt>列表标题</dt>
  <dd>列表内容</dd>
</dl>

### 有序列表 (ol)

1. List Item 1
2. List Item 2
3. List Item 3

### 无序列表 (ul)

- List Item 1
- List Item 2
- List Item 3

### 任务列表
- [x] Baidu analytics
- [ ] Algolia (https://github.com/kakawait/hugo-tranquilpeak-theme/issues/8)
- [ ] Pagination custumization `tagPagination`, `categoryPagination` 


## 表格测试

|  Header 1  | Header 2   | Header 3   |
|:----------:|------------|------------|
| Division 1 | Division 2 | Division 3 |
| Division 1 | Division 2 | Division 3 |
| Division 1 | Division 2 | Division 3 |
| Division 1 | Division 2 | Division 3 |

## 高亮文字测试

{{< hl-text red >}}文字可以高亮为：red、green、blue、purple、orange、yellow、cyan、primary、success、warning、danger。{{< /hl-text >}} 

## Alert测试

{{< alert info >}}
alert的类型可以是：info、success、warning、danger
{{< /alert >}}


## 引用测试

### 普通引用

> 这里是普通引用

### 从书籍引用

{{< blockquote "wly" "wly.supernum" >}}
格式：姓名 + 书名
{{< /blockquote >}}

### 从网络引用

{{< blockquote "@wly" "//wly.supernum.tech" "我的博客" >}}
格式：姓名 + 网址 + [网址标签]
{{< /blockquote >}}

### 行内引用测试

Phasellus adipiscing, mauris nec mollis egestas, ipsum nunc auctor velit, et rhoncus lorem ipsum at ante. Duis vel mauris nulla. Maecenas mattis interdum ante, quis sagittis.
{{< pullquote left >}}
Here is a pullquote left. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
{{< /pullquote >}}
ulputate nisl, ac congue ante tortor ut ante. Proin aliquam sem vel mauris tincidunt, elementum ullamcorper nisl pretium, ultrices cursus justo. Mauris porttitor commodo eros, ac ornare orci interdum in. Cras fermentum cursus leo sed mattis. In dignissim lorem sem, sit amet elementum mauris venenatis ac.
{{< pullquote right >}}
Here is a pullquote right. Lorem ipsum dolor sit amet, consectetur adipiscing elit.
{{< /pullquote >}}


## 代码块测试

### 普通代码块

```js
alert('Hello World!');
```

### 有标题和网址的代码块

{{< codeblock "apache.conf" "apacheConf" "http://underscorejs.org/#compact" "apache.conf" >}}
# 格式：代码块标签 + [网址标签] + [网址] + [代码类型]
  <Location /maps/>
    RewriteMap map txt:map.txt
    RewriteMap lower int:tolower
    RewriteCond %{REQUEST_URI} ^/([^/.]+)\.html$ [NC]
    RewriteCond ${map:${lower:%1}|NOT_FOUND} !NOT_FOUND
    RewriteRule .? /index.php?q=${map:${lower:%1}} [NC,L]
  </Location>
{{< /codeblock >}}

### 翻页代码块测试

{{< tabbed-codeblock 代码块标题 >}}
<!-- tab js -->
function $initHighlight(block, flags) {
  try {
    if (block.className.search(/\bno\-highlight\b/) != -1)
      return processBlock(block.function, true, 0x0F) + ' class=""';
  } catch (e) {
    var e4x =
        <div>Example
            <p>1234</p></div>;
  }
  console.log(Array.every(classes, Boolean));
}
<!-- endtab -->
<!-- tab css -->
@media screen and (-webkit-min-device-pixel-ratio: 0) {
  body:first-of-type pre::after {
    content: 'highlight: ' attr(class);
  }
  body {
    background: linear-gradient(45deg, blue, red);
  }
}
<!-- endtab -->
<!-- tab html -->
<?xml version="1.0"?>
<response value="ok" xml:lang="en">
  <text>Ok</text>
  <comment html_allowed="true"/>
  <ns1:description><![CDATA[
  CDATA is <not> magical.
  ]]></ns1:description>
  <a></a> <a/>
</response>
<!-- endtab -->
{{< /tabbed-codeblock >}}

### Gist代码块测试

{{< gist imathis 996818 >}}

### jsFiddle代脉快测试

{{< jsfiddle ccWP7 >}}


## 图片测试

### 普通图片

![supernum.tech](https://www.supernum.tech/favicon.png)

### 图片与链接结合

[![supernum.tech](https://www.supernum.tech/favicon.png)](http://www.supernum.tech)

### 图片画廊

```yaml
src:        图片地址
thumbnail:  缩略图地址
title:      图片标题
group:      用于创建一个图片gallery，只能用于拥有fancybox属性的图片
classes:  
  fancybox: 允许点击展示原图
  left、right、center: 图片位置
  fig-[20、25、33、50、66、75、80、100]: 图片百分比大小
  clear: 另起一行
```
{{< image classes="fig-100" src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-15.jpg" thumbnail="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-15-750.jpg" >}}
{{< image group="group:travel1" classes="fancybox nocaption fig-50" src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-4.jpg" thumbnail="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-4-375.jpg" title="Ferrari" >}}
{{< image group="group:travel1" classes="fancybox nocaption fig-50" src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-12.jpg" thumbnail="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-12-375.jpg" title="BMW i8 Concept" >}}
{{< image group="group:travel2" classes="fancybox nocaption fig-33" src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-14.jpg" thumbnail="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-14-250.jpg" >}}
{{< image group="group:travel2" classes="fancybox nocaption fig-33 clear" src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-9.jpg" thumbnail="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-9-250.jpg" >}}

### 宽型图片测试

{{< wide-image src="//d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-1.jpg" title="Mercedes SLS" >}}


## 视频测试

### Youtube

{{< youtube BSVkI3Ds8E >}}

### Vimeo

{{< vimeo 147585091 >}}


## 其它内容测试 

### 插入Emojj表情及数学公式

[Emoji cheat sheet](https://www.webfx.com/tools/emoji-cheat-sheet/)
[katex](https://katex.org/docs/supported.html)

### 颜色对照

| 颜色                | RGB
|:--------------------|:--------------
| red                 | #ffe6e6
| orange              | #ffedcc
| yellow              | #ffc
| green               | #cdffcd
| cyan                | #cff
| blue                | #e6e6ff
| purple              | #ffe6ff
| primary             | #ddeffd
| success             | #d4f1d7
| warning             | #fdeece
| danger              | #fee3e0

### 使用彩色字体与彩色背景的字体

<font color="#FF0000">找不到对象</font>
{{< hl-text red >}}找不到对象{{< /hl-text >}}

### 加入下载链接

<a href="" target="_blank" download="../../../css/gitment.css">点击下载</a>


