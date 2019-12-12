---
title: R语言使用ggplot2绘图
date: 2019-12-30
categories:
  - R语言
  - 绘图
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

**ggplot2**是R语言中非常热门的一个绘图扩展包，可以允许我们以图层的形式逐一添加图形。这篇文章我们将介绍如何在R语言中使用ggplot2绘制优美的统计类图形。

<!--more-->

<!-- toc -->

**ggplot2**是按照图层的形式绘制图像的，在绘制图形之前我们首先需要使用{{< hl-text primary >}}ggplot{{< /hl-text >}}函数，创建一个初始化图层。此外我们还可以**ggplot**函数中，指定绘图需要使用的数据框，并使用{{< hl-text primary >}}aes{{< /hl-text >}}函数，指定如何将数据框中的变量映射到图形属性（X、Y轴坐标、图形类型等）。

接下来我们可以通过加号叠加图层或对图层某个部分的设定。**ggplot2**中绘图相关的函数，都可以使用与其相应的对象表示（**ggplot2**中首字母大写的变量，即相应绘图函数的对象）。所以叠加的过程，相当于将几个不同的对象，以向下覆盖的形式合并为同一个对象。

<br>

## 1、图形管理

**ggplot2**中所有的图形，都可以通过**geom**家族中相应的函数添加。在**geom**家族的某些函数中，可能需要设置相应图形的特定属性（比如{{< hl-text primary >}}geom_abline{{< /hl-text >}}中需要设置**slope、intercept**），这一点需要视具体函数而定。此外**geom**家族函数还可以：

- 指定当前图形的数据框、映射关系、以及是否去除其中的缺失值（**data、mapping、na.rm**参数）。

- 指定绘制当前图形时，需要对数据进行的统计方式（**stat**参数），对于不需要统计，或者已经统计好的数据，我们可以指定`stat = "identity"`；如果必须对底层数据进行统计才能绘图，则需要指定合适的，与**stat**家族函数相应的统计方式（比如{{< hl-text primary >}}geom_boxplot{{< /hl-text >}}的统计方式为`stat = "boxplot"`，对应{{< hl-text primary >}}stat_boxplot{{< /hl-text >}}）。

- 指定当前图形的摆放方式（**position**参数）：

| &emsp;&emsp; 函数                  | 解释说明                                                      
|:-----------------------------------|:-----------------------------------------------------------------
| &emsp;&emsp; position_identity     | 保持原有位置
| &emsp;&emsp; position_jitter       | 对重叠的点形等进行小范围调整
| &emsp;&emsp; position_jitterdodge  | 对重叠的点形等进行中小范围调整
| &emsp;&emsp; position_dodge        | 对重叠的点形进行中等范围调整，或将柱形等不留间隔并列放置
| &emsp;&emsp; position_dodge2       | 对重叠的点形进行大范围调整，或将柱形等按一定间隔并列放置
| &emsp;&emsp; position_stack        | 将柱形等堆叠放置
| &emsp;&emsp; position_fill         | 将柱形等按照比例堆叠放置
| &emsp;&emsp; position_nudge        | 对标签等按特定值进行调整

- 指定是否展示当前图层的图例（**show.legend**参数）。


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

<br>

## 2、图形属性映射

除了横纵坐标**x、y**之外，**ggplot2**中还可以将变量映射到图形的**color、fill、alpha、linetype、shape、size**属性，即**轮廓颜色、填充颜色、透明度、线条类型、形状类型、形状大小**（根据特定图形可能有所差异）。将变量映射到横纵坐标之外的图形属性之后，都可以自动生成图例。

我们可以将分类型、连续型、数列型、日期型、日期时间型变量（**discrete、continuous、ordinal、date、datetime**）映射给图形属性。同时我们也可以使用**scale**家族函数，设置某个图形属性对应的变量类型。比如使用{{< hl-text primary >}}scale_alpha{{< /hl-text >}}函数设置图形颜色透明度对应的变量类型，注意对于形状大小而言，我们既可以将变量映射到形状面积、也可以映射到半径，分别对应{{< hl-text primary >}}scale_size_area、scale_radius{{< /hl-text >}}函数。

使用以上方式将变量映射到横纵坐标之外的图形属性时，变量并不会直接被作为图形属性值使用，而是根据变量的大小、类别选取合适的图形属性值。比如我们设置`aes(color = "blue")`，此时图形的轮廓颜色可能是红色（**ggplot2**默认调色板中的第一个颜色）。如果需要映射的变量即图形属性值本身，则应当使用相应的**scale_*_identity**函数来映射变量。此外如果我们需要手动设置分类变量每个取值应当对应的图形属性值，则可以使用相应的**scale_*_manual**函数。

{{< image classes="fancybox center" src="https" >}}

<br>

## 3、常用绘图设置函数

**ggplot2**中的坐标轴，默认情况下总是按照从小到大的顺序取值。我们可以使用{{< hl-text primary >}}scale_x_reverse、scale_y_reverse{{< /hl-text >}}设置横轴坐标从大到小取值。

我们可以使用{{< hl-text primary >}}labs{{< /hl-text >}}，设置图像的标题、副标题、坐标轴标题、图例标题、图像说明、图像标签。此外我们还可以使用便捷函数{{< hl-text primary >}}ggtitle、xlab、ylab{{< /hl-text >}}，设置主、副标题以及X、Y轴标题。

我们可以使用{{< hl-text primary >}}lims{{< /hl-text >}}函数，设置图形的绘制边界，或图形中某个纬度（颜色、形状等）的展示边界。这种方式相当于先将超出边界的数据去除，再用剩余的数据绘图。此外ggplot2中还有另外一种设置绘制边界的方式（参考**coord_cartesian**函数），可以在不去除数据的情况下，只展示图形的一部分。两种方式在一般情况下没有差异，但会对拟合线的计算方式等有影响。此外我们还可以使用便捷函数{{< hl-text primary >}}xlim、ylim{{< /hl-text >}}，设置X、Y轴方向的图形绘制边界。特别的，我们还可以使用{{< hl-text primary >}}expand_limits{{< /hl-text >}}函数，扩展图形的绘制边界。此时，将会包含**expand_limits**中设置的值。

我们可以使用以下函数对坐标轴进行相应的调整。注意这些函数中都可以设置图形的绘制边界，但实现绘制边界的方式与**lims**函数不同。

| 函数              | 解释说明                                                      
|:------------------|:-----------------------------------------------------------------
| coord_trans       | 设置横纵坐标按一定规则缩放（开平方、取对数等）
| coord_cartesian   | 设置横纵坐标数值范围，相当于将图像的某一部分进行缩放
| coord_equal       | 设置纵横坐标轴总长度一致
| coord_fixed       | 设置纵横坐标轴单位刻度对应的长度的比率
| coord_flip        | 将横纵坐标轴位置互换
| coord_polar       | 极性旋转坐标轴
| coord_sf          | 设置坐标轴为地图坐标轴（适用于**geom_sf**绘制的地图）
| coord_map         | 设置坐标轴为地图坐标轴（适用于**geom_map**绘制的地图）
| coord_quickmap    | 设置坐标轴为地图坐标轴（适用于**geom_map**绘制的地图）

与底层函数不同，**ggplot2**中实现一页多图的方式是将分类变量映射到图像的分面属性中，根据分类变量每个值在数据框中对应的数据，绘制成一幅单独的分面图。我们可以使用{{< hl-text primary >}}facet_grid、facet_wrap{{< /hl-text >}}函数，分面绘制图形。其中前者可以接收**1-2**各分类变量，取值分别表示纵横方向的分面图；而后者只能接收**1**各分类变量，其纵横方向的分面图的数量则需要通过**nrow、ncol**参数来设置。

<br>

## 4、色彩管理

ggplot2中的颜色体系，与R语言本身的颜色体系类似。我们既可以通过关键字指定颜色（如**red**），也可以通过RGB颜色系统指定颜色（如**#FFFFFF**）。但ggplot2与R语言本身的调色板R略有不同，我们可以使用**RColorBrewer**程序包中的函数，查看、获取ggplot2中的系统调色板，以及调色板中的颜色。

{{< image classes="fancybox center" src="https" >}}

我修改**ggplot2**中的默认调色板时，我们既可以既可以从系统调色板中选择、也可以从某个色系（或颜色集合）中手动生成调色板。注意**ggplot2**中图形的轮廓颜色与填充颜色可以分别对应不同的调色板，这里我们以轮廓颜色的调色板为例展开说明，设置填充颜色的调色板也可以用同样的规律。

- 使用{{< hl-text primary >}}scale_color_brewer{{< /hl-text >}}函数，设置分类变量的调色板。注意这里调色板中的颜色数量是固定的，需要使用的颜色不足则只会使用其中的一部分，需要使用的颜色过多则会重复使用。

- 使用{{< hl-text primary >}}scale_color_distiller{{< /hl-text >}}函数，设置连续变量的调色板。此时调色板中的颜色数量依然是固定的，但这里会使用插值法，实现在两种不同颜色中平滑过渡。

- 通过{{< hl-text primary >}}scale_color_grey、scale_color_hue、scale_color_gradient、scale_color_gradient2、scale_color_gradientn{{< /hl-text >}}函数，使用灰度色系、HSV色系、双色渐变色系、通过饱和度或明亮度实现的双色渐变色系、多色渐变色系。

- 通过{{< hl-text primary >}}scale_color_viridis_c、scale_color_viridis_d{{< /hl-text >}}函数，使用 [viridis](https://bids.github.io/colormap/) 色系。

<br>

## 5、图形细节管理

```R
# ggplot2中的绘图细节
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
    plot.background = element_rect(color = "blue", size = 1),
    panel.border = element_rect(color = "red"),
    legend.box.background = element_rect(color = "green"),
    legend.box.margin = margin(5, 5, 5, 5),
    legend.box.just = "left",
    legend.background = element_rect(color = "gray30"),
    legend.key = element_rect(fill = "gray90"),
    legend.key.width = unit(15, "pt"),
  )
```

{{< image classes="fancybox center" src="https" >}}

我们可以在**ggplot2**中使用{{< hl-text primary >}}theme{{< /hl-text >}}函数控制图形细节。对于图形中的边距、间距、矩形样式、线形样式、字体样式等细节的控制，需要是用到{{< hl-text primary >}}margin、unit、element_blank、element_line、element_rect、element_text{{< /hl-text >}}等函数生成的对象。注意对于矩形、线形、字体等类型的绘图细节，我们不能直接使用**NULL**值将其设置为空，而需要使用到{{< hl-text primary >}}element_blank{{< /hl-text >}}函数。

```R
# 设置边距
margin(t = 0, r = 0, b = 0, l = 0, unit = "pt")
# 设置间距等
unit(x, units, data=NULL)
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
```

一系列设置完备的图形细节可以看作是一套图形主题，**ggplot2**中预设的图形主题分别是{{< hl-text primary >}}theme_bw、theme_gray、theme_dark、theme_light、theme_minimal、theme_classic、theme_linedraw、theme_void{{< /hl-text >}}，其中绘图时默认的图形主题是**theme_gray**。我们可以以某个图形主题为基础，修改特定的绘图细节。以下是**theme**函数中支持修改的绘图细节：

- **line、rect、text**设置图像中所有线形、矩形、文字的样式。
- **title**设置图像中所有标题的样式（包括主标题、副标题、坐标轴标题、图例标题），继承自**text**。
- **aspect.ratio**设置纵横坐标轴总长度的比率。

- **plot.background**设置图像区域背景色。继承自**rect**。
- **plot.margin**设置图像边距。继承自**margin**。
- **plot.title、plot.subtitle、plot.caption、plot.tag**设置图像标题、副标题、注释、标签的样式。继承自**text**。
- **plot.tag.position**设置图像标签的位置，取值可以是**topleft、top、topright、left、right、bottomleft、bottom、bottomright**，也可以是**c(x, y)**（取值范围均在**0-1**之间，**0.5**表示居中）表示的，相对于图像的位置。

- **panel.background、panel.border**设置主图区域背景色、边框。继承自**rect**。
- **panel.spacing**设置分面图之间的间隔。参数**panel.spacing.x、panel.spacing.y**略。继承自**unit**。
- **panel.ontop**设置是否将主图区域的背景置于最上层，通常仅用于主图区域没有背景色或背景色半透明的情况。
- **panel.grid**设置主图区域的网格线。继承自**line**。我们也可以设置**panel.grid.major、panel.grid.minor**，使主、辅网格线间隔出现。参数**panel.grid.major.x、panel.grid.major.y、panel.grid.minor.x、panel.grid.minor.y**略。

- **strip.placement**设置分面图页眉相对于坐标轴的放置位置，取值可以是**inside、outside**。
- **strip.switch.pad.grid、strip.switch.pad.wrap**设置分面图标签相对于坐标轴的间隔。继承自**unit**。
- **strip.background**设置分面图页眉背景的样式。继承自**rect**。参数**strip.background.x、strip.background.y**略。
- **strip.text**设置分面图页眉标签的样式。继承自**text**。参数**strip.text.x、strip.text.y**略。

- **axis.title**设置坐标轴标题的样式，继承自**title**。此外我们还可以使用**axis.title.x、axis.title.y**参数，分别设置X、Y坐标轴标题的样式；或者更明细的，使用**axis.title.x.top、 axis.title.x.bottom、axis.title.y.left,、axis.title.y.right**参数，分别设置X轴上、下以及Y轴左、右标题的样式
- **axis.text**设置坐标轴标签的样式，继承自**text**。参数**axis.text.x、axis.text.x.top、axis.text.x.bottom、axis.text.y、axis.text.y.left、axis.text.y.right**略。
- **axis.ticks**设置坐标轴刻度的样式，继承自**line**。参数**axis.ticks.x、axis.ticks.x.top、axis.ticks.x.bottom、axis.ticks.y、axis.ticks.y.left、axis.ticks.y.right**略。
- **axis.ticks.length**设置坐标轴刻度的长度。参数**axis.ticks.length.x、axis.ticks.length.x.top、axis.ticks.length.x.bottom、axis.ticks.length.y、axis.ticks.length.y.left、axis.ticks.length.y.right**略。
- **axis.line**设置坐标轴直线的样式。继承自**line**。参数**axis.line.x、axis.line.x.top、axis.line.x.bottom、axis.line.y、axis.line.y.left、axis.line.y.right**略。

- **legend.position**设置图例的摆放位置。取值可以是**none、left、right、bottom、top**；也可以是**c(x, y)**表示的，相对于图像的位置。
- **legend.justification**设置图例的位置在**legend.position**的基础上进行调整。取值可以是**center**，也可以是**c(x, y)**表示的偏移量。
- **legend.direction**设置图例中的对象按水平或垂直方向依次放置，取值可以是**horizontal、vertical**。
- **legend.background**设置图例背景，继承自**rect**。
- **legend.margin**设置图例边距。继承自**margin**。
- **legend.spacing**设置图例各元素之间的间距。继承自**unit**。参数**legend.spacing.x, legend.spacing.y**略。
- **legend.title**设置图例标题的样式，继承自**title**。
- **legend.title.align**设置图例标题的对齐方式，取值范围在**0-1**之间（0表示左对齐；0.5表示居中；1表示右对齐）。
- **legend.text**设置图例标签的样式，继承自**text**。
- **legend.text.align**设置图例标签的对齐方式，取值范围在**0-1**之间。
- **legend.key**设置图例形状的背景，继承自**rect**。
- **legend.key.size**设置图例形状背景的大小。继承自**unit**。参数**legend.key.height、legend.key.width**略。

- **llegend.box**当有多个图例时，设置图例之间的排列方式。取值可以是**horizontal、vertical**。
- **llegend.box.just**当有多个图例时，设置图例相对于图例外边框的对齐方式。取值可以是**left、right、bottom、top**。
- **legend.box.background**设置多个图例的外边框背景。继承自**rect**。
- **legend.box.margin**设置多个图例的外边距。继承自**margin**。
- **legend.box.spacing**设置多个图例的之间的间隔距离。继承自**unit**。

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 如何使用**ggplot2**绘制扇形图、环形图、玫瑰图？
- ？
- ？

{{< /note >}}

<br>
