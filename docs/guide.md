---
title: "Elements showcase"
date: 2015-05-28
categories:
- tranquilpeak
- features
tags:
- html elements
- markdown
thumbnailImagePosition: left
thumbnailImage: //d1u9biwaxjngwg.cloudfront.net/elements-showcase/vintage-140.jpg
coverImage: //d1u9biwaxjngwg.cloudfront.net/cover-image-showcase/city.jpg
metaAlignment: center
coverMeta: out
gallery:
- //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-31.jpg "Mercedes"
- //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-9.jpg "图片标题"
- //d1u9biwaxjngwg.cloudfront.net/tag-plugins-showcase/car-10.jpg 
---

摘要测试 Check out how Tranquilpeak theme display well HTML elements (title, paragraph, blockquote, table and more..). It's simple and elegant. 
<!--more-->


# 标题测试 1

## 标题测试 2

### 标题测试 3

#### 标题测试 4

##### 标题测试 5

###### 标题测试 6

<!-- toc -->

## 段落测试

[远程链接测试](www.baidu.com), [本地链接测试](#翻页代码块), **粗体字测试** ,  *斜体字测试* , <u>下划线测试</u>, ~~删除线测试~~ , `行内代码测试`.

<sup>上标文字测试</sup>, <sub>下标文字测试</sub> , 键盘文本测试<kdb>ctrl + c</kdb>, <cite>行内引用测试</cite>
， 缩写测试<acronym title="National Basketball Association">NBA</acronym>，简写测试<abbr title="Avenue">AVE</abbr>


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

## 图片与链接结合

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
  fig-[20、25、33、50、75、100]: 图片百分比大小
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


