---
title: 使用R语言绘制图形
date: 2019-12-30
categories:
  - R语言
  - 绘图
tags:
  - R语言绘图
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


## 1、

geom_blank        空图形

geom_point        散点图（需要指定**x、y**）
geom_jitter       散点图（需要指定**x、y**，给重合的点添加偏移量）
geom_count        散点图（需要指定**x、y**，以点形大小表示重叠点的数量）
geom_hex          二维区间频率密度图（需要指定**x、y**，以六边形为单位统计频数）
geom_bin2d        二维区间频率密度图（需要指定**x、y**，以矩形为单位统计概率密度）

geom_spoke        射线（需要指定**x、y、angle、radius**）
geom_segment      点到点的直线（需要指定**x、y、xend、yend**）
geom_curve        点到点的弧线（需要指定**x、y、xend、yend**）
geom_abline       一元一次方程线（需要设置**slope、intercept**）
geom_hline        水平线（需要设置**yintercept**）
geom_vline        垂直线（需要设置**xintercept**）
geom_line         折线（需要指定**x、y**，按从左到右的顺序依次连接）
geom_path         折线（需要指定**x、y**，按点坐标出现的顺序依次连接）
geom_step         阶梯线（需要指定**x、y**，先水平后垂直）

geom_rect         矩形（需要指定**xmin、ymin、xmax、ymax**）
geom_tile         矩形（需要指定矩形中心点**x、y**，还可以指定**width、height**)
geom_raster       矩形（需要指定矩形中心点**x、y**，长宽固定为**1**）
geom_polygon      任意多边形（需要指定**x、y**)
geom_text         文字（需要指定**x、y、label**)
geom_label        标签（需要指定**x、y、label**)
geom_rug          坐标轴须线

geom_histogram    直方图（需要指定**x**）
geom_freqpoly     频率密度曲线（需要指定**x**）
geom_dotplot      一维散点图（需要指定**x**）
geom_boxplot      箱线图（需要指定分类变量**x**，连续变量**y**，或者**lower、upper、middle、ymin、ymax**）
geom_violin       小提琴图（需要指定分类变量**x**，连续变量**y**）
geom_bar          柱形图（需要指定分类变量**x**，统计**x**的频数）
geom_col          柱形图（需要指定分类变量**x**，连续变量**y**）
geom_density      概率密度图（需要指定**x**，统计**x**取任意值时的概率密度）
geom_density2d    二维概率密度图（需要指定**x、y**，统计图形中任意位置的概率密度）
geom_area         面积图（需要指定**x、y**，生成经过**x、y**中所有点的曲线与X轴之间围成的面积）
geom_ribbon       区间带图（需要指定**x、ymin、ymax**）
geom_map          形状填充图（需要指定形状轮廓**map**，形状属性**map_id**）
geom_contour      等高线图（需要指定**x、y、z**）
geom_sf           地图（需要**.shp**格式的文件）
geom_sf_text      在地图中加入文字
geom_sf_label     在地图中加入标签

geom_errorbar     误差区间图（需要指定**x、ymin、ymax**）
geom_errorbarh    水平方向的误差区间图（需要指定**x、ymin、ymax**）
geom_linerange    垂线表示的区间图（需要指定**x、ymin、ymax**）
geom_pointrange   点线表示的区间图（需要指定**x、y、ymin、ymax**）
geom_crossbar     柱形表示的区间图（需要指定**x、y、ymin、ymax**）
geom_quantile     分位数回归图（需要指定**x、y**）
geom_qq           QQ图（需要指定**sample**）
geom_qq_line      QQ图中的拟合线（需要指定**sample**）
geom_smooth       平滑线（需要指定**x、y**，可以设置**method、formula**来修改平滑线的绘制方式；设置**se、level**来修改置信区间的绘制方式）


**position**参数可以是**identity、jitter、jitterdodge、dodge、dodge2、stack、fill、nudge**，分别表示
保持原有位置；对重叠的点形等进行小范围调整；对重叠的点形等进行中小范围调整；对重叠的点形进行中等范围调整，或将柱形等不留间隔并列放置；对重叠的点形进行大范围调整，或将柱形等按一定间隔并列放置；将柱形等堆叠放置；将柱形等按照比例堆叠放置（计算比率）；对标签等按特定值进行调整。


scale_alpha, scale_alpha_continuous, scale_alpha_date, scale_alpha_datetime, scale_alpha_discrete, scale_alpha_identity, scale_alpha_manual, scale_alpha_ordinal, 
scale_color_brewer, scale_color_continuous, scale_color_discrete, scale_color_distiller, scale_color_gradient, scale_color_gradient2, scale_color_gradientn, scale_color_grey, scale_color_hue, scale_color_identity, scale_color_manual, scale_color_viridis_c, scale_color_viridis_d, scale_colour_brewer, scale_colour_continuous, scale_colour_date, scale_colour_datetime, scale_colour_discrete, scale_colour_distiller, scale_colour_gradient, scale_colour_gradient2, scale_colour_gradientn, scale_colour_grey, scale_colour_hue, scale_colour_identity, scale_colour_manual, scale_colour_ordinal, scale_colour_viridis_c, scale_colour_viridis_d, 
scale_fill_brewer, scale_fill_continuous, scale_fill_date, scale_fill_datetime, scale_fill_discrete, scale_fill_distiller, scale_fill_gradient, scale_fill_gradient2, scale_fill_gradientn, scale_fill_grey, scale_fill_hue, scale_fill_identity, scale_fill_manual, scale_fill_ordinal, scale_fill_viridis_c, scale_fill_viridis_d, 
scale_linetype, scale_linetype_continuous, scale_linetype_discrete, scale_linetype_identity, scale_linetype_manual, 
scale_shape, scale_shape_continuous, scale_shape_discrete, scale_shape_identity, scale_shape_manual, scale_shape_ordinal, 
scale_size, scale_size_area, scale_size_continuous, scale_size_date, scale_size_datetime, scale_size_discrete, scale_size_identity, scale_size_manual, scale_size_ordinal, 

scale_continuous_identity, scale_discrete_identity, scale_discrete_manual, scale_radius, scale_type,

scale_y_discrete
scale_y_continuous
scale_y_date
scale_y_time
scale_y_datetime
scale_y_sqrt
scale_y_log10
scale_y_reverse

coord_cartesian, coord_equal, coord_fixed, coord_flip, coord_map, coord_munch, coord_polar, coord_quickmap, coord_sf, coord_trans, 

theme_bw
theme_gray
theme_dark
theme_light
theme_classic
theme_minimal    
theme_linedraw


aes, xlab, ylab, xlim, ylim, lims, expand_limits, expand_scale, 
wrap_dims, facet_grid, facet_null, facet_wrap, 


获取更多速记手册，请前往 [这里](https://rstudio.com/resources/cheatsheets/)

<br>

{{< note "思考思考" "#e6e6ff" >}}
- 如何使用**ggplot2**绘制扇形图、玫瑰图？
- ？
- ？

{{< /note >}}

<br>
