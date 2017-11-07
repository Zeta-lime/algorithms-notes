# 第三章 使用Atom作为Markdown编辑器

---
[TOC]

## 3.1 Atom入门

一些参考网站：
- 极客学院atom基础教程：
http://wiki.jikexueyuan.com/project/atom/basis.html
- csdn 2个atom专辑：
http://blog.csdn.net/column/details/atom.html
http://blog.csdn.net/column/details/atom-tutorial.html

## 3.2 快捷键

### 常用快捷键(Windows)

- 文件
`ctrl-n`新建文件
`ctrl-s`保存
`ctrl-shift-s`另存为
`ctrl-o`打开文件
`ctrl-shift-o`打开文件夹
`ctrl-t (ctrl-p)`	打开project中的文件
`ctrl-b`	打开buff中的文件（buff指的是当前在编辑面板打开的文件）
- 视图
>视图中绿色高亮的文件、行号表示新加入git，黄色部分表示修改但还没有commit to git，灰色表示ignore，蓝色表示重命名，红色表示git已经移除
参见`ctrl-shift-p styleguide`

`ctrl-\`打开、关闭project面板
`alt-\`跳转到project文件tree中操作
`ctrl-alt-[或]`展开、折叠当前行
`ctrl-alt-shift-[或]`展、折叠全部
`ctrl-k, left/right/up/down`在相应方向上分割面板
`ctrl-k, ctrl-left/right/up/down`	光标跳到相应方向的面板上
`ctrl-shift-\`在目录树中显示当前编辑的文件位置
- 跳转
`home`、`end`跳到句首、句尾
`ctrl-home`、`ctrl-end`跳到全文首部、尾部
`ctrl-方向键left`、`ctrl-方向键right`调到词首、词尾
`ctrl-r`打开导航
`ctrl-m`前后括号之间跳转
`ctrl-g`跳转到指定行列
- 选取
`ctrl-l`选取一行
`shift-方向键左、右`向左向右选取单个字母
`ctrl-shift-方向键左、右`以词为单位向左向右选取
`shift-up` 向上选择
`shift-down` 向下选择
`shift-home\end`向左、右选取直到句首、尾
`shift-pageup\pagedown`以页面为单位向上向下选取
`ctrl-shift-home\end`向前、后选取直到文首、尾
- 编辑
`ctrl-shift-c`复制当前文件的路径
`ctrl-/`对代码进行注释
`ctrl-shift-d`复制一行
`ctrl-shift-k`删除一行
`ctrl-[或]`缩进
`ctrl-j` 将下一行与当前行合并
`ctrl-k ctrl-l`使当前字符小写
`ctrl-k ctrl-u`使当前字符大写
`ctrl-up\down`代码上移、下移
- 多行编辑
`ctrl`+鼠标
`ctrl-d`选取文档中和当前单词相同的下一处
`alt-ctrl-up\down`在当前光标的上面和下面增加多个光标
`alt-F3`选择文档中与当前光标所在单词一样的所有单词，并进入多行编辑模式
- 查找
`ctrl-f`	在buff中查找
`ctrl-shift-f`	在project中查找
>查找右上角四个按键分别是正则表达式、大小写匹配、只在选中的部分中查找、作为单个词查找（在其他词中出现的情况不算在内）

- 命令行
`ctrl-shift-p`打开命令行
atom-terminal:
    - Open terminal on current file's directory with ctrl-shift-t.
    - Open a terminal in the project's root directory with alt-shift-t.
### 自定义快捷键

ATOM按键绑定 **keybindings** 即自定义快捷键，可以在ATOM的 **keymap.cson** 文件下自定义按键绑定。

#### 了解CSON

**CSON** 全称为 **CoffeeScript Object Notation** ，类似我们经常使用的 **JSON(JavaScript Object Notation)** ，二者都是储存结构化数据的文本格式，表现为由键值对组成的简单对象的形式。
什么是 JSON ？
>JSON 指的是 JavaScript 对象表示法（JavaScript Object Notation）
JSON 是轻量级的文本数据交换格式
JSON 独立于语言
JSON 具有自我描述性，更易理解
JSON 使用 JavaScript 语法来描述数据对象，但是 JSON 仍然独立于语言和平台。JSON 解析器和 JSON 库支持许多不同的编程语言。
>

CSON文件格式示例如下：

><code class="hljs css has-numbering">key:
   key1:value1
   key2:value2
   key3:[value,value]</code>

>示例：来自[百度知道](https://zhidao.baidu.com/question/1754528056363532548.html)

```
ret, input1, input2 ,input3 =showUI("{ \"style\":\"default\", \"views\" :[ { \"type\":\"Label\", \"text\":\"设置\", \"size\":25,\"align\":\"center\",\"color\":\"0,0,255\"},{\"type\":\"RadioGroup\", \"list\":\"选项1,选项2,选项3,选项4,选项5,选项6,选项7\",\"select\":\"1\"},{\"type\":\"Edit\", \"prompt\":\"测试三下\",\"text\":\"默认值\", \"size\":15,\"align\":\"left\", \"color\":\"255,0,0\"},{\"type\":\"CheckBoxGroup\", \"list\":\"选项1,选项2,选项3,选项4,选项5,选项6,选项7\",\"select\":\"3@5\"}]}")
```
>- {a:"a"}这就是一个JSON数据。 JSON数据是用键值对的形式存储的。冒号（:）前面的是键，冒号后面的是值。JSON,的每一个值之间可以用分号（;）隔开。大的类可以用{}大括号包围他其中的值，集合可以用[]中括号，包围值

1. 上面的代码，其重点是调用一个 showUI 的函数，这个函数其功能大概是根据传递过来的参数来显示某个UI的。
2. 传递给 showUI 函数的参数，由于传递的参数数量比较多，所以采用的是将多个参数打包成 json 字符串的形式。
3.  json 简单说就是 javascript 中的对象和数组，所以这两种结构就是对象和数组两种结构，通过这两种结构可以表示各种复杂的结构，举例，其形式如下：
`{"firstName":"Brett","lastName":"McLaughlin","email":"aaaa"}`
4. 看起来上面的挺复杂，将这个格式重新排列下，可能更容易看出来：

```javascript {.line-numbers}
{
    "style": "default",//风格名称
    "views": [//风格的具体样式设置
        {
            "type": "Label",//Label元素的设置
            "text": "设置",
            "size": 25,
            "align": "center",
            "color": "0,0,255"
        },
        {
            "type": "RadioGroup",//RadioGroup元素的设置
            "list": "选项1,选项2,选项3,选项4,选项5,选项6,选项7",
            "select": "1"
        },
        {
            "type": "Edit",//Edit元素的设置
            "prompt": "测试三下",
            "text": "默认值",
            "size": 15,
            "align": "left",
            "color": "255,0,0"
        },
        {
            "type": "CheckBoxGroup",//CheckBoxGroup元素的设置
            "list": "选项1,选项2,选项3,选项4,选项5,选项6,选项7",
            "select": "3@5"
        }
    ]
}
```
>从上面的数据结构可以看出，这些参数是对UI一些元素进行设置。


对象是CSON的基石，由缩进（像上面的示例那样）或者花括号（{}）描述。一个键的值可以是字符串、数字、对象、布尔值、null或者上述数据类型的一个数组。 
Atom的所有配置文件（除了样式表和初始脚本）全部用CSON编写。

#### 设置按键绑定

可以在在设置菜单可以查看可以使用的快捷键： 
![这里写图片描述](http://img.blog.csdn.net/20160709091619937)
如上图所示： 
按键绑定 = 快捷键(Keystroke) + 执行命令(Command) + 来源(Source) + 选择器(Selector)

*   快捷键：按键组合
*   执行命令：按下快捷键后触发的命令
*   来源：ATOM内置核心或ATOM插件
*   选择器：类似CSS选择器，快捷键只对特定的选择器生效

如下图所示，ctrl-up快捷键的默认功能是将光标所在行上移，复制该按键绑定 
![这里写图片描述](http://img.blog.csdn.net/20160709093346990)
并粘贴到keymap.cson文件 
![这里写图片描述](http://img.blog.csdn.net/20160709093826201) 
只需要在keymap.cson文件修改快捷键组合即可设置按键绑定非常方便，修改完成后无需重启编辑器即可生效，修改如下： 
![这里写图片描述](http://img.blog.csdn.net/20160709221657735)

#### 解决按键绑定冲突

有时使用从ATOM插件库下载的插件默认的快捷键时会发现快捷键失效，此时可以去ATOM**按键绑定菜单**里搜索该快捷键所对应的执行命令，若发现按键绑定冲突可以修改快捷键或**取消**不经常使用的按键绑定。 
取消按键绑定操作如下： 
![这里写图片描述](http://img.blog.csdn.net/20160709095623567) 
然后去按键绑定菜单列表确认该按键绑定是否已经取消 
![这里写图片描述](http://img.blog.csdn.net/20160709095840619)

#### 设置按键绑定注意事项

在设置按键绑定指定的**选择器**不像CSS的选择器，CSON的键在每个对象中只能出现一次。如果存在重复的键，最后一次出现的那个会覆盖其他所有同名的键，Atom所有的配置文件都遵循这个原则。 
**错误的按键绑定** 
![这里写图片描述](http://img.blog.csdn.net/20160709094500819) 
选择器“atom-workspace”在keymap.cson文件下重复出现，因此下边的按键绑定将覆盖上面的按键绑定。 
**正确配置：** 
![这里写图片描述](http://img.blog.csdn.net/20160709094734400)

## 3.2 插件
### 如何安装插件
  >两种方式：
  >1. Settings->install
  >2. 在终端使用apm命令:apt install 插件名

### 一些推荐的插件
  - 汉化
  [simplified-chinese-menu](https://atom.io/packages/simplified-chinese-menu)
  - 编辑增强
  [markdown-preview-enhanced](https://atom.io/packages/markdown-preview-enhanced)Markdown增强
  [highlight-selected](https://atom.io/packages/highlight-selected)高亮与选择词相同的位置
  [highlight-line](https://atom.io/packages/highlight-line)高亮当前编辑的行
  [activate-power-mode](https://atom.io/packages/activate-power-mode) 炫酷的打字特效
  - coding增强
  [atom-terminal](https://atom.io/packages/atom-terminal)
  - 主题  
  [atom-material-ui](https://atom.io/themes/atom-material-ui) 好看到爆  
  [atom-material-syntax](https://atom.io/themes/atom-material-syntax)
  - 美化  
  [atom-beautify](https://atom.io/packages/atom-beautify) 一键代码美化  
  [file-icons](https://atom.io/packages/file-icons) 给文件加上好看的图标  
  [atom-minimap](https://atom.io/users/atom-minimap) 方便美观的缩略滚动图  
  [pretty-json](https://atom.io/packages/pretty-json) json格式化工具  
  - git  
  [atomatigit](https://atom.io/packages/atomatigit) 可视化git操作  
  [git-time-machine](https://atom.io/packages/git-time-machine) git版本对比工具，可视化选择每一个commit  
  [merge-conflicts](https://atom.io/packages/merge-conflicts) 合并冲突可视化工具
  - 代码提示  
  [emmet](https://atom.io/packages/emmet) 这个不用介绍了吧  
  [atom-ternjs](https://atom.io/packages/atom-ternjs) js代码提示很强大，高度定制化  
  [docblockr](https://atom.io/packages/docblockr) jsdoc 给js添加注释  
  [autoclose-html](https://atom.io/packages/autoclose-html) 闭合html标签  
  [color-picker](https://atom.io/packages/color-picker) 取色器 必备插件  
  [pigments](https://atom.io/packages/pigments) 颜色显示插件 必装  
  [terminal-panel](https://atom.io/packages/terminal-panel) 直接在atom里面写命令了  
  [svg-preview](https://atom.io/packages/svg-preview) svg预览
  - 便捷操作  
  [advanced-open-file](https://atom.io/packages/advanced-open-file) 快速打开、切换文件  
  [project-folder](https://atom.io/packages/project-folder) 快速打开、切换项目  
  [script](https://atom.io/packages/script) 立即执行当前js文件
  - 高亮  
  [language-vue](https://atom.io/packages/language-vue) vue框架代码高亮
  - 终端  
  [platformio-atom-ide-terminal](https://atom.io/packages/platformio-ide-terminal) 终端插件，支持显示、隐藏及多窗口
