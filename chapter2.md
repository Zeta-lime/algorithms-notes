# 第二章 学习使用Markdown
---
- 一些Markdown的学习网站
  - [GitHub guide关于markdown的说明](https://guides.github.com/features/mastering-markdown/)
  - [Markdown 语法基础及使用教程](http://col.dog/2015/11/22/Markdown-Syntax/)
  - [github guides](https://guides.github.com/features/mastering-markdown/)

## 2.1 一些常见的问题

### Q1：如何使用anchor（锚点）进行跳转？
* 跳转到标题：
```
#heading1 {#anchor1}
context...
[jump to heading1](#anchor1)
```
* 跳转到页内任意位置：
首先在你需要在**目的点**位置设置锚点：
```
<div id='anchor2'></div>here
```
**源点**：
```
[jump to here](#anchor2)
```
* 跳转到其他markdown文件(`.\xxx\xx.md`)或者某个网址(`http://www.xxx.com/`)上的锚点(anchor3)：
```
[jump to](.\xxx\xx.md)
[jump to](http://www.xxx.com/#anchor3)
```
*怎样跳转到其他markdown文件上的锚点？（尚不知道）*


参考：
1.[Cross-reference (named anchor) in markdown](https://stackoverflow.com/questions/5319754/cross-reference-named-anchor-in-markdown/17028463#17028463)
2.[Anchors in Markdown](https://gist.github.com/asabaylus/3071099#anchors-in-markdown)


### Q2：如何设置多行空白？
### Q3：如何插入doc，html文件？
### Q4: 如何输入数学公式？
### Q5：如何插入高级图表（流程图等）？
### Q6: 如何使代码块显示行号？
### Q7: 如何插入图片，图片链接？



$$
e^{i\pi}+1=0
$$

