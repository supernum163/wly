---
title: R语言使用ggplot2绘图
date: 2019-12-30
categories:
  - R语言
  - 扩展包
tags:
  - R语言绘图
  - R语言扩展包
keywords:
  - R语言
  - 绘图
  - ggplot2
thumbnailImagePosition: left
thumbnailImage: https
---

这篇文章我们将介绍**ggplot2**。

<!--more-->

<!-- toc -->

```
ggplot(mtcars, aes(wt, mpg, color = as.character(cyl), shape = as.character(carb))) + 
  geom_point() + facet_wrap(am~., labeller = labeller(am = c("0" = "自动", "1" = "手动"))) +
  labs(x = "重量（千磅）", y = "每加仑英里数", color = "气缸数量", shape = "汽化器数量",
       title = "汽车重量与每加仑英里数之间的关系", 
       subtitle = "辅助分析因素：换挡类型、气缸数量、汽化器数量", 
       caption = "汽车公路测试数据", tag = "车") +
  theme_bw() + theme(
    plot.title = element_text(hjust = 0.5),
    plot.subtitle = element_text(hjust = 0.5),
    plot.caption = element_text(hjust = 0.5),
    legend.box.background = element_rect(color = "gray30"),
    legend.box.margin = margin(5, 5, 5, 5),
    legend.box.just = "left",
    legend.background = element_rect(color = "gray60"),
    legend.key = element_rect(fill = "gray90"),
    legend.key.width = unit(15, "pt"),
  )
```


## 1、图形管理

| 函数              | 解释说明                                                      
|:------------------|:-----------------------------------------------------------------
| geom_blank        | 空图形
| geom_point        | 散点图（需要指定**x、y**）
| geom_jitter       | 散点图（需要指定**x、y**，给重合的点添加偏移量）
| geom_count        | 散点图（需要指定**x、y**，以点形大小表示重叠点的数量）
| geom_hex          | 二维区间频率密度图（需要指定**x、y**，以六边形为单位统计频数）
| geom_bin2d        | 二维区间频率密度图（需要指定**x、y**，以矩形为单位统计频数）
| geom_spoke        | 射线（需要指定**x、y、angle、radius**）
| geom_segment      | 点到点的直线（需要指定**x、y、xend、yend**）
| geom_curve        | 点到点的弧线（需要指定**x、y、xend、yend**）
| geom_abline       | 一元一次方程线（需要设置**slope、intercept**）
| geom_hline        | 水平线（需要设置**yintercept**）
| geom_vline        | 垂直线（需要设置**xintercept**）
| geom_line         | 折线（需要指定**x、y**，按从左到右的顺序依次连接）
| geom_path         | 折线（需要指定**x、y**，按点坐标出现的顺序依次连接）
| geom_step         | 阶梯线（需要指定**x、y**，先水平后垂直）
| geom_rect         | 矩形（需要指定**xmin、ymin、xmax、ymax**）
| geom_tile         | 矩形（需要指定矩形中心点**x、y**，还可以指定**width、height**)
| geom_raster       | 矩形（需要指定矩形中心点**x、y**，长宽固定为**1**）
| geom_polygon      | 任意多边形（需要指定**x、y**)
| geom_area         | 面积图（需要指定**x、y**，生成经过**x、y**中所有点的曲线与X轴之间围成的面积）
| geom_ribbon       | 区间带图（需要指定**x、ymin、ymax**）
| geom_map          | 形状填充图（需要指定形状轮廓**map**，形状属性**map_id**）
| geom_contour      | 等高线图（需要指定**x、y、z**）
| geom_sf           | 地图（需要**.shp**格式的文件）
| geom_sf_text      | 在地图中加入文字
| geom_sf_label     | 在地图中加入标签
| geom_histogram    | 直方图（需要指定**x**）
| geom_freqpoly     | 频率密度曲线（需要指定**x**）
| geom_dotplot      | 一维散点图（需要指定**x**）
| geom_boxplot      | 箱线图（需要指定分类变量**x**，连续变量**y**，或者**lower、upper、middle、ymin、ymax**）
| geom_violin       | 小提琴图（需要指定分类变量**x**，连续变量**y**）
| geom_bar          | 柱形图（需要指定分类变量**x**，统计**x**的频数）
| geom_col          | 柱形图（需要指定分类变量**x**，连续变量**y**）
| geom_density      | 概率密度图（需要指定**x**，统计**x**取任意值时的概率密度）
| geom_density2d    | 二维概率密度图（需要指定**x、y**，统计图形中任意位置的概率密度）
| geom_qq           | 标准QQ图（需要指定**sample**）
| geom_qq_line      | 标准QQ图中的一元一次拟合线（需要指定**sample**）
| geom_quantile     | 分位数回归图（需要指定**x、y**）
| geom_smooth       | 平滑线（需要指定**x、y**，可以设置**method、formula**来修改平滑线的绘制方式；设置**se、level**来修改置信区间的绘制方式）
| geom_errorbar     | 误差区间图（需要指定**x、ymin、ymax**）
| geom_errorbarh    | 水平方向的误差区间图（需要指定**x、ymin、ymax**）
| geom_linerange    | 垂线表示的区间图（需要指定**x、ymin、ymax**）
| geom_pointrange   | 点线表示的区间图（需要指定**x、y、ymin、ymax**）
| geom_crossbar     | 柱形表示的区间图（需要指定**x、y、ymin、ymax**）
| geom_text         | 文字（需要指定**x、y、label**)
| geom_label        | 标签（需要指定**x、y、label**)
| geom_rug          | 坐标轴须线


| 函数                  | 解释说明                                                      
|:----------------------|:-----------------------------------------------------------------
| position_identity     | 保持原有位置
| position_jitter       | 对重叠的点形等进行小范围调整
| position_jitterdodge  | 对重叠的点形等进行中小范围调整
| position_dodge        | 对重叠的点形进行中等范围调整，或将柱形等不留间隔并列放置
| position_dodge2       | 对重叠的点形进行大范围调整，或将柱形等按一定间隔并列放置
| position_stack        | 将柱形等堆叠放置
| position_fill         | 将柱形等按照比例堆叠放置
| position_nudge        | 对标签等按特定值进行调整

## 2、将统计信息映射到图形属性

ggplot2中可以映射统计信息的图形属性有**color、fill、alpha、linetype、shape、size**，分别代表**轮廓颜色、填充颜色、透明度、线条类型、形状类型、形状大小**。


**discrete、continuous、ordinal、date、datetime、identity、manual**
scale_size, scale_size_area, scale_radius, 
scale_continuous_identity, scale_discrete_identity, scale_discrete_manual, scale_type,

scale_y_discrete
scale_y_continuous
scale_y_date
scale_y_time
scale_y_datetime
scale_y_sqrt
scale_y_log10
scale_x_reverse   设置横轴坐标从大到小取值

## 2、色彩管理

ggplot2中的颜色体系，与R语言本身的颜色体系类似。我们既可以通过关键字指定颜色（如**red**），也可以通过RGB颜色系统指定颜色（如**#FFFFFF**）。但ggplot2与R语言本身的调色板R略有不同，我们可以使用**RColorBrewer**程序包中的函数，查看、获取ggplot2中的系统调色板，以及调色板中的颜色。

{{< image classes="fancybox center" src="https" >}}

我们可以通过多种方式，修改ggplot2中的调色板。

使用**scale_color_brewer**函数，设置分类变量的调色板。注意这里调色板中的颜色数量是固定的，需要使用的颜色不足则只会使用其中的一部分，需要使用的颜色过多则会重复使用。

使用**scale_color_distiller**函数，设置连续变量的调色板。 这里调色板中的颜色数量依然是固定的，但**scale_color_distiller**函数会使用插值法，实现在两种不同颜色中平滑过渡。

使用**scale_color_grey、scale_color_hue、scale_color_gradient、scale_color_gradient2、scale_color_gradientn**，使用灰度色系、HSV色系、双色渐变色系、通过中间色实现的双色渐变色系、多色渐变色系。

我们还可以通过**scale_color_viridis_c、scale_color_viridis_d**函数，来使用 [viridis](https://bids.github.io/colormap/) 色系。

## 2、坐标轴管理

coord_trans       设置横纵坐标按一定规则缩放（开平方、取对数等）
coord_cartesian   设置横纵坐标数值范围，相当于将坐标轴与图形同时缩放。而**xlim、ylim**函数，相当于在原坐标轴中只绘制图形的一部分
coord_equal       设置纵横坐标轴总长度一致
coord_fixed       设置纵横坐标轴单位刻度对应的长度的比率
coord_flip        将横纵坐标轴位置互换
coord_polar       极性旋转坐标轴
coord_sf          设置坐标轴为地图坐标轴（适用于**geom_sf**绘制的地图）
coord_map         设置坐标轴为地图坐标轴（适用于**geom_map**绘制的地图）
coord_quickmap    设置坐标轴为地图坐标轴（适用于**geom_map**绘制的地图）

## 2、图形主题管理

theme_bw
theme_gray
theme_dark
theme_light
theme_minimal
theme_classic
theme_linedraw
theme_void

element_blank、element_line、element_rect、element_text、margin

```
# 设置空样式
element_blank()
# 设置矩形样式
element_rect(fill = NULL, colour = NULL, size = NULL,
  linetype = NULL, color = NULL, inherit.blank = FALSE)
# 设置线形样式
element_line(colour = NULL, size = NULL, linetype = NULL,
  lineend = NULL, color = NULL, arrow = NULL,
  inherit.blank = FALSE)
# 设置字体样式
element_text(family = NULL, face = NULL, colour = NULL,
  size = NULL, hjust = NULL, vjust = NULL, angle = NULL,
  lineheight = NULL, color = NULL, margin = NULL, debug = NULL,
  inherit.blank = FALSE)
# 设置边距
margin(t = 0, r = 0, b = 0, l = 0, unit = "pt")
```

- **line、rect、text**设置图像中所有线形、矩形、文字的样式。
- **title**设置图像中所有标题的样式（包括主标题、副标题、坐标轴标题、图例标题），继承自**text**。
- **aspect.ratio**设置纵横坐标轴总长度的比率。
- **axis.title**设置坐标轴标题的样式，继承自**title**。此外我们还可以使用**axis.title.x、axis.title.y**参数，分别设置X、Y坐标轴标题的样式；或者更明细的，使用**axis.title.x.top、 axis.title.x.bottom、axis.title.y.left,、axis.title.y.right**参数，分别设置X轴上、下以及Y轴左、右标题的样式
- **axis.text**设置坐标轴标签的样式，继承自**text**。参数**axis.text.x、axis.text.x.top、axis.text.x.bottom、axis.text.y、axis.text.y.left、axis.text.y.right**略。
- **axis.ticks**设置坐标轴刻度的样式，继承自**line**。参数**axis.ticks.x、axis.ticks.x.top、axis.ticks.x.bottom、axis.ticks.y、axis.ticks.y.left、axis.ticks.y.right**略。
- **axis.ticks.length**设置坐标轴刻度的长度。参数**axis.ticks.length.x、axis.ticks.length.x.top、axis.ticks.length.x.bottom、axis.ticks.length.y、axis.ticks.length.y.left、axis.ticks.length.y.right**略。
- **axis.line**设置坐标轴直线的样式。参数**axis.line.x、axis.line.x.top、axis.line.x.bottom、axis.line.y、axis.line.y.left、axis.line.y.right**略。

- **legend.background**设置图例背景，继承自**rect**。
- **legend.margin**设置图例边距。
- **legend.spacing**设置图例各元素之间的间距。参数**legend.spacing.x, legend.spacing.y**略。
- **legend.key**设置图例形状的背景色，继承自**rect**。
- **legend.key.size**设置图例形状背景的大小。参数**legend.key.height、legend.key.width**略。
- **legend.text**设置图例标签的样式，继承自**text**。
- **legend.text.align**设置图例标签的对齐方式，取值为0表示左对齐；0.5表示居中；1表示右对齐。
- **legend.title**设置图例标题的样式，继承自**title**。
- **legend.title.align**设置图例标题的对齐方式，取值为0表示左对齐；0.5表示居中；1表示右对齐。
- **legend.position**设置图例的摆放位置。取值可以是**none、left、right、bottom、top**；也可以是**c(x, y)**形式表示的，相对于图像的位置（其中**x、y**的取值范围均在**0-1**之间，取值为**0.5**表示居中对齐）。
- **legend.justification**设置图例的位置在**legend.position**的基础上进行调整。取值可以是**center**，也可以是**c(x, y)**形式表示的偏移量。
- **legend.direction**设置图例中的对象按水平或垂直方向依次放置，取值可以是**horizontal、vertical**。

- **llegend.box**当有多个图例时，设置图例之间的排列方式。取值可以是**horizontal、vertical**。
- **llegend.box.just**当有多个图例时，设置图例相对于图例外边框的对齐方式。取值可以是**left、right、bottom、top**。
- **legend.box.margin**当有多个图例时，设置图例外边框的边距。
- **legend.box.background**当有多个图例时，设置图例外边框的填充色。继承自**rect**。
- **legend.box.spacing**当有多个图例时，设置各个图例之间的间隔距离。

- **panel.background、panel.border**设置主图区域背景色、边框。继承自**rect**。
- **panel.spacing**设置分面图之间的间隔。参数**panel.spacing.x、panel.spacing.y**略。
- **panel.grid**设置主图区域的网格线。我们也可以设置**panel.grid.major、panel.grid.minor**，使主、辅网格线间隔出现。参数**panel.grid.major.x、panel.grid.major.y、panel.grid.minor.x、panel.grid.minor.y**略。

- **panel.ontop**设置是否将图形区域的背景置于最上层，通常仅用于图形区域没有背景色或背景色半透明的情况。
- **plot.background**设置图像区域背景色。继承自**rect**。
- **plot.title、plot.subtitle、plot.caption、plot.tag**设置图像标题、副标题、注释、标签的样式。继承自**text**。
- **plot.tag.position**设置图像标签的位置，取值可以是**topleft、top、topright、left、right、bottomleft、bottom、bottomright**，也可以是**c(x, y)**形式表示的，相对于图像的位置。
- **plot.margin**设置图像边距。

- **strip.background**设置分面图标签背景色。继承自**rect**。参数**strip.background.x、strip.background.y**略。
- **strip.text**设置分面图标签的样式。继承自**text**。参数**strip.text.x、strip.text.y**略。
- **strip.placement**设置分面图标签相对于坐标轴的放置位置，取值可以是**inside、outside**。
- **strip.switch.pad.grid、strip.switch.pad.wrap**设置分面图标签相对于坐标轴的间隔。

## 2、图形分面与布局

wrap_dims, facet_grid, facet_null, facet_wrap, 

## 2、其它常用函数
aes, 
xlab, ylab, labs
xlim, ylim, lims, expand_limits, expand_scale, 


获取更多速记手册，请前往 [这里](https://rstudio.com/resources/cheatsheets/)

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 如何使用**ggplot2**绘制扇形图、环形图、玫瑰图？
- ？
- ？

{{< /note >}}

<br>
