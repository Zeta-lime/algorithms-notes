# 第二章 学习使用Markdown

---
[toc]

- 一些Markdown的学习网站
  - [GitHub guide关于markdown的说明](https://guides.github.com/features/mastering-markdown/)
  - [Markdown 语法基础及使用教程](http://col.dog/2015/11/22/Markdown-Syntax/)
  - [github guides](https://guides.github.com/features/mastering-markdown/)
  - [GitHub Flavored Markdown](https://github.github.com/gfm/)
  - [dillinger编辑器的markdown介绍](https://www.markdownguide.org/)

## 2.1 一些常见的问题（FAQ）

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
<a name="anchor2"></a>here
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
- [ ] *<u>怎样跳转到其他markdown文件上的锚点？（尚不知道）</u>*

参考：
1.[Cross-reference (named anchor) in markdown](https://stackoverflow.com/questions/5319754/cross-reference-named-anchor-in-markdown/17028463#17028463)
2.[Anchors in Markdown](https://gist.github.com/asabaylus/3071099#anchors-in-markdown)


### Q2：常用的文字样式
- 一些有用的HTML标签
<Center>文字居中</Center>
<u>下划线</u>
空行<br><br>空行
<!--这是一段注释。注释不会在浏览器中显示。-->
- 高亮
==marked==
- *斜体*、**粗体**、~~删除线~~
- 下标
30~th~
- 上标
30^th^

- 脚注
Content [^1]

[^1]: Hi! This is a footnote

- 下标
H~2~O

### Q3：如何插入doc，html文件？

- 通用文本转换工具[pandoc](http://pandoc.org/)
- 在线转换 <https://word-to-markdown.herokuapp.com/>

### Q4: 如何输入数学公式？

[MathJax basic tutorial and quick reference](https://math.meta.stackexchange.com/questions/5020/mathjax-basic-tutorial-and-quick-reference)
[MathJax使用LaTeX语法编写数学公式教程](https://www.zybuluo.com/knight/note/96093)
- 行内公式：$\sum_{i=0}^n i^2 = \frac{(n^2+n)(2n+1)}{6}$

- 行外公式：$$\sum_{i=0}^n i^2 = \frac{(n^2+n)(2n+1)}{6}$$

- 大括号：$\{(n^2+n)(2n+1)+1\}-n(n+1)$

- 希腊字母：

  | 显示 | 命令 | 显示 | 命令 |
  | :-: | :-: | :-: | :-: |
  | α | \alpha | β | \beta |
  | γ | \gamma | δ | \delta |
  | ε | \epsilon | ζ | \zeta |
  | η | \eta | θ | \theta |
  | ι | \iota | κ | \kappa |
  | λ | \lambda | μ | \mu |
  | ν | \nu | ξ | \xi |
  | π | \pi | ρ | \rho |
  | σ | \sigma | τ | \tau |
  | υ | \upsilon | φ | \phi |
  | χ | \chi | ψ | \psi |
  | ω | \omega |   |   |

  若需要大写希腊字母，将命令首字母大写即可。
  `\Gamma`呈现为$\Gamma$

- 字母修饰:

  - 上下标

    *   上标：`^`
    *   下标：`_`
    *   举例：`C_n^2`呈现为$C_2^n$

  - 矢量

    *   `\vec a`呈现为$\vec{a}$ 
    *   `\overrightarrow{xy}`呈现为$\overrightarrow{xy}$

  - 字体

    *   Typewriter：`\mathtt{A}`呈现为$\mathtt{A}$
    $\mathtt{ABCDEFGHIJKLMNOPQRSTUVWXYZ}$

    *   Blackboard Bold：`\mathbb{A}`呈现为$\mathbb{A}$ 
    $\mathbb{ABCDEFGHIJKLMNOPQRSTUVWXYZ}$

    *   Sans Serif：`\mathsf{A}`呈现为$\mathsf{A}$ 
    $\mathsf{ABCDEFGHIJKLMNOPQRSTUVWXYZ}$

  - 分组

    *   使用`{}`将具有相同等级的内容扩入其中，成组处理
    *   举例：`10^{10}`呈现为$10^{10}$，而`10^10`呈现为$10^10$

  - 括号

    *   小括号：`()`呈现为$()$
    *   中括号：`[]`呈现为$[]$
    *   尖括号：`\langle,\rangle`呈现为$\langle,\rangle$ 
    *   使用`\left(`或`\right)`使符号大小与邻近的公式相适应；该语句适用于所有括号类型 

        *   `(\frac{x}{y})`呈现为$(\frac{x}{y})$
        *   而`\left(\frac{x}{y}\right)`呈现为$\left(\frac{x}{y}\right)$

  - 求和、极限与积分

    *   求和：`\sum` 
        *   举例：$$\sum_{i=1}^n{a_i}$$
    *   极限：`\lim`
        $$\lim_{x \to \infty}$$
    *   积分：`\int` 
        *   举例：$$\int_0^\infty{f(x)dx}$$

  - 分式与根式

    *   分式(fractions)：$\frac{x}{y}$
    *   根式：$\sqrt[x]{y}$

  - 特殊函数

    *   `\函数名`
    *   举例：$\sin x$，$\ln x$，$\max(A,B,C)$

  - 特殊符号

    | 显示 | 命令 |
    | :-: | :-: |
    | ∞ | \infty |
    | ∪ | \cup |
    | ∩ | \cap |
    | ⊂ | \subset |
    | ⊆ | \subseteq |
    | ⊃ | \supset |
    | ∈ | \in |
    | ∉ | \notin |
    | ∅ | \varnothing |
    | ∀ | \forall |
    | ∃ | \exists |
    | ¬ | \lnot |
    | ∇ | \nabla |
    | ∂ | \partial |

  - 空格

    *   LaTeX语法本身会忽略空格的存在
    *   小空格：$a\ b$
    *   4格空格：$a\quad b$

  - 矩阵

    - 基本语法

      *   起始标记`\begin{matrix}`，结束标记\end{matrix}`
      *   每一行末尾标记`\\`，行间元素之间以`&`分隔
      *   举例

    $$\begin{matrix}
    1&0&0\\
    0&1&0\\
    0&0&1\\
    \end{matrix}$$

    - 矩阵边框

      *   在起始、结束标记处用下列词替换`matrix` 

          *   `pmatrix`：小括号边框
          *   `bmatrix`：中括号边框
          *   `Bmatrix`：大括号边框
          *   `vmatrix`：单竖线边框
          *   `Vmatrix`：双竖线边框

    - 省略元素

      *   横省略号：`\cdots`
      *   竖省略号：`\vdots`
      *   斜省略号：`\ddots`
      *   举例

          $$\begin{bmatrix}
          {a_{11}}&{a_{12}}&{\cdots}&{a_{1n}}\\
          {a_{21}}&{a_{22}}&{\cdots}&{a_{2n}}\\
          {\vdots}&{\vdots}&{\ddots}&{\vdots}\\
          {a_{m1}}&{a_{m2}}&{\cdots}&{a_{mn}}\\
          \end{bmatrix}$$

    - 阵列

      *   需要array环境：起始、结束处以`{array}`声明
      *   对齐方式：在`{array}`后以`{}`逐行统一声明 

          *   左对齐：`l`；居中：`c`；右对齐：`r`
          *   竖直线：在声明对齐方式时，插入`|`建立竖直线
      *   插入水平线：`\hline`
      *   举例
      ```
      $$
      \begin{array}{c|lcr}
      n & \text{Left} & \text{Center} & \text{Right} \\
      \hline
      1 & 0.24 & 1 & 125 \\
      2 & -1 & 189 & -8 \\
      3 & -20 & 2000 & 1+10i
      \end{array}
      $$
      ```

      $$ \left[
    \begin{array}{cc|c}
      1&2&3\\
      4&5&6
    \end{array}
    \right] $$


  - 方程组

    *   需要cases环境：起始、结束处以`{cases}`声明
    *   举例

    $$\begin{cases}
    a_1x+b_1y+c_1z=d_1\\
    a_2x+b_2y+c_2z=d_2\\
    a_3x+b_3y+c_3z=d_3\\
    \end{cases}
    $$

### Q5：如何插入高级图表（流程图等）？

这不是标准markdown支持的，需要额外的插件
参考一些在线的markdown编辑器如cmd markdown、有道markdown、CSDN markdown
参考 <https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/diagrams>

### Q6: 如何高亮语法、代码块显示行号？

这不是标准markdown支持的，需要额外的插件，这里是markdown preview enhanced(MPE)插件的语法。
#### 语法高亮

你可以给你的代码块添加任何一种语言的语法高亮

例如，给 ruby 代码添加语法高亮：

```ruby
require 'redcarpet'
markdown = Redcarpet.new("Hello World!")
puts markdown.to_html
```
#### 代码块 class（MPE 扩展的特性）

你可以给你的代码块设置 class。

例如，添加 class1 class2 到一个 代码块：

```javascript {.class1 .class}
function add(x, y) {
  return x + y
}
```
#### 代码行数

如果你想要你的代码块显示代码行数，只要添加 line-numbers class 就可以了。

例如：

```javascript {.line-numbers}
function add(x, y) {
  return x + y
}
```

### Q7: 如何插入图片，图片链接？

- 行内式：
`[![无法连接时显示的文字](img位置 "img说明")](图片转向的链接)`
`无法显示时的文字`、`img说明`可以不填写
最简单的形式：`[![](img位置)](转向的链接)`
- 参考式：
```
[![][baidu-logo]][site]
[baidu-logo]: https://www.baidu.com/img/baidu_jgylogo3.gif "描述"
[site]: https://www.baidu.com/
```


### Q8：如何复制粘贴网页上的内容?

原理是复制HTML代码转为markdown，需要额外的工具
有现成的网站[md2](https://phodal.github.io/2md/),该项目的GitHub：<https://github.com/phodal/2md>
