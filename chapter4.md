# 第四章： 使用git

---

[TOC]

- 网站资源：
  - [猴子都能懂的GIT入门](https://backlog.com/git-tutorial/cn/)
  - [《git权威指南》](http://www.worldhello.net/gotgit/)以及[gotgithub](http://www.worldhello.net/gotgithub/)
  - 两个国外的网站：<http://gitready.com/>、 <https://git.wiki.kernel.org/index.php/Git_FAQ>
## 4.0 git简介

### 图解git
- git基本概念
![git基本概念](/assets/git基本概念.png)
- git命令
![git命令](http://img.blog.csdn.net/20161202183909310 "git命令")

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

<code>\$ git config --global user.name "John Doe"
\$ git config --global user.email johndoe@example.com</code>

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

C:\Users\LiME\gittest>cd > a.txt

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


- 使用status命令确认工作树和索引的状态。

  `$ git status`

- 将文件加入到索引，要使用add命令。在<file>指定加入索引的文件。用空格分割可以指定多个文件。

  `$ git add <file>..`
- 指定参数「.」，可以把所有的文件加入到索引。

  `$ git add .`
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
*>安装git的同时会安装名为gitk的工具(集成diff可视化)。在仓库目录使用这个工具，可以在GUI下确认提交记录。
`$ gitk`*

### 快速clone GitHub中的工程

`git clone [--depth=14] https://xxxx/xxx.git`

常用的也就是 git clone + 路径。但是其中有个选项 --depth

其中的 --depth=14 选项，告诉gitHub 仅仅pull down 最近的14条commits
这样你的download又快又小。
缺点就是没有全部的commit信息，但已足够！！

### 删除本地数据仓库
直接删除本地仓库目录下的`.git`文件夹，这样这个仓库从本地删除但文件仍然保留在电脑中

## 4.4 设置GitHub的SSH key
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
