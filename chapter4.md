# 第四章： 使用git

---

[TOC]

- 网站资源：
    - [一个very nice 的网站，手把手教你上手——gitimmersion](http://gitimmersion.com/)
    - [猴子都能懂的GIT入门](https://backlog.com/git-tutorial/cn/)
    - [《git权威指南》](http://www.worldhello.net/gotgit/)以及[gotgithub](http://www.worldhello.net/gotgithub/)
    - 两个国外的网站：<http://gitready.com/>、 <https://git.wiki.kernel.org/index.php/Git_FAQ>
    <http://gitreal.codeschool.com/?utm_source=github&utm_medium=codeschool_option&utm_campaign=trygit>
    - [易百git教程](http://www.yiibai.com/git/)
    - [阮一峰Git远程操作详解](http://www.ruanyifeng.com/blog/2014/06/git_remote.html)
    - [15分钟的简单git流程，交互式教学](https://try.github.io/levels/1/challenges/1)
    - [git - 简明指南](http://rogerdudler.github.io/git-guide/index.zh.html)
    - [think-like-a-git](http://think-like-a-git.net/)
    - [图解git](http://marklodato.github.io/visual-git-guide/index-zh-cn.html)
    - [Customized Training](https://services.github.com/customized-training)
## 4.0 git简介

### 图解git
- git基本概念

![git基本概念](/assets/git基本概念.png)

- git命令

![git命令](http://img.blog.csdn.net/20161202183909310 "git命令")

### git原理概念
**直接记录快照，而非差异比较**
Git 和其它版本控制系统（包括 Subversion 和近似工具）的主要差别在于 Git 对待数据的方法。 概念上来区分，其它大部分系统以文件变更列表的方式存储信息。 这类系统（CVS、Subversion、Perforce、Bazaar 等等）将它们保存的信息看作是一组基本文件和每个文件随时间逐步累积的差异。
![20120201121203_850](/assets/20120201121203_850.png)
Figure 存储每个文件与初始版本的差异.
Git 不按照以上方式对待或保存数据。 反之，Git 更像是把数据看作是对小型文件系统的一组快照。 每次你提交更新，或在 Git 中保存项目状态时，它主要对当时的全部文件制作一个快照并保存这个快照的索引。 为了高效，如果文件没有修改，Git 不再重新存储该文件，而是只保留一个链接指向之前存储的文件。 Git 对待数据更像是一个 快照流。
![20120201121204_39](/assets/20120201121204_39.png)
Figure存储项目随时间改变的快照

**近乎所有操作都是本地执行**
在 Git 中的绝大多数操作都只需要访问本地文件和资源，一般不需要来自网络上其它计算机的信息。 因为你在本地磁盘上就有项目的完整历史，所以大部分操作看起来瞬间完成。

举个例子，要浏览项目的历史，Git 不需外连到服务器去获取历史，然后再显示出来————它只需直接从本地数据库中读取。 你能立即看到项目历史。 如果你想查看当前版本与一个月前的版本之间引入的修改，Git 会查找到一个月前的文件做一次本地的差异计算，而不是由远程服务器处理或从远程服务器拉回旧版本文件再来本地处理。

**Git 保证完整性**
Git 中所有数据在存储前都计算校验和，然后以校验和来引用。 这意味着不可能在 Git 不知情时更改任何文件内容或目录内容。 这个功能建构在 Git 底层，是构成 Git 哲学不可或缺的部分。 若你在传送过程中丢失信息或损坏文件，Git 就能发现。

Git 用以计算校验和的机制叫做 SHA-1 散列（hash，哈希）。 这是一个由 40 个十六进制字符（0-9 和 a-f）组成字符串，基于 Git 中文件的内容或目录结构计算出来。 SHA-1 哈希看起来是这样：

24b9da6552252987aa493b52f8696cd6d3b00373
Git 中使用这种哈希值的情况很多，你将经常看到这种哈希值。 实际上，Git 数据库中保存的信息都是以文件内容的哈希值来索引，而不是文件名。

**Git 一般只添加数据**
你执行的 Git 操作，几乎只往 Git 数据库中增加数据。 很难让 Git 执行任何不可逆操作，或者让它以任何方式清除数据。 同别的 VCS 一样，未提交更新时有可能丢失或弄乱修改的内容；但是一旦你提交快照到 Git 中，就难以再丢失数据，特别是如果你定期的推送数据库到其它仓库的话。深度探讨 Git 如何保存数据及恢复丢失数据的话题，请参考撤消操作。

**文件的三种状态**
本地的文件有三种状态，你的文件可能处于其中之一：已提交（committed）、已修改（modified）和已暂存（staged）。
已提交表示该文件已经被安全地保存在本地数据库 中了；已修改表示修改了某个文件，但还没有提交保存；已暂存表示把已修改的文件放在下次提交时要保存的清单中。
由此引入 Git 项目的三个工作区域的概念：Git 仓库、工作目录以及暂存区域。
>staged:
Files are ready to be committed.
unstaged:
Files with changes that have not been prepared to be committed.
untracked:
Files aren't tracked by Git yet. This usually indicates a newly created file.
deleted:
File has been deleted and is waiting to be removed from Git.

![20120201121205_151](/assets/20120201121205_151.png)
Figure工作目录、暂存区域以及 Git 仓库.
每个项目都有一个 Git 目录（如果 git clone 出来的话，就是其中 .git 的目录；如果git clone --bare 的话，新建的目录本身就是 Git 目录。），它是 Git 用来保存元数据和对象数据库的地方。该目录非常重要，每次克隆镜像仓库的时候，实际拷贝的就是这个目录里面的数据。

从项目中取出某个版本的所有文件和目录，用以开始后续工作的叫做工作目录。这些文件实际上都是从 Git 目录中的压缩对象数据库中提取出来的，接下来就可以在工作目录中对这些文件进行编辑。

*所谓的暂存区域只不过是个简单的文件*，一般都放在 Git 目录中。有时候人们会把这个文件叫做*索引文件*，不过标准说法还是叫暂存区域。
>Staging Area:
A place where we can group files together before we "commit" them to Git.
Commit
A "commit" is a snapshot of our repository. This way if we ever need to look back at the changes we've made (or if someone else does), we will see a nice timeline of all changes.

基本的 Git 工作流程如下：

1. 在工作目录中修改某些文件。
2. *对修改后的文件进行快照*，然后保存到暂存区域（索引）。
3. 提交更新，将保存在暂存区域的文件快照永久转储到 Git 仓库目录中。

如果 Git 目录中保存着的特定版本文件，就属于已提交状态。 如果作了修改并已放入暂存区域，就属于已暂存状态。 如果自上次取出后，作了修改但还没有放到暂存区域，就是已修改状态。
参考：
1. http://www.open-open.com/lib/view/open1328069609436.html

### 使用github需要注意的事项
- 关于不同系统的换行符
在文本处理中, CR, LF, CR/LF是不同操作系统上使用的换行符.
Dos和windows采用回车+换行CR/LF表示下一行,
而UNIX/Linux采用换行符LF表示下一行，
苹果机(MAC OS系统)则采用回车符CR表示下一行.
CR用符号’r’表示, 十进制ASCII代码是13, 十六进制代码为0x0D;
LF使用’n’符号表示, ASCII代码是10, 十六制为0x0A.
所以Windows平台上换行在文本文件中是使用 0d 0a 两个字节表示, 而UNIX和苹果平台上换行则是使用0a或0d一个字节表示.
一般操作系统上的运行库会自动决定文本文件的换行格式. 如一个程序在windows上运行就生成CR/LF换行格式的文本文件，而在Linux上运行就生成LF格式换行的文本文件.
在一个平台上使用另一种换行符的文件文件可能会带来意想不到的问题, 特别是在编辑程序代码时. 有时候代码在编辑器中显示正常, 但在编辑时却会因为换行符问题而出错.
很多文本/代码编辑器带有换行符转换功能, 使用这个功能可以将文本文件中的换行符在不同格式单互换.
在不同平台间使用FTP软件传送文件时, 在ascii文本模式传输模式下, 一些FTP客户端程序会自动对换行格式进行转换. 经过这种传输的文件字节数可能会发生变化. 如果你不想ftp修改原文件, 可以使用bin模式(二进制模式)传输文本.

>跨平台协作开发是常有的，不统一的换行符确实对跨平台的文件交换带来了麻烦。最大的问题是，在不同平台上，换行符发生改变时，Git 会认为整个文件被修改，这就造成我们没法 diff，不能正确反映本次的修改。还好 Git 在设计时就考虑了这一点，其提供了一个 autocrlf 的配置项，用于在提交和检出时自动转换换行符，该配置有三个可选项：
true: 提交时转换为 LF，检出时转换为 CRLF
false: 提交检出均不转换
input: 提交时转换为LF，检出时不转换
用如下命令即可完成配置：
提交时转换为LF，检出时转换为CRLF
git config --global core.autocrlf true   
提交时转换为LF，检出时不转换
git config --global core.autocrlf input   
提交检出均不转换
git config --global core.autocrlf false
在 Windows 上，系统默认配置一般为 true。如果文件编码是 UTF8 并且包含中文字符，那最好还是把 autocrlf 设置为 false。否则，就会遇到我所遇到的问题，Git 尝试将 CRLF 转化为 LF 时失败，导致无法 add 。
如果把 autocrlf 设置为 false 时，那另一个配置项 safecrlf 最好设置为 ture。该选项用于检查文件是否包含混合换行符，其有三个可选项：
true: 拒绝提交包含混合换行符的文件
false: 允许提交包含混合换行符的文件
warn: 提交包含混合换行符的文件时给出警告
配置方法：
拒绝提交包含混合换行符的文件
git config --global core.safecrlf true   
允许提交包含混合换行符的文件
git config --global core.safecrlf false   
提交包含混合换行符的文件时给出警告
git config --global core.safecrlf warn

## 4.1 安装 Git

是时候动手尝试下 Git 了，不过得先安装好它。有许多种安装方式，主要分为两种，一种是通过编译源代码来安装；另一种是使用为特定平台预编译好的安装包。

### [从源代码安装](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-Git#从源代码安装)

若是条件允许，从源代码安装有很多好处，至少可以安装最新的版本。Git 的每个版本都在不断尝试改进用户体验，所以能通过源代码自己编译安装最新版本就再好不过了。有些 Linux 版本自带的安装包更新起来并不及时，所以除非你在用最新的 distro 或者 backports，那么从源代码安装其实该算是最佳选择。

Git 的工作需要调用 curl，zlib，openssl，expat，libiconv 等库的代码，所以需要先安装这些依赖工具。在有 yum 的系统上（比如 Fedora）或者有 apt-get 的系统上（比如 Debian 体系），可以用下面的命令安装：

```
$ yum install curl-devel expat-devel gettext-devel \
  openssl-devel zlib-devel

$ apt-get install libcurl4-gnutls-dev libexpat1-dev gettext \
  libz-dev libssl-dev
```

之后，从下面的 Git 官方站点下载最新版本源代码：

<code>http://git-scm.com/download</code>

然后编译并安装：

```
$ tar -zxf git-1.7.2.2.tar.gz
$ cd git-1.7.2.2
$ make prefix=/usr/local all
$ sudo make prefix=/usr/local install
```

现在已经可以用 `git` 命令了，用 `git` 把 Git 项目仓库克隆到本地，以便日后随时更新：

<code>$ git clone git://git.kernel.org/pub/scm/git/git.git</code>
### [在 Linux 上安装](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-Git#在-Linux-上安装)

如果要在 Linux 上安装预编译好的 Git 二进制安装包，可以直接用系统提供的包管理工具。在 Fedora 上用 yum 安装：

<code>$ yum install git-core</code>

在 Ubuntu 这类 Debian 体系的系统上，可以用 apt-get 安装：

<code>$ apt-get install git</code>
### [在 Mac 上安装](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-Git#在-Mac-上安装)

在 Mac 上安装 Git 有两种方式。最容易的当属使用图形化的 Git 安装工具，界面如图 1-7，下载地址在：

http://sourceforge.net/projects/git-osx-installer/

![](https://git-scm.com/figures/18333fig0107-tn.png)

图 1-7\. Git OS X 安装工具

另一种是通过 MacPorts (`http://www.macports.org`) 安装。如果已经装好了 MacPorts，用下面的命令安装 Git：

<code>$ sudo port install git-core +svn +doc +bash_completion +gitweb</code>

这种方式就不需要再自己安装依赖库了，Macports 会帮你搞定这些麻烦事。一般上面列出的安装选项已经够用，要是你想用 Git 连接 Subversion 的代码仓库，还可以加上 +svn 选项，具体将在第八章作介绍。（译注：还有一种是使用 homebrew（`https://github.com/mxcl/homebrew`）：`brew install git`。）

### [在 Windows 上安装](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%AE%89%E8%A3%85-Git#在-Windows-上安装)

在 Windows 上安装 Git 同样轻松，有个叫做 msysGit 的项目提供了安装包，可以到 GitHub 的页面上下载 exe 安装文件并运行：

<code>http://msysgit.github.com/</code>

完成安装之后，就可以使用命令行的 `git` 工具（已经自带了 ssh 客户端）了，另外还有一个图形界面的 Git 项目管理工具。

给 Windows 用户的敬告：你应该在 msysGit 提供的 Unix 风格的 shell 来运行 Git。在 Unix 风格的 shell 中，可以使用本书中提及的复杂多行的命令。对于那些需要在 Windows 命令行中使用 Git 的用户，必须注意：在参数中间有空格的时候，必须使用双引号将参数括起来（在 Linux 中是单引号）；另外，如果扬抑符（^）作为参数的结尾，并且作为这一行的最后一个字符，则这个参数也需要用双引号括起来。因为扬抑符在 Windows 命令行中表示续行（译注：即下一行为这一行命令的继续）。

## 4.2 初次运行git前的配置

一般在新的系统上，我们都需要先配置下自己的 Git 工作环境。配置工作只需一次，以后升级时还会沿用现在的配置。当然，如果需要，你随时可以用相同的命令修改已有的配置。

Git 提供了一个叫做 `git config` 的工具（译注：实际是 `git-config` 命令，只不过可以通过 `git` 加一个名字来呼叫此命令。），专门用来配置或读取相应的工作环境变量。而正是由这些环境变量，决定了 Git 在各个环节的具体工作方式和行为。这些变量可以存放在以下三个不同的地方：

*   `/etc/gitconfig` 文件：系统中对所有用户都普遍适用的配置。若使用 `git config` 时用 `--system` 选项，读写的就是这个文件。
*   `~/.gitconfig` 文件：用户目录下的配置文件只适用于该用户。若使用 `git config` 时用 `--global` 选项，读写的就是这个文件。
*   当前项目的 Git 目录中的配置文件（也就是工作目录中的 `.git/config` 文件）：这里的配置仅仅针对当前项目有效。每一个级别的配置都会覆盖上层的相同配置，所以 `.git/config` 里的配置会覆盖 `/etc/gitconfig` 中的同名变量。

在 Windows 系统上，Git 会找寻用户主目录下的 `.gitconfig` 文件。主目录即 `$HOME` 变量指定的目录，一般都是 `C:\Documents and Settings\$USER`。此外，Git 还会尝试找寻 `/etc/gitconfig` 文件，只不过看当初 Git 装在什么目录，就以此作为根目录来定位。

### [用户信息](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%88%9D%E6%AC%A1%E8%BF%90%E8%A1%8C-Git-%E5%89%8D%E7%9A%84%E9%85%8D%E7%BD%AE#用户信息)

第一个要配置的是你个人的用户名称和电子邮件地址。这两条配置很重要，每次 Git 提交时都会引用这两条信息，说明是谁提交了更新，所以会随更新内容一起被永久纳入历史记录：

    git config --global user.name "John Doe"
    git config --global user.email johndoe@example.com

如果用了 `--global` 选项，那么更改的配置文件就是位于你用户主目录下的那个，以后你所有的项目都会默认使用这里配置的用户信息。如果要在某个特定的项目中使用其他名字或者电邮，只要去掉 `--global` 选项重新配置即可，新的设定保存在当前项目的 `.git/config` 文件里。

### [文本编辑器](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%88%9D%E6%AC%A1%E8%BF%90%E8%A1%8C-Git-%E5%89%8D%E7%9A%84%E9%85%8D%E7%BD%AE#文本编辑器)

接下来要设置的是默认使用的文本编辑器。Git 需要你输入一些额外消息的时候，会自动调用一个外部文本编辑器给你用。默认会使用操作系统指定的默认编辑器，一般可能会是 Vi 或者 Vim。如果你有其他偏好，比如 Emacs 的话，可以重新设置：

<code>$ git config --global core.editor emacs</code>
### [差异分析工具](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%88%9D%E6%AC%A1%E8%BF%90%E8%A1%8C-Git-%E5%89%8D%E7%9A%84%E9%85%8D%E7%BD%AE#差异分析工具)

还有一个比较常用的是，在解决合并冲突时使用哪种差异分析工具。比如要改用 vimdiff 的话：

<code>$ git config --global merge.tool vimdiff</code>

Git 可以理解 kdiff3，tkdiff，meld，xxdiff，emerge，vimdiff，gvimdiff，ecmerge，和 opendiff 等合并工具的输出信息。当然，你也可以指定使用自己开发的工具，具体怎么做可以参阅第七章。

### [查看配置信息](https://git-scm.com/book/zh/v2/%E8%B5%B7%E6%AD%A5-%E5%88%9D%E6%AC%A1%E8%BF%90%E8%A1%8C-Git-%E5%89%8D%E7%9A%84%E9%85%8D%E7%BD%AE#查看配置信息)

要检查已有的配置信息，可以使用 `git config --list` 命令：

<code>$ git config --list
user.name=Scott Chacon
user.email=schacon@gmail.com
color.status=auto
color.branch=auto
color.interactive=auto
color.diff=auto
...</code>

有时候会看到重复的变量名，那就说明它们来自不同的配置文件（比如 `/etc/gitconfig` 和 `~/.gitconfig`），不过最终 Git 实际采用的是最后一个。

也可以直接查阅某个环境变量的设定，只要把特定的名字跟在后面即可，像这样：

<code>$ git config user.name
Scott Chacon</code>

### 快速打开git config

现有快速打开git config的方法，直接使用--edit 选项
使用方法：

`git config [--global] --edit`

### 获取帮助
想了解 Git 的各式工具该怎么用，可以阅读它们的使用帮助，方法有三：
```
$ git help <verb>
$ git <verb> --help
$ man git-<verb>
```
比如，要学习 config 命令可以怎么用，运行：
```
$ git help config
```

## 4.3 新建本地数据仓库

### 新建本地数据仓库

接下来要在本地新建数据库，创建一个名称为「gittest」的空目录，并把它放在Git管理之下。
首先在任意一个地方创建gittest目录。然后使用init命令为该目录创建本地Git数据仓库。

```
C:\Users\LiME>mkdir gittest

C:\Users\LiME>cd gittest

C:\Users\LiME\gittest>git init
Initialized empty Git repository in C:/Users/LiME/gittest/.git/

C:\Users\LiME\gittest>cd . > a.txt

C:\Users\LiME\gittest>echo hello > a.txt

C:\Users\LiME\gittest>type a.txt
hello

C:\Users\LiME\gittest>git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)

        a.txt

nothing added to commit but untracked files present (use "git add" to track)
C:\Users\LiME\gittest>git add a.txt

C:\Users\LiME\gittest>git status
On branch master

No commits yet

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

        new file:   a.txt


C:\Users\LiME\gittest>git commit -m "first commit"
[master (root-commit) d0f5994] first commit
 1 file changed, 1 insertion(+)
 create mode 100644 a.txt

C:\Users\LiME\gittest>git status
On branch master
nothing to commit, working tree clean

C:\Users\LiME\gittest>git log
commit d0f59941460ec7d4cc13099609d1f22359fc2c53 (HEAD -> master)
Author: Phillins Lime <lime31415@gmail.com>
Date:   Sat Nov 4 00:19:33 2017 +0800

    first commit

```

- 将当前路径的目录初始化为本地仓库
  `git init`

- 使用status命令确认工作树和索引的状态。

  `git status`

- 将文件加入到索引，要使用add命令。在<file>指定加入索引的文件。用空格分割可以指定多个文件。

  `git add <file>..`
- 指定参数「.」，可以把所有的文件加入到索引。

  `git add .`
  >add all:
You can also type `git add -A .` where the dot stands for the current directory, so everything in and beneath it is added. The -A ensures even deleted files are included(如果是--ignore--removal，则工作区删除的文件不会从仓库中删除).
git reset:
You can use git reset <filename> to remove a file or files from the staging area.

![KwOLu](/assets/KwOLu.jpg)
- 使用通配符（ wildcards），可以把与通配符相匹配的文件添加到索引，这里通配符需用引号引用
  `$ git add '通配符'`
  例如：`git add '*.txt'`将所有txt文件添加到索引
  >Wildcards:
We need quotes so that Git will receive the wildcard before our shell can interfere with it. Without quotes our shell will only execute the wildcard search within the current directory. Git will receive the list of files the shell found instead of the wildcard and it will not be able to add the files inside of the subdirectory.
不适用引号的话，通配符首先被shell调用搜索，git接受到的仅仅是当前目录下与通配符匹配的文件，子目录的文件不会被添加。

- 加入到索引后，我们就可以提交文件了。请执行如下显示的commit命令。

  `$ git commit -m "提交的描述信息"`
  如果我们这里不用-m参数的话，git将调到一个文本编译器（通常是vim）来让你输入提交的描述信息。
  可能一天下来，你对工作树中的许多文档都进行了更新（文档添加、修改、删除），但是我忘记了它们的名字，此时若将所做的全部更新添加到索引中，比较轻省的做法就是：
  `git commit -a -m "提交的描述信息"`
  git commit 命令的-a 选项可只将所有被修改或者已删除的且已经被git管理的文档提交到仓库中。如果只是修改或者删除了已被Git 管理的文档，是没必要使用git add 命令的。
  `git add .`命令除了能够判断出当前目录（包括其子目录）所有被修改或者已删除的文档，还能判断用户所添加的新文档，并将其信息追加到索引中。
  `git commit --amend` 对于已经修改提交过的注释，如果需要修改，可以借助 git commit --amend 来进行。
  例如 在gittest 里最新的提交就是 first commit，我现在需要将其改为 resolving the roaming problem for fixing bug 7732
  在 gittest 下 输入 git commit --amend,就会进入一个文本编辑界面（退出方式与Linux的vim相似输入`:wq`），在注释的地方修改 ，保存然后退出，这样注释就修改了，再重新push.
  另外，要注意的问题是，Git 不会主动记录你对文档进行的更新，除非你对它发号施令（比如通过git add命令）
- 使用log命令，我们可以在数据库的提交记录看到新的提交。
  `$ git log`
  >Use `git log --summary` to see more information for each commit. You can see where new files were added for the first time or where files were deleted. It's a good overview of what's going on in the project.

`$ gitk`
>安装git的同时会安装名为gitk的工具(集成diff可视化)。在仓库目录使用这个工具，可以在GUI下确认提交记录。

### 快速clone GitHub中的工程
`git clone [--depth=14] https://xxxx/xxx.git [<directory>]`

常用的也就是 git clone + 远程数据库的URL。但是其中有个选项 --depth

其中的 --depth=14 选项，告诉gitHub 仅仅pull down 最近的14条commits
这样你的download又快又小。
缺点就是没有全部的commit信息，但已足够！！

### 删除本地数据仓库
直接删除本地仓库目录下的`.git`文件夹，这样这个仓库从本地删除但文件仍然保留在电脑中

## 4.4 设置GitHub的SSH key
>git for windows已经集成了ssh客户端

使用SSH可以快速验证，从而无需每次验证用户名密码
其原理是RSA加密的签名认证
同样有一个私钥(id_rsa)和公钥(id_rsa.pub)
### 检查本机SSH key设置
`cd ~/.ssh`Windows中用用户文件夹路径代替~
如果现实没有该路径表明尚未创立过ssh key
### 备份和删除原来的ssh key
如果该路径存在，可以备份原来的key,也就是备份id_rsa和id_rsa.pub
此文件夹下还有一个know_hosts文件，记录访问过的服务器的公钥，如果前后访问的公钥不一致则会发出警告，这个文件也可以备份。
### 生成新的SSH key
输入 `ssh-keygen -t rsa -C "your_email address"`
执行这条命令会提示文件保存路径，可以直接按Enter
然后提示输入 passphrase（密码），输入两次（可以不输直接两次Enter）
这样会在用户目录下的`.ssh`文件夹下生成id_rsa和id_rsa.pub两个文件
打开GitHub账户设置中的SSH，选择添加新SSH key，将id_rsa.pub（公钥）中的内容复制粘贴进去就可以了
测试 ssh 链接 github：
输入 `ssh -T git@github.com`提示successfully就表示设置好了
参考：https://www.ezlippi.com/blog/2015/03/github-pages-blog.html
为了使用git命令行形式，还需要将私钥添加到git for windows 附带的ssh-agent中，打开`git bash`进行以下进行以下操作：
    LiME@LIME-SurfacePro MINGW64 ~
    $ eval $(ssh-agent -s)
    Agent pid 10020

    LiME@LIME-SurfacePro MINGW64 ~
    $ ssh-add .ssh/id_rsa
    Identity added: .ssh/id_rsa (.ssh/id_rsa)

    LiME@LIME-SurfacePro MINGW64 ~
    $ ssh-add -l
    2048 SHA256:BiggwYq0nIhGZ71cP8aNn2l/QCweb8qe8GYapNnIW0U .ssh/id_rsa (RSA)

    LiME@LIME-SurfacePro MINGW64 ~
    $ ssh-add -l -E md5
    2048 MD5:62:cf:8f:0d:06:8a:d6:61:12:c1:49:c0:fc:26:90:5a .ssh/id_rsa (RSA)

后面两个命令给出了公钥的SHA256和MD5值，可以与GitHub上的对比是否一致。
参考：
1. https://help.github.com/articles/connecting-to-github-with-ssh/
2. https://help.github.com/articles/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent/
3. https://help.github.com/articles/reviewing-your-ssh-keys/

## 4.5 将本地仓库push到github远程仓库
### 在GitHub上新建一个新仓库，GitHub上的公共仓库都是免费的
这部分很简单，常见GitHub
### 给当前项目的本地仓库增加GitHub远程仓库
假设在GitHub创建了一个新的空的GitHub仓库（https://github.com/try-git/try_git.git）。 为了把我们的本地仓库推到GitHub服务器上，我们需要添加一个远程仓库。
`git remote add origin https://github.com/try-git/try_git.git`
This command takes a remote name and a repository URL, which in this case is  https://github.com/try-git/try_git.git.
这里有两个参数，第一个指定一个名字给添加的远程仓库，第二个指定远程仓库的URL，一般惯例主仓库用名origin
>git remote:
Git doesn't care what you name your remotes, but it's typical to name your main one origin.
执行推送或者拉取的时候，如果省略了远程数据库的名称，则默认使用名为”origin“的远程数据库。因此一般都会把远程数据库命名为origin。

### 将本地分支push到远程仓库
    git push -u origin master
命令push告诉git提交到什么地方，当我们完成工作时将我们本地的修改 push 到 origin repo （on GitHub）
>repo是repository仓库的缩写
Directory:
A folder used for storing multiple files.
Repository:
A directory where Git has been initialized to start version controlling your files.
The .git directory:
It's usually hidden.
If you click it you'll notice it has all sorts of directories and files inside it. You'll rarely ever need to do anything inside here but it's the guts of Git, where all the magic happens.


我们远程仓库的名字是origin，默认本地分支的名字是master。参数`-u`告诉git记住以上参数，这样下次直接使用`git push`不用再加上参数。但是，首次运行指令向空的远程数据库推送时，必须指定远程数据库名称和分支名称。
这样本地的master分支将track origin仓库的master分支。
push到GitHub时，有两种方式https和ssh，使用https需要输入GitHub的账号密码。

## 4.6 从远程仓库pull
###将远程分支pull到本地仓库
当远程仓库的master分支有了变化，我们需要把这些变化pull到我们的本地仓库中
    git pull origin master
这时远程仓库的新修改会覆盖我们本地工作区的内容，但是不用担心，了解git原理的话，就会知道，只要我们pull前先将我们的修改commit到本地仓库，这些内容就不会丢失。

## 4.7 使用diff查看文件变化
`git-diff` 比较的是工作目录（working tree）和暂存区域快照（index）之间的差异，也就是修改后还没有暂存起来的内容
`git diff HEAD`
比较工作目录（working tree）和本地仓库（local repository）上次提交（commit）的快照的区别
>The HEAD is a pointer that holds your position within all your different commits. By default HEAD points to your most recent commit, so it can be used as a quick way to reference that commit without having to look up the SHA.

`git diff --staged`
比较的是暂存文件（staged）和上次提交的快照的区别
>Another great use for diff is looking at changes within files that have already been staged. Remember, staged files are files we have told git that are ready to be committed.

参考：[如何读懂diff结果](chapter4\how-to-read-diff-results.md)

## 4.8 恢复、撤销、删除
### 从暂存区（stage）中撤销
`git reset <path>...`
将文件从暂存区中移除

### 从仓库中恢复文件
`git checkout -- [<path>...]`
从仓库中恢复文件
>-- 是必需的，否则若分支与文件同名，恢复出来的是分支而不是文件

### 从仓库中删除文件
如果仅仅删除暂存区中的文件
`git rm --cached <path>...`
从工作区和暂存区中都删除文件
`git rm <path>...`
这样做之后文件还是在仓库中可以checkout恢复
>If you want to remove an entire folder, You can use the recursive option on git rm:
git rm -r folder
This will recursively remove all folders and files from the given directory.

但使用`git commit`后将彻底从仓库中删除文件
>If you happen to delete a file without using 'git rm' you'll find that you still have to 'git rm' the deleted files from the working tree. You can save this step by using the '-a' option on 'git commit', which auto removes deleted files with the commit.
git commit -am "Delete stuff"

## 4.9 创建分支
当开发者开发某项新功能或者解决某个bug时，他们经常创建一个copy（aka.分支branch）(aka.also known as)，这样就能单独提交。但他们完成时，他们可以将自己的分支与master分支合并

![capture_stepup1_1_2](/assets/capture_stepup1_1_2.png)

### 分支的运用

在Git您可以自由地建立分支。但是，要先确定运用规则才可以有效地利用分支。

这里我们会介绍两种分支 (“Merge分支”和 “Topic分支” ) 的运用规则。

- Merge分支
Merge分支是为了可以随时发布release而创建的分支，它还能作为Topic分支的源分支使用。保持分支稳定的状态是很重要的。如果要进行更改，通常先创建Topic分支，而针对该分支，可以使用Jenkins之类的CI工具进行自动化编译以及测试。
通常，大家会将master分支当作Merge分支使用。

- Topic分支
Topic分支是为了开发新功能或修复Bug等任务而建立的分支。若要同时进行多个的任务，请创建多个的Topic分支。
Topic分支是从稳定的Merge分支创建的。完成作业后，要把Topic分支合并回Merge分支。

![capture_stepup1_2_1](/assets/capture_stepup1_2_1.png)

### 创建当前项目的分支
`git branch <branch name>`
>Branches are what naturally happens when you want to work on multiple features at the same time. Rather you'd separate the code base into two "snapshots" (branches) and work on and commit to them separately. As soon as one was ready, you might merge this branch back into the master branch and push it to the remote server.

### 在分支间切换
`git branch`,可以看到当前仓库中的所有分支,前面有*的就是现在的分支。
使用`git checkout <branch name>`可以切换到该分支
>All at Once
You can use:
git checkout -b new_branch
to checkout and create a branch at the same time. This is the same thing as doing:
git branch new_branch
git checkout new_branch
若要切换作业的分支，就要进行checkout操作。进行checkout时，git会从工作树还原向目标分支提交的修改内容。checkout之后的提交记录将被追加到目标分支。

HEAD指向的是现在使用中的分支的最后一次更新。通常默认指向master分支的最后一次更新。通过移动HEAD，就可以变更使用的分支。

提交时使用`~`(tilde)和`^`(caret)就可以指定某个提交的相对位置。最常用的就是相对于HEAD的位置。HEAD后面加上`~`(tilde）可以指定HEAD之前的提交记录。合并分支会有多个根节点，您可以用`^`(caret) 来指定使用哪个为根节点。

![capture_stepup1_3_2](/assets/capture_stepup1_3_2.png)

>git stash:
Sometimes when you go to pull you may have changes you don't want to commit just yet. One option you have, other than commiting, is to stash the changes.
Use the command `git stash` to stash your changes, and `git stash apply` to re-apply your changes after your pull.

还未提交的修改内容以及新添加的文件，留在索引区域或工作树的情况下切换到其他的分支时，修改内容会从原来的分支移动到目标分支。但是如果在checkout的目标分支中相同的文件也有修改，checkout会失败的。这时要么先提交修改内容，要么用stash暂时保存修改内容后再checkout。
stash是临时保存文件修改内容的区域。stash可以暂时保存工作树和索引里还没提交的修改内容，您可以事后再取出暂存的修改，应用到原先的分支或其他的分支上。
## 4.10 合并分支
>Pull Requests
If you're hosting your repo on GitHub, you can do something called a pull request.
A pull request allows the boss of the project to look through your changes and make comments before deciding to merge in the change. It's a really great feature that is used all the time for remote workers and open-source projects.

首先转到master分支
`git checkout master`
使用命令`git merge <branch name>`来合并分支
>Merge Conflicts can occur when changes are made to a file at the same time. A lot of people get really scared when a conflict happens, but fear not! They aren't that scary, you just need to decide which code to keep.

修改完成topic分支后要合并回merge分支。合并分支有2种方法：使用merge或rebase。使用这2种方法，合并后分支的历史记录会有很大的差别。

- merge

使用merge可以合并多个历史记录的流程。

如下图所示，bugfix分支是从master分支分叉出来的。
![capture_stepup1_4_1](/assets/capture_stepup1_4_1.png)

合并 bugfix分支到master分支时，如果master分支的状态没有被更改过，那么这个合并是非常简单的。 bugfix分支的历史记录包含master分支所有的历史记录，所以通过把master分支的位置移动到bugfix的最新分支上，Git 就会合并。这样的合并被称为fast-forward（快进）合并。

![capture_stepup1_4_2](/assets/capture_stepup1_4_2.png)

但是，master分支的历史记录有可能在bugfix分支分叉出去后有新的更新。这种情况下，要把master分支的修改内容和bugfix分支的修改内容汇合起来。

![capture_stepup1_4_3](/assets/capture_stepup1_4_3.png)

因此，合并两个修改会生成一个提交。这时，master分支的HEAD会移动到该提交上。

![capture_stepup1_4_4](/assets/capture_stepup1_4_4.png)

>Note
执行合并时，如果设定了non fast-forward选项，即使在能够fast-forward合并的情况下也会生成新的提交并合并。
![capture_stepup1_4_5](/assets/capture_stepup1_4_5.png)
执行non fast-forward后，分支会维持原状。那么要查明在这个分支里的操作就很容易了。

- rebase

跟merge的例子一样，如下图所示，bugfix分支是从master分支分叉出来的。

![capture_stepup1_4_6](/assets/capture_stepup1_4_6.png)

如果使用rebase方法进行分支合并，会出现下图所显示的历史记录。现在我们来简单地讲解一下合并的流程吧。

![capture_stepup1_4_7](/assets/capture_stepup1_4_7.png)
首先，rebase bugfix分支到master分支, bugfix分支的历史记录会添加在master分支的后面。如图所示，历史记录成一条线，相当整洁。

这时移动提交X和Y有可能会发生冲突，所以需要修改各自的提交时发生冲突的部分。

![capture_stepup1_4_8](/assets/capture_stepup1_4_8.png)

rebase之后，master的HEAD位置不变。因此，要合并master分支和bugfix分支，即是将master的HEAD移动到bugfix的HEAD这里。

![capture_stepup1_4_9](/assets/capture_stepup1_4_9.png)

>Note
Merge和rebase都是合并历史记录，但是各自的特征不同。
merge
保持修改内容的历史记录，但是历史记录会很复杂。
rebase
历史记录简单，是在原有提交的基础上将差异内容反映进去。
因此，可能导致原本的提交内容无法正常运行。
您可以根据开发团队的需要分别使用merge和rebase。
例如，想简化历史记录:
>- 在topic分支中更新merge分支的最新代码，请使用rebase。
>- 向merge分支导入topic分支的话，先使用rebase，再使用merge。




### 4.11 删除分支
`git branch -d <branch name>`

强制删除分支`git branch -D <branch name>`
>Force delete
What if you have been working on a feature branch and you decide you really don't want this feature anymore? You might decide to delete the branch since you're scrapping the idea. You'll notice that git branch -d bad_feature doesn't work. This is because -d won't let you delete something that hasn't been merged.
You can either add the --force (-f) option or use -D which combines -d -f together into one command.

合并到master分支后，提交到远程仓库
`git push`

## 4.12 解决冲突
在执行pull之后，进行下一次push之前，如果其他人进行了推送内容到远程数据库的话，那么你的push将被拒绝。这种情况下，在读取别人push的变更并进行合并操作之前，你的push都将被拒绝。这是因为，如果不进行合并就试图覆盖已有的变更记录的话，其他人push的变更就会丢失。
>合并的时候，Git会自动合并已有的变更点！不过，也存在不能自动合并的情况。如果远程数据库和本地数据库的同一个地方都发生了修改的情况下，因为无法自动判断要选用哪一个修改，所以就会发生冲突。
![capture_intro5_1_3](/assets/capture_intro5_1_3.png)
==分割线上方是本地数据库的内容,
下方是远程数据库的编辑内容。


现在，我们将要学习怎样解决冲突。
首先，我们用同一个分支的两个本地仓库“tutorial”和“tutorial2”制造一个冲突状态。

首先，打开tutorial目录的sample.txt文档，添加以下黑体字之后进行提交。
```
连猴子都懂的Git命令
add 把变更录入到索引中
commit 记录索引的状态
$ git add sample.txt
$ git commit -m "添加commit的说明"
[master 95f15c9] 添加commit的说明
 1 files changed, 1 insertions(+), 0 deletions(-)
```

接下来，打开tutorial2目录的sample.txt文档，添加以下黑体字之后进行提交。
```
连猴子都懂的Git命令
add 把变更录入到索引中
pull 取得远端数据库的内容
$ git add sample.txt
$ git commit -m "添加pull的说明"
[master 4c01823] 添加pull的说明
 1 files changed, 1 insertions(+), 0 deletions(-)
```
现在从tutorial2 推送内容到远程数据库。
```
$ git push
Username: <用户名>
Password: <密码>
Counting objects: 5, done.
Delta compression using up to 4 threads.
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 391 bytes, done.
Total 3 (delta 0), reused 0 (delta 0)
To https://nulab.backlog.jp/git/BLG/tutorial.git
   3da09c1..4c01823  master -> master
```
在目前的远程数据库，"sample.txt"文档已包含第三行内容「pull 取得远端数据库的内容」，并且已被存储到历史记录中啦。

现在从tutorial推送内容到远程数据库吧。
```
$ git push
Username: <用户名>
Password: <密码>
To https://nulab.backlog.jp/git/BLG/tutorial.git
 ! [rejected]        master -> master (non-fast-forward)
error: failed to push some refs to 'https://nulab.backlog.jp/git/BLG/tutorial.git'
To prevent you from losing history, non-fast-forward updates were rejected
Merge the remote changes (e.g. 'git pull') before pushing again.  See the
'Note about fast-forwards' section of 'git push --help' for details.
```
由于远程仓库的内容在tutorial一次pull、push之间已经发生修改，在合并修改时发生了冲突，推送被拒绝（rejected）了。
解决冲突

**为了把变更内容推送到远程数据库，我们必须手动解决冲突。首先运行pull，以从远程数据库取得最新的变更记录。**
```
$ git pull origin master
Username: <用户名>
Password: <密码>
remote: Counting objects: 5, done.
remote: Compressing objects: 100% (2/2), done.
remote: Total 3 (delta 0), reused 0 (delta 0)
Unpacking objects: 100% (3/3), done.
From https://nulab.backlog.jp/git/BLG/tutorial
 * branch            master     -> FETCH_HEAD
Auto-merging sample.txt
CONFLICT (content): Merge conflict in sample.txt
Automatic merge failed; fix conflicts and then commit the result.
```
显示合并时发生冲突的讯息。
讯息显示「Merge conflict in sample.txt」。打开sample.txt文件，我们看到Git已添加标示以显示冲突部分。为Git无法完成主动合并的部分做手动的修改。
```
连猴子都懂的Git命令
add 把变更录入到索引中
<<<<<<< HEAD
commit 记录索引的状态
=======
pull 取得远端数据库的内容
>>>>>>> 4c0182374230cd6eaa93b30049ef2386264fe12a
```

进行修改
```
连猴子都懂的Git命令
add 把变更录入到索引中
commit 记录索引的状态
pull 取得远端数据库的内容
```
文件的内容发生了修改，所以需要进行提交。
```
$ git add sample.txt
$ git commit -m "合并"
[master d845b81] 合并
```
这样就完成了从远程数据库导入最新的修改内容。

我们可以用log命令来确认数据库的历史记录是否准确。指定--graph选项，能以文本形式显示更新记录的流程图。指定--oneline选项，能在一行中显示提交的信息。
```
$ git log --graph --oneline
*   d845b81 合并
|\
| * 4c01823 添加pull的说明
* | 95f15c9 添加commit的说明
|/
* 3da09c1 添加add的说明
* ac56e47 first commit
```
这表明两个修改记录已经整合了。

现在可以push到远程仓库了

## 4.13 应用分支开发软件流程
topic分支和merge分支的运用实例我们用简单的实例来讲解topic分支和merge分支的操作方法。

例如，在开发功能的topic分支操作途中，需要修改bug。

![capture_stepup1_5_1](/assets/capture_stepup1_5_1.png)

这时，merge分支还是处于开发功能之前的状态。在这里新建修改错误用的主题分支，就可以从开发功能的作业独立出来，以便开始新的工作。

![capture_stepup1_5_2](/assets/capture_stepup1_5_2.png)

完成bug修正的工作后，把分支导入到原本的merge分支后就可以公开了。

导入到原本的合并分支後就可以公开
![capture_stepup1_5_3](/assets/capture_stepup1_5_3.png)
回到原本的分支继续进行开发功能的操作
![capture_stepup1_5_4](/assets/capture_stepup1_5_4.png)
但是，如果要继续进行操作，你会发现需要之前修正bug时提交X的内容。有2种导入提交X的内容的方法：一种是直接merge，另一种是和rebase导入提交X的合并分支。

这里我们使用rebase合并分支的方法。

![capture_stepup1_5_5](/assets/capture_stepup1_5_5_15j48jfes.png)

在导入提交X的内容的状态下继续进行开发功能。

这样，有效地利用分支的话就可以同时进行不同的作业了。
>专栏「A successful Git branching model」
>
>作为Git的分支的用例 ，这里介绍 A successful Git branching model
>
>原文:
>http://nvie.com/posts/a-successful-git-branching-model/

这个用例主要分为

主分支
特性分支
release分支
hotFix分支
分别使用4个种类的分支来进行开发的。

![capture_stepup1_5_6](/assets/capture_stepup1_5_6.png)

主分支
主分支有两种：master分支和develop分支

master
master分支只负责管理发布的状态。在提交时使用标签记录发布版本号。
develop
develop分支是针对发布的日常开发分支。刚才我们已经讲解过有合并分支的功用。
特性分支
特性分支就是我们在前面讲解过的topic分支的功用。

这个分支是针对新功能的开发，在bug修正的时候从develop分支分叉出来的。基本上不需要共享特性分支的操作，所以不需要远端控制。完成开发后，把分支合并回develop分支后发布。

release分支
release分支是为release做准备的。通常会在分支名称的最前面加上release-。release前需要在这个分支进行最后的调整，而且为了下一版release开发用develop分支的上游分支。

一般的开发是在develop分支上进行的，到了可以发布的状态时再创建release分支，为release做最后的bug修正。

到了可以release的状态时，把release分支合并到master分支，并且在合并提交里添加release版本号的标签。

要导入在release分支所作的修改，也要合并回develop分支。

hotFix分支
hotFix分支是在发布的产品需要紧急修正时，从master分支创建的分支。通常会在分支名称的最前面加上 hotfix-。

例如，在develop分支上的开发还不完整时，需要紧急修改。这个时候在develop分支创建可以发布的版本要花许多的时间，所以最好选择从master分支直接创建分支进行修改，然后合并分支。

修改时创建的hotFix分支要合并回develop分支。
