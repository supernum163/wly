---
title: "JavaScript"
date: 2020-02-01
categories:
  - web语言
tags:
  - web语言
keywords:
  - JavaScript
comments: false
thumbnailImagePosition: left
thumbnailImage: https
---

这篇文章我们将逐一介绍 **JavaScript** 的作用及使用方法。

<!--more-->

<!-- toc -->

<br>


```JavaScript
// 行注释

/*
  块注释
*/

```

## 1、
|  语法                     | 说明
|:--------------------------|:---------------------------------------------------------------------
| `console`                 | JS调试器命令行
| `window`                  | 浏览器窗口
| `Navigator`               | 浏览器信息
| `Screen`                  | 显示屏信息
| `History`                 | 访问历史记录（当前窗口）
| `Location`                | URL地址信息
| `document`                | 网页内容
| `Math`                    | JS扩展对象


```JavaScript
class.__proto__ class.prototype class.field

document.querySelector 
document.createElement tag.appendChild tag.removeChild tag.parentNode
tag.setAttribute tag.removeAttribute tag.addEventListener 
tag.style

callback
setTimeOut setInterval 
promise Promise.all then
async await

// Ajax与读写数据库
XMLHttpRequest SqlConnection
// 请求远程数据
fetch(url).then(function(response) { })

// 存储少量数据
sessionStorage localStorage.setItem localStorage.getItem localStorage.removeItem
// 存储大型数据
let request = window.indexedDB.open(databaseName, version);
let db;
request.onerror = event => console.log('数据库打开报错');
request.onsuccess = event => db = request.result;
request.onupgradeneeded = event => db = event.target.result;
db.transaction
// 存储文件
if('serviceWorker' in navigator) {
  navigator.serviceWorker.register('/test.js')
    .then(function() { console.log('存储完毕'); });
  }
```

```html
<!-- 使脚本与浏览器异步加载（脚本不等HTML加载完毕就运行），多个异步脚步执行顺序不固定 -->
<script async src="test.js"></script>
<!-- 使脚本脚本等HTML加载完毕才运行，多个脚本按照在HTML中出现的先后顺序执行 -->
<script defer src="test.js"></script>
```

<br>

