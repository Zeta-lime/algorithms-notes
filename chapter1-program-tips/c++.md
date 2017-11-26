# 常用的编程TIPS(C++)
--- 
[toc]
## 编译调试知识

### 链接

由汇编程序生成的目标文件并不能立即就被执行，其中可能还有许多没有解决的问题。
例如，某个源文件中的函数可能引用了另一个源文件中定义的某个符号（如变量或者函数调用等）；
在程序中可能调用了某个库文件中的函数，等等。所有的这些问题，都需要经链接程序的处理方能得以解决。

链接程序的主要工作就是将有关的目标文件彼此相连接，也即将在一个文件中引用的符号同该符号在另外一个文件中的定义连接起来，使得所有的这些目标文件成为一个能够诶操作系统装入执行的统一整体。

根据开发人员指定的同库函数的链接方式的不同，链接处理可分为两种：

（1）静态链接 
在这种链接方式下，函数的代码将从其所在地静态链接库中被拷贝到最终的可执行程序中。这样该程序在被执行时这些代码将被装入到该进程的虚拟地址空间中。静态链接库实际上是一个目标文件的集合，其中的每个文件含有库中的一个或者一组相关函数的代码。 
>调用函数的目标文件从静态库被拷贝到源程序的目标代码中，程序运行时不需要静态库和链接程序。

（2）动态链接
在此种方式下，函数的代码被放到称作是动态链接库或共享对象的某个目标文件中。链接程序此时所作的只是在最终的可执行程序中记录下共享对象的名字以及其它少量的登记信息。在此可执行文件被执行时，动态链接库的全部内容将被映射到运行时相应进程的虚地址空间。动态链接程序将根据可执行程序中记录的信息找到相应的函数代码。
>链接时只是将相应函数的信息放入源程序的目标代码中，程序运行时进行链接，需要动态库和链接程序。

对于可执行文件中外部函数的调用，可分别采用动态链接或静态链接的方法。使用动态链接能够使最终的可执行文件比较短小，并且当共享对象被多个进程使用时能节约一些内存，因为在内存中只需要保存一份此共享对象的代码。但并不是使用动态链接就一定比使用静态链接要优越。在某些情况下动态链接可能带来一些性能上损害。

### 调试
GCC把C语言源文件（＇.c＇）编译成汇编语言文件（＇.s＇）；
汇编器把汇编语言文件翻译成目标文件（＇.o＇）；
最后由链接器链接所有的目标文件和有关的库生成可执行文件（＇a.out＇）。

如打开＇-g＇选项，GCC编译＇.c＇文件时，把附加的调试信息插进＇.s＇文件，这些调试信息经汇编器和链接器稍加转换一直传到可执行文件中。这些调试信息包括行号、变量的类型和作用域、函数名字、函数参数和函数的作用域等源文件的特性。

## 全局变量、局部变量、静态全局变量、静态局部变量的区别

C++变量根据定义的位置的不同的**生命周期**，具有不同的**作用域**，作用域可分为6种：**全局作用域，局部作用域，语句作用域，类作用域，命名空间作用域和文件作用域。**

- 从**作用域**看：

    **全局变量具有全局作用域**。全局变量(在函数外声明的变量)只需在一个源文件中定义，就可以作用于所有的源文件。当然，其他不包含全局变量定义的源文件需要用extern关键字再次声明这个全局变量。

    **静态局部变量具有局部作用域**，它只被初始化一次，自从第一次被初始化直到程序运行结束都**一直存在**，它和全局变量的区别在于全局变量对所有的函数都是可见的，而静态局部变量只对定义自己的函数体始终可见。

    **局部变量也只有局部作用域**，它是自动对象（auto），它在程序运行期间不是一直存在，而是只在函数执行期间存在，函数的一次调用执行结束后，变量被撤销，其所占用的内存也被**收回**。

    **静态全局变量**也具有全局作用域，它与全局变量的区别在于如果程序包含多个文件的话，**它作用于定义它的文件里，不能作用到其它文件里**，即被static关键字修饰过的变量具有**文件作用域**。这样即使两个不同的源文件都定义了相同名字的静态全局变量，它们也是不同的变量。


- 从**分配内存空间**看：

    全局变量，静态局部变量，静态全局变量都在静态存储区分配空间，而**局部变量在栈里分配空间**

**全局变量本身就是静态存储方式**， 静态全局变量当然也是静态存储方式。这两者在存储方式上并无不同。这两者的区别虽在于**非静态全局变量的作用域是整个源程序，当一个源程序由多个源文件组成时，非静态的全局变量在各个源文件中都是有效的**。 而静态全局变量则限制了其作用域， 即只在定义该变量的源文件内有效，在同一源程序的其它源文件中不能使用它。由于静态全局变量的作用域局限于一个源文件内，只能为该源文件内的函数公用，因此可以避免在其它源文件中引起错误。

1)、静态变量会被放在程序的静态数据存储区（数据段）(全局可见)中，这样可以在下一次调用的时候还可以保持原来的赋值。这一点是它与堆栈变量(局部变量)和堆变量（用户自行分配内存的变量）的区别。
2)、变量用static告知编译器，自己仅仅在变量的作用范围内可见。这一点是它与全局变量的区别。

从以上分析可以看出， 把局部变量改变为静态变量后是改变了它的存储方式即改变了它的生存期。把全局变量改变为静态变量后是改变了它的作用域，限制了它的使用范围。因此static 这个说明符在不同的地方所起的作用是不同的。应予以注意。

Tips:
a. 若全局变量仅在单个c文件中访问，则可以将这个变量修改为静态全局变量，以降低模块间的耦合度；
b. 若全局变量仅由单个函数访问，则可以将这个变量改为该函数的静态局部变量，以降低模块间的耦合度；
c. 设计和使用访问动态全局变量、静态全局变量、静态局部变量的函数时，需要考虑重入问题，因为他们都放在静态数据存储区，全局可见；
d. 如果我们需要一个可重入的函数，那么，我们一定要避免函数中使用static变量(这样的函数被称为：带“内部存储器”功能的的函数)
e. 函数中必须要使用static变量情况:比如当某函数的返回值为指针类型时，则必须是static的局部变量的地址作为返回值，若为auto类型，则返回为错指针。


static 全局变量: 改变作用范围，不改变存储位置

static 局部变量：改变存储位置，不改变作用范围

静态函数 ：在函数的返回类型前加上static关键字,函数即被定义为静态函数。静态函数与普通函数不同，它只能在声明它的文件当中可见，不能被其它文件使用。

如果在一个源文件中定义的函数，只能被本文件中的函数调用，而不能被同一程序其它文件中的函数调用，这种函数也称为内部函数。定义一个内部函数，只需在函数类型前再加一个“static”关键字即可。

## 输入输出
### c风格
printf()\scanf()\getchar()\putchar() //#include <cstdio>
### c++风格
cin()\cout\get()(输入一行时，换行符留在输入缓存)\getline()(输入一行，丢弃输入缓存中的换行符，以空字符代替)
### 输入输出状态标识符
//#include<iostream>
cin.clear（）是用来更改cin的状态标示符的。
cin.sync（）是用来清除缓存区的数据流的。
如果标示符没有改变那么即使清除了数据流也无法输入。所以两个要联合起来使用。
>在vs2015上使用失败，在g++使用成功，依赖编译器实现。

稳妥点用
cin.clear();
cin.ignore(std::numeric_limits<std::streampos>::max(), '\n'); //#include <climits>
>c风格清除读写缓存
int fflush(FILE *stream) //include <cstdio>

### 输出格式化

```c++
#include <iostream>
#include <iomanip>
#include <bitset>
using std::bitset;
using std::hex;
using std::oct;
using std::cout;
using std::cin;
using std::endl;
int main()
{
 int a=10; 
 cout<<"Dec:"<<a<<endl; 
 cout<<hex<<"Hex:"<<a<<endl;
 cout<<oct<<"Oct:"<<a<<endl;
 cout<<bitset<32>(a)<<endl;
 getchar();
 return 0;
}
```

```c++
注：下面的scientific 和 fixed不能同时使用
double a=123.456789012345;对a赋初值
(1) cout<<a;输出： 123.456  
(2) cout<<setprecision(9)<<a;输出： 123.456789  
(3) cout<<setprecision(6);恢复默认格式(精度为6)
(4) cout<< setiosflags(ios∷fixed);输出： 123.456789
(5) cout<<setiosflags(ios∷fixed)<<setprecision(8)<<a;输出： 123.45678901
(6) cout<<setiosflags(ios∷scientific)<<a;输出： 1.234568e+02
(7) cout<<setiosflags(ios∷scientific)<<setprecision(4)<<a; 输出： 1.2346e02
下面是整数输出的例子： 
int b=123456;对b赋初值
(1) cout<<b;输出： 123456
(2) cout<<hex<<b; 输出： 1e240     
(3) cout<<setiosflags(ios∷uppercase)<<b;输出： 1E240     
(4) cout<<setw(10)<<b<<′,′<<b; 输出：     123456，123456
(5) cout<<setfill(′*′)<<setw(10)<<b;输出： **** 123456
(6) cout<<setiosflags(ios∷showpos)<<b;输出： +123456
```
itoa函数的原型为char* itoa(int value, char * string, int radix); int value 被转换的整数，char *string 转换后储存的字符数组int radix 转换进制数，如2,8,10,16 进制等，
```c
#include <stdio.h>
#include <stdlib.h> 

int main()
{
    
    int a = 12;
    printf("八进制 --> %o\n", a);
    printf("十六进制 --> %X\n", a);
    printf("十进制 --> %d\n", a);
    char s[10];
    itoa(a, s, 2);
    printf("二进制 --> %s\n", s);
    itoa(a, s, 3);
    printf("三进制 --> %s\n", s);
    return 0;
}
```
>输出布尔值
std::cout<<std::boolalpha<<bool_variable<<endl; 

### 字符与数字转换
- c风格(a->ascii i->int)
    ```c
    Defined in header <stdlib.h>
    int       atoi( const char *str );
    long      atol( const char *str );
    long long atoll( const char *str );
    ```
- c++风格 
    <string>
    converts a string to a signed integer 
    `stoi stol stoll`
    
    converts a string to an unsigned integer 
    `stoul stoull`
    
    converts a string to a floating point value 
    `stof stod stold`
    
    converts an integral or floating point value to string 
    `to_string`
    
    converts an integral or floating point value to wstring 
    `to_wstring`
    <cstdlib>
    converts a byte string to a floating point value 
    `atof`
    
    converts a byte string to an integer value 
    `atoi atol atoll`
    
    converts a byte string to an integer value 
    `strtol strtoll`
    
    converts a byte string to an unsigned integer value 
    `strtoul strtoull`
    
    converts a byte string to a floating point value 
    `strtof strtod strtold`
 

## 复杂的声明（Right-Left Rule）
how to interpret complex C/C++ declarations
![main-qimg-f447a62012196ede2a03400528f5445a](/assets/main-qimg-f447a62012196ede2a03400528f5445a.webp)
[C Right-Left Rule](http://ieng9.ucsd.edu/~cs30x/rt_lt.rule.html)
The "right-left" rule is a completely regular rule for deciphering C
declarations.  It can also be useful in creating them.

First, symbols.  Read

     *		as "pointer to"			- always on the left side
     [] 	as "array of"			- always on the right side
     ()		as "function returning"		- always on the right side

as you encounter them in the declaration.

STEP 1
------
Find the identifier.  This is your starting point.  Then say to yourself,
"identifier is."  You've started your declaration.
>identifier 标识符
modifier 修饰符

STEP 2
------
Look at the symbols on the right of the identifier.  If, say, you find "()"
there, then you know that this is the declaration for a function.  So you
would then have "identifier is function returning".  Or if you found a 
"[]" there, you would say "identifier is array of".  Continue right until
you run out of symbols *OR* hit a *right* parenthesis ")".  (If you hit a 
left parenthesis, that's the beginning of a () symbol, even if there
is stuff in between the parentheses.  More on that below.)

STEP 3
------
Look at the symbols to the left of the identifier.  If it is not one of our
symbols above (say, something like "int"), just say it.  Otherwise, translate
it into English using that table above.  Keep going left until you run out of
symbols *OR* hit a *left* parenthesis "(".  

Now repeat steps 2 and 3 until you've formed your declaration.  Here are some
examples:

     int *p[];

1) Find identifier.          int *p[];
                                  ^
   "p is"

2) Move right until out of symbols or right parenthesis hit.
                             int *p[];
                                   ^^
   "p is array of"

3) Can't move right anymore (out of symbols), so move left and find:
                             int *p[];
                                 ^
   "p is array of pointer to"

4) Keep going left and find:
                             int *p[];
                             ^^^
   "p is array of pointer to int". 
   (or "p is an array where each element is of type pointer to int")

Another example:

   int *(*func())();

1) Find the identifier.      int *(*func())();
                                    ^^^^
   "func is"

2) Move right.               int *(*func())();
                                        ^^
   "func is function returning"

3) Can't move right anymore because of the right parenthesis, so move left.
                             int *(*func())();
                                   ^
   "func is function returning pointer to"

4) Can't move left anymore because of the left parenthesis, so keep going
   right.                    int *(*func())();
                                           ^^
   "func is function returning pointer to function returning"

5) Can't move right anymore because we're out of symbols, so go left.
                             int *(*func())();
                                 ^
   "func is function returning pointer to function returning pointer to"

6) And finally, keep going left, because there's nothing left on the right.
                             int *(*func())();
                             ^^^
   "func is function returning pointer to function returning pointer to int".


As you can see, this rule can be quite useful.  You can also use it to
sanity check yourself while you are creating declarations, and to give
you a hint about where to put the next symbol and whether parentheses
are required.

Some declarations look much more complicated than they are due to array
sizes and argument lists in prototype form.  If you see "[3]", that's
read as "array (size 3) of...".  If you see "(char *,int)" that's read
as "function expecting (char *,int) and returning...".  Here's a fun
one:

                 int (*(*fun_one)(char *,double))[9][20];

I won't go through each of the steps to decipher this one.

Ok.  It's:

     "fun_one is pointer to function expecting (char *,double) and 
      returning pointer to array (size 9) of array (size 20) of int."

As you can see, it's not as complicated if you get rid of the array sizes
and argument lists:

     int (*(*fun_one)())[][];

You can decipher it that way, and then put in the array sizes and argument
lists later.

Some final words:

It is quite possible to make illegal declarations using this rule,
so some knowledge of what's legal in C is necessary.  For instance,
if the above had been:

     int *((*fun_one)())[][];

it would have been "fun_one is pointer to function returning array of array of
                                          ^^^^^^^^^^^^^^^^^^^^^^^^
pointer to int".  Since a function cannot return an array, but only a 
pointer to an array, that declaration is illegal.


Illegal combinations include:

	 []() - cannot have an array of functions
	 ()() - cannot have a function that returns a function
	 ()[] - cannot have a function that returns an array

In all the above cases, you would need a set of parens to bind a *
symbol on the left between these () and [] right-side symbols in order
for the declaration to be legal.

Here are some legal and illegal examples:

int i;                  an int
int *p;                 an int pointer (ptr to an int)
int a[];                an array of ints
int f();                a function returning an int
int **pp;               a pointer to an int pointer (ptr to a ptr to an int)
int (*pa)[];            a pointer to an array of ints
int (*pf)();            a pointer to a function returning an int
int *ap[];              an array of int pointers (array of ptrs to ints)
int aa[][];             an array of arrays of ints
int af[]();             an array of functions returning an int (ILLEGAL)
int *fp();              a function returning an int pointer
int fa()[];             a function returning an array of ints (ILLEGAL)
int ff()();             a function returning a function returning an int
                                (ILLEGAL)
int ***ppp;             a pointer to a pointer to an int pointer
int (**ppa)[];          a pointer to a pointer to an array of ints
int (**ppf)();          a pointer to a pointer to a function returning an int
int *(*pap)[];          a pointer to an array of int pointers
int (*paa)[][];         a pointer to an array of arrays of ints
int (*paf)[]();         a pointer to a an array of functions returning an int
                                (ILLEGAL)
int *(*pfp)();          a pointer to a function returning an int pointer
int (*pfa)()[];         a pointer to a function returning an array of ints
                                (ILLEGAL)
int (*pff)()();         a pointer to a function returning a function
                                returning an int (ILLEGAL)
int **app[];            an array of pointers to int pointers
int (*apa[])[];         an array of pointers to arrays of ints
int (*apf[])();         an array of pointers to functions returning an int
int *aap[][];           an array of arrays of int pointers
int aaa[][][];          an array of arrays of arrays of ints
int aaf[][]();          an array of arrays of functions returning an int
                                (ILLEGAL)
int *afp[]();           an array of functions returning int pointers (ILLEGAL)
int afa[]()[];          an array of functions returning an array of ints
                                (ILLEGAL)
int aff[]()();          an array of functions returning functions
                                returning an int (ILLEGAL)
int **fpp();            a function returning a pointer to an int pointer
int (*fpa())[];         a function returning a pointer to an array of ints
int (*fpf())();         a function returning a pointer to a function
                                returning an int
int *fap()[];           a function returning an array of int pointers (ILLEGAL)
int faa()[][];          a function returning an array of arrays of ints
                                (ILLEGAL)
int faf()[]();          a function returning an array of functions
                                returning an int (ILLEGAL)
int *ffp()();           a function returning a function
                                returning an int pointer (ILLEGAL)


## IEEE二进制浮点数算术标准（IEEE 754）
|形式|	指数|	小数部分|
|:---:|:---:|:---:|
|零|	0	|0
|非规约形式|	0|	非0|
|规约形式 |1到 2^e^-2 |任意
|无穷	|2^e^-1	|0
|NaN| 2^e^-1|非零

### 非规约形式
非规约形式的浮点数绝对值已经小于所有的规约浮点数的绝对值；即所有的非规约浮点数比规约浮点数更接近0，一般是某个数字相当接近零时才会使用非规约型式来表示。。规约浮点数的尾数大于等于1且小于2，而非规约浮点数的尾数小于1且大于0。IEEE754-1985标准采用非规约浮点数，用来解决填补绝对值意义下最小规格数与零的距离。非规约浮点数源于70年代末IEEE浮点数标准化专业技术委员会酝酿浮点数二进制标准时，Intel公司对渐进式下溢出（gradual underflow）的力荐。如果没有渐进式下溢出，那么0与绝对值最小的浮点数之间的距离（gap）将大于相邻的小浮点数之间的距离。例如单精度浮点数的绝对值最小的规约浮点数是  1.0*2^-126^,它与绝对值次小的规约浮点数之间的距离为  2^-126^*2^-23^=2^-149^。如果不采用渐进式下溢出，那么绝对值最小的规约浮点数与0的距离是相邻的小浮点数之间距离的2^23^倍！可以说是非常突然的下溢出到0。这种情况的一种糟糕后果是：两个不等的小浮点数X与Y相减，结果将是0.

### 有效数字
单精和双精浮点数的有效数字分别是有存储的23和52个位，加上最左手边没有存储的第1个位，即是24和53个位。
$log 2^{24}=7.22$
$log 2^{53}=15.95$
由以上的计算，单精和双精浮点数可以保证7位和15位十进制有效数字。

### 十进制精度
C++语言标准定义的浮点数的十进制精度(decimal precision)：十进制数字的位数，可被(浮点数)表示而值不发生变化。C语言标准定义的浮点数的十进制精度为：十进制数字的位数q，使得任何具有q位十进制数字的浮点数可近似表示为b进制的p位数字并且能近似回十进制表示而不改变这q位十进制数字
但由于相对近似误差不均匀，有的7位十进制浮点数不能保证近似转化为32比特浮点再近似转化回7位十进制浮点后保持值不变：例如8.589973e9将变成8.589974e9。这种近似误差不会超过1比特的表示能力，因此(24-1)*std::log10(2)等于6.92，下取整为6，成为std::numeric_limits<float>::digits10以及FLT_DIG的值。std::numeric_limits<float>::max_digits10的值为9，含义是必须9位十进制数字才能区分float的所有值；也即float的最大表示区分度。
类似的，std::numeric_limits<double>::digits10或DBL_DIG是15， std::numeric_limits<double>::max_digits10是17

以下的C++程序，概略地展示了单精和双精浮点数的精度。
```c++
#include <iostream>

int main () {
    std::cout.precision(20);
    float a=123.45678901234567890;
    double b=123.45678901234567890;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    return 0;
}

// Xcode 5.1
// Output:
// 123.456787109375
// 123.45678901234568059
// Program ended with exit code: 0
```

参考：
1. [IEEE 754](https://zh.wikipedia.org/wiki/IEEE_754)
2. [boost float-point comparison](http://www.boost.org/doc/libs/1_65_1/libs/math/doc/html/math_toolkit/float_comparison.html)
3. [boost floating-point Numbers](http://www.boost.org/doc/libs/1_65_1/libs/multiprecision/doc/html/boost_multiprecision/tut/floats.html)
4. [boost mutiprecision](http://www.boost.org/doc/libs/1_65_1/libs/multiprecision/doc/html/index.html)
5. [一个浮点数跨平台产生的问题](https://coolshell.cn/articles/11235.html)



## [C++ STL详解之容器](http://huqunxing.site/2016/09/22/C++STL%E8%AF%A6%E8%A7%A3%E4%B9%8B%E5%AE%B9%E5%99%A8/)

本篇博客主要介绍C++ 中STL的基础概念以及容器组件，内容来自网上，经过整合而成。

### 概念

STL（Standard Template Library），即标准模板库，是一个具有工业强度的，高效的C++ 程序库。它被容纳于C++ 标准程序库（C++ Standard Library）中，是ANSI/ISO C++ 标准中最新的也是极具革命性的一部分。该库包含了诸多在计算机科学领域里所常用的基本数据结构和基本算法。为广大C++程序员们提供了一个可扩展的应用框架，高度体现了软件的可复用性。

从逻辑层次来看，在STL中体现了泛型化程序设计的思想（generic programming），引入了诸多新的名词，比如像需求（requirements），概念（concept），模型（model），容器（container），算法（algorithmn），迭代子（iterator）等。与OOP（object-oriented programming）中的多态（polymorphism）一样，泛型也是一种软件的复用技术；

从实现层次看，整个STL是以一种类型参数化（type parameterized）的方式实现的，这种方式基于一个在早先C++ 标准中没有出现的语言特性–模板（template）。如果查阅任何一个版本的STL源代码，你就会发现，模板作为构成整个STL的基石是一件千真万确的事情。除此之外，还有许多C++的新特性为STL的实现提供了方便。

从广义上讲，STL的代码分为三类：algorithm, container, iterator 几乎所有的代码都采用了模板类和模板函数的方式。在C++标准中，STL被组织为下面的13个头文件： `<algorithm>、<deque>、<functional>、<iterator>， <vector>， <list>、<map>、<memory>、<numeric>、<queue>、<set>、<stack>和<utility>`。

### 六大组件

*   容器（Container）: 是一种数据结构，如 list，vector，和deques ，以模板类的方法提供。为了访问容器中的数据，可以使用由容器类输出的迭代器；
*   迭代器（Iterator）: 提供了访问容器中对象的方法。例如，可以使用一对迭代器指定list或vector中的一定范围的对象。迭代器就如同一个指针。事实上，C++的指针也是一种迭代器。但是，迭代器也可以是那些定义了operator*()以及其他类似于指针的操作符地方法的类对象；
*   算法（Algorithm）:是用来操作容器中的数据的模板函数。例如，STL用sort()来对一个vector中的数据进行排序，用find()来搜索一个list中的对象，函数本身与他们操作的数据的结构和类型无关，因此他们可以在从简单数组到高度复杂容器的任何数据结构上使用；
*   仿函数（Function object，仿函数(functor): 又称之为函数对象（function object），其实就是重载了()操作符的struct，没有什么特别的地方
*   迭代适配器（Adaptor）:
*   空间配制器（allocator）: 其中主要工作包括两部分1.对象的创建与销毁 2.内存的获取与释放

### 容器 container

#### 序列式容器

每个元素都有固定的位置（取决于插入的时机和位置，与元素值无关），分为 `vector`，`deque`, `list`。

##### vector

**特点：**
将一个元素置于一个**动态数组**中加以管理，可以**随机存取**元素。在数组尾部添加或删除元素非常快速，但是在中部或头部插入或删除元素比较耗时。

**使用方法**
假设有`vector<int> c;`

| 函数名 | 功能 |
| --- | --- |
| push_back | 在数组的最后添加一个数据, 示例： `c.push_back(5);` |
| pop_back | 去掉数组的最后一个数据, 示例：`c.pop_back();` |
| at | 得到编号位置的数据， 示例： `int d = c.at(0);` |
| begin | 得到数组头的指针, 示例： `vector<int>::iterator it = c.begin();` |
| end | 得到数组的最后一个单元+1的指针, 示例： `vector<int>::iterator it = c.end();` |
| front | 得到数组头的引用, 示例： `int first = c.front();` |
| back | 得到数组的最后一个单元的引用, 示例： `int last = c.back();` |
| max_size | 得到vector最大可以是多大 |
| capacity | 当前vector分配的大小 |
| size | 当前使用数据的大小 |
| resize | 改变当前使用数据的大小，如果它比当前使用的大，则填充默认值 |
| reserve | 改变当前vecotr所分配空间的大小 |
| erase | 删除指针指向的数据项 |
| clear | 清空当前的vector |
| rbegin | 将vector反转后的开始指针返回(其实就是原来的end-1) |
| rend | 将vector反转后的结束指针返回(其实就是原来的begin-1) |
| empty | 判断vector是否为空 |
| swap | 与另一个vector交换数据 |

**vector 内存管理与效率**
**使用reserve()函数提前设定容量大小，避免多次容量扩充操作导致效率低下。**
关于STL容器，最令人称赞的特性之一就是是只要不超过它们的最大大小，它们就可以自动增长到足以容纳你放进去的数据。(要知道这个最大值，只要调用名叫max_size的成员函数。)
对于vector和string，如果需要更多空间，就以类似realloc的思想来增长大小。vector容器支持随机访问，因此为了提高效率，它内部使用动态数组的方式实现的。在通过 reserve() 来申请特定大小的时候总是按指数边界来增大其内部缓冲区。当进行 insert 或 push_back 等增加元素的操作时，如果此时动态数组的内存不够用，就要 **动态的重新分配当前大小的1.5~2倍的新内存区** ，再把原数组的内容复制过去。所以，在一般情况下，其访问速度同一般数组，只有在重新分配发生时，其性能才会下降。正如上面的代码告诉你的那样。而进行pop_back操作时，capacity并不会因为vector容器里的元素减少而有所下降，还会维持操作之前的大小。对于vector容器来说，**如果有大量的数据需要进行push_back，应当使用reserve()函数提前设定其容量大小，否则会出现许多次容量扩充操作，导致效率低下。**

reserve成员函数允许你最小化必须进行的重新分配的次数，因而可以避免真分配的开销和迭代器/指针/引用失效。但在我解释reserve为什么可以那么做之前，让我简要介绍有时候令人困惑的四个相关成员函数。在标准容器中，只有vector和string提供了所有这些函数。

*   `size()` : 告诉你容器中有多少元素。它没有告诉你容器为它容纳的元素分配了多少内存。

*   `capacity()`: 告诉你容器在它已经分配的内存中可以容纳多少元素。那是容器在那块内存中总共可以容纳多少元素，而不是还可以容纳多少元素。如果你想知道一个vector或string中有多少没有被占用的内存，你必须从capacity()中减去size()。如果size和capacity返回同样的值，容器中就没有剩余空间了，而下一次插入（通过insert或push_back等）会引发上面的重新分配步骤。

*   `resize(Container::size_type n)`强制把容器改为容纳n个元素。调用resize之后，size将会返回n。如果n小于当前大小，容器尾部的元素会被销毁。如果n大于当前大小，新默认构造的元素会添加到容器尾部。如果n大于当前容量，在元素加入之前会发生重新分配。

*   `reserve(Container::size_type n)`: 强制容器把它的容量改为至少n，提供的n不小于当前大小。这一般强迫进行一次重新分配，因为容量需要增加。（如果n小于当前容量，vector忽略它，这个调用什么都不做，string可能把它的容量减少为size()和n中大的数，但string的大小没有改变。在我的经验中，使用reserve来从一个string中修整多余容量一般不如使用“交换技巧”）

**只要有元素需要插入而且容器的容量不足时就会发生重新分配**（包括它们维护的原始内存分配和回收，对象的拷贝和析构和迭代器、指针和引用的失效）。所以，避免重新分配的关键是使用reserve尽快把容器的容量设置为足够大，最好在容器被构造之后立刻进行。

例如，假定你想建立一个容纳1-1000值的vector。没有使用reserve，你可以像这样来做：

```c++
 vector<int> v;

 for (int i = 1; i <= 1000; ++i)

    v.push_back(i);

```

在大多数STL实现中，这段代码在循环过程中将会导致2到10次重新分配。（10这个数没什么奇怪的。记住vector在重新分配发生时一般把容量翻倍，而1000约等于2^10。）
把代码改为使用reserve，我们得到这个：

```c++
 vector<int> v;

 v.reserve(1000);

 for (int i = 1; i <= 1000;++i)

    v.push_back(i);
```
 

这在循环中不会发生重新分配。
在大小和容量之间的关系让我们可以预言什么时候插入将引起vector或string执行重新分配，而且，可以预言什么时候插入会使指向容器中的迭代器、指针和引用失效。例如，给出这段代码，

```c++
 string s;

 ...

 if (s.size() < s.capacity()) {

 s.push_back('x');

 }

```

push_back 的调用不会使指向这个string中的迭代器、指针或引用失效，因为string的容量保证大于它的大小。如果不是执行push_back，代码在string的任意位置进行一个insert，我们仍然可以保证在插入期间没有发生重新分配，但是，与伴随string插入时迭代器失效的一般规则一致，所有从插入位置到string结尾的迭代器/指针/引用将失效。
通常有两情况使用reserve来避免不必要的重新分配。第一个可用的情况是当你确切或者大约知道有多少元素将最后出现在容器中。那样的话，就像上面的vector代码，你只是提前reserve适当数量的空间。第二种情况是保留你可能需要的最大的空间，然后，一旦你添加完全部数据，修整掉任何多余的容量。

**使用“交换技巧”来修整vector过剩空间/内存**
有一种方法来把它从曾经最大的容量减少到它现在需要的容量。这样减少容量的方法常常被称为“收缩到合适（shrink to fit）”。该方法只需一条语句：
`vector<int>(ivec).swap(ivec);`
表达式vector(ivec)建立一个临时vector，它是ivec的一份拷贝：vector的拷贝构造函数做了这个工作。但是，vector的拷贝构造函数只分配拷贝的元素需要的内存，所以这个临时vector没有多余的容量。然后我们让临时vector和ivec交换数据，这时我们完成了，ivec只有临时变量的修整过的容量，而这个临时变量则持有了曾经在ivec中的没用到的过剩容量。在这里（这个语句结尾），临时vector被销毁，因此释放了以前ivec使用的内存，收缩到合适。

**用swap方法强行释放STL Vector所占内存**

```c++
 template < class T> void ClearVector( vector<T>& v )

 {

 vector<T>vtTemp;

 vtTemp.swap( v );

 }

 如

 vector<int> v ;

 nums.push_back(1);

 nums.push_back(3);

 nums.push_back(2);

 nums.push_back(4);

 vector<int>().swap(v);

 /* 或者v.swap(vector<int>()); */

 /*或者{ std::vector<int> tmp = v; v.swap(tmp); }; //加大括号{ }是让tmp退出{ }时自动析构*/

```

**其他相关函数**

```c++
 c.assign(beg,end) //将[beg; end)区间中的数据赋值给c。

 c.assign(n,elem) //将n个elem的拷贝赋值给c。

 c.at(idx) //传回索引idx所指的数据，如果idx越界，抛出out_of_range。

 c.back() //传回最后一个数据，不检查这个数据是否存在。

 c.front() //传回第一个数据。

 get_allocator //使用构造函数返回一个拷贝。

 c.rbegin() //传回一个逆向队列的第一个数据。

 c.rend() //传回一个逆向队列的最后一个数据的下一个位置。

 c.~ vector <Elem>() //销毁所有数据，释放内存。

```

**使用示例：**

```c++
 #include <iostream>

 #include <vector>

 using namespace std;

 typedef vector<int> INTVECTOR;//自定义类型INTVECTOR

 //测试vector容器的功能

 int main()

 {

 //vec1对象初始为空

 INTVECTOR vec1;

 //vec2对象最初有10个值为6的元素

 INTVECTOR vec2(10,6);

 //vec3对象最初有3个值为6的元素，拷贝构造

 INTVECTOR vec3(vec2.begin(),vec2.begin()+3);

 //声明一个名为i的双向迭代器

 INTVECTOR::iterator i;

 //从前向后显示vec1中的数据

 cout<<"vec1.begin()--vec1.end():"<<endl;

 for (i =vec1.begin(); i !=vec1.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //从前向后显示vec2中的数据

 cout<<"vec2.begin()--vec2.end():"<<endl;

 for (i =vec2.begin(); i !=vec2.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //从前向后显示vec3中的数据

 cout<<"vec3.begin()--vec3.end():"<<endl;

 for (i =vec3.begin(); i !=vec3.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //测试添加和插入成员函数，vector不支持从前插入

 vec1.push_back(2);//从后面添加一个成员

 vec1.push_back(4);

 vec1.insert(vec1.begin()+1,5);//在vec1第一个的位置上插入成员5

 //从vec1第一的位置开始插入vec3的所有成员

 vec1.insert(vec1.begin()+1,vec3.begin(),vec3.end());

 cout<<"after push() and insert() now the vec1 is:" <<endl;

 for (i =vec1.begin(); i !=vec1.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //测试赋值成员函数

 vec2.assign(8,1); // 重新给vec2赋值，8个成员的初始值都为1

 cout<<"vec2.assign(8,1):" <<endl;

 for (i =vec2.begin(); i !=vec2.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //测试引用类函数

 cout<<"vec1.front()="<<vec1.front()<<endl;//vec1第零个成员

 cout<<"vec1.back()="<<vec1.back()<<endl;//vec1的最后一个成员

 cout<<"vec1.at(4)="<<vec1.at(4)<<endl;//vec1的第五个成员

 cout<<"vec1[4]="<<vec1[4]<<endl;

 //测试移出和删除

 vec1.pop_back();//将最后一个成员移出vec1

 vec1.erase(vec1.begin()+1,vec1.end()-2);//删除成员

 cout<<"vec1.pop_back() and vec1.erase():" <<endl;

 for (i =vec1.begin(); i !=vec1.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //显示序列的状态信息

 cout<<"vec1.size(): "<<vec1.size()<<endl;//打印成员个数

 cout<<"vec1.empty(): "<<vec1.empty()<<endl;//清空

 }

 /**运行结果

 vec1.begin()--vec1.end():

 vec2.begin()--vec2.end():

 6 6 6 6 6 6 6 6 6 6

 vec3.begin()--vec3.end():

 6 6 6

 after push() and insert() now the vec1 is:

 2 6 6 6 5 4

 vec2.assign(8,1):

 1 1 1 1 1 1 1 1

 vec1.front()=2

 vec1.back()=4

 vec1.at(4)=5

 vec1[4]=5

 vec1.pop_back() and vec1.erase():

 2 6 5

 vec1.size(): 3

 vec1.empty(): 0

 */

```

##### deque

“double-ended queue” 双端队列，可以**随机存取**。数组尾部或头部添加或删除元素非常快速，但在中部插入或删除元素比较费时。

双端队列是一种优化了的、对序列两端元素进行添加和删除操作的基本序列容器。它允许较为快速地随机访问，但它不像vector 把所有的对象保存在一块连续的内存块，而是采用多个连续的存储块，并且在一个映射结构中保存对这些块及其顺序的跟踪。向deque 两端添加或删除元素的开销很小。它不需要重新分配空间，所以向末端增加元素比vector 更有效。
双向队列和向量很相似，但是它允许在容器头部快速插入和删除（就像在尾部一样）。
实际上，deque 是对vector 和list 优缺点的结合，它是处于两者之间的一种容器。

**Deque 的特点**：

*   随机访问方便，即支持 `[ ]` 操作符和`vector.at()` ，但性能没有vector 好；
*   可以在内部进行插入和删除操作，但性能不及list ；
*   可以在两端进行push 、pop ；
*   相对于verctor 占用更多的内存。

**使用方法：**

*   Constructors 创建一个新双向队列
    语法:

    ```c++
     deque();//创建一个空双向队列

     deque( size_type size );// 创建一个大小为size的双向队列

     deque( size_type num, const TYPE &val ); //放置num个val的拷贝到队列中

     deque( const deque &from );// 从from创建一个内容一样的双向队列

     deque( input_iterator start, input_iterator end ); // start 和 end - 创建一个队列，保存从start到end的元素。
    ```
     

*   Operators 比较和赋值双向队列

    可以使用[]操作符访问双向队列中单个的元素

*   assign() 设置双向队列的值
    语法:

    ```c++
     void assign( input_iterator start, input_iterator end); //start和end指示的范围为双向队列赋值

     void assign( Size num, const TYPE &val );//设置成num个val。

    ```

*   at() 返回指定的元素
    语法: `reference at( size_type pos );` 返回一个引用，指向双向队列中位置pos上的元素

*   back() 返回最后一个元素
    语法: `reference back();` //返回一个引用，指向双向队列中最后一个元素

*   begin() 返回指向第一个元素的迭代器
    语法: `iterator begin();`//返回一个迭代器，指向双向队列的第一个元素

*   clear() 删除所有元素

*   empty() 返回真如果双向队列为空

*   end() 返回指向尾部的迭代器

*   erase() 删除一个元素
    语法:

    ```c++
     iterator erase( iterator pos ); //删除pos位置上的元素

     iterator erase( iterator start, iterator end ); //删除start和end之间的所有元素

     //返回指向被删除元素的后一个元素

    ```

*   front() 返回第一个元素的引用

*   get_allocator() 返回双向队列的配置器

*   insert() 插入一个元素到双向队列中
    语法:
    ```c++
     iterator insert( iterator pos, size_type num, const TYPE &val ); //pos前插入num个val值

     void insert( iterator pos, input_iterator start, input_iterator end ); //插入从start到end范围内的元素到pos前面
    ```

*   max_size() 返回双向队列能容纳的最大元素个数

*   pop_back() 删除尾部的元素

*   pop_front() 删除头部的元素

*   push_back() 在尾部加入一个元素

*   push_front() 在头部加入一个元素

*   rbegin() 返回指向尾部的逆向迭代器

*   rend() 返回指向头部的逆向迭代器

*   resize() 改变双向队列的大小

*   size() 返回双向队列中元素的个数

*   swap() 和另一个双向队列交换元素
    语法： `void swap( deque &target );` // 交换target和现双向队列中元素

**使用示例**：
```c++
 //双向队列 deque

 #include <deque>

 #include <cstdio>

 #include <algorithm>

 using namespace std;

 int main()

 {

 deque<int> ideq(20); //Create a deque ideq with 20 elements of default value 0

 deque<int>::iterator pos;

 int i;

 //使用assign()赋值 assign在计算机中就是赋值的意思

 for (i = 0; i < 20; ++i)

 ideq[i] = i;

 //输出deque

 printf("输出deque中数据:\n");

 for (i = 0; i < 20; ++i)

 printf("%d ", ideq[i]);

 putchar('\n');

 //在头尾加入新数据

 printf("\n在头尾加入新数据...\n");

 ideq.push_back(100);

 ideq.push_front(i);

 //输出deque

 printf("\n输出deque中数据:\n");

 for (pos = ideq.begin(); pos != ideq.end(); pos++)

 printf("%d ", *pos);

 putchar('\n');

 //查找

 const int FINDNUMBER = 19;

 printf("\n查找%d\n", FINDNUMBER);

 pos = find(ideq.begin(), ideq.end(), FINDNUMBER);

 if (pos != ideq.end())

 printf("find %d success\n", *pos);

 else

 printf("find failed\n");

 //在头尾删除数据

 printf("\n在头尾删除数据...\n");

 ideq.pop_back();

 ideq.pop_front();

 //输出deque

 printf("\n输出deque中数据:\n");

 for (pos = ideq.begin(); pos != ideq.end(); pos++)

 printf("%d ", *pos);

 putchar('\n');

 return 0;

 }

 /**输出结果：

 输出deque中数据:

 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

 在头尾加入新数据...

 输出deque中数据:

 20 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 100

 查找19

 find 19 success

 在头尾删除数据...

 输出deque中数据:

 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19

 */

```

##### list

双向链表，不提供随机存取（**按顺序存储**），在任何位置插入或删除动作都非常迅速。只能顺序访问（从前向后或者从后向前）。与前面两种容器类有一个明显的区别就是：它**不支持随机访问**。要访问表中某个下标处的项需要从表头或表尾处（接近该下标的一端）开始循环。而且缺少下标运算符：operator[ ]。

**用法：**

| 函数名 | 说明 |
| --- | --- |
| assign() | 给list赋值 |
| back() | 返回最后一个元素 |
| begin() | 返回指向第一个元素的迭代器 |
| clear() | 删除所有元素 |
| empty() | 如果list是空的则返回true |
| end() | 返回末尾的迭代器 |
| erase() | 删除一个元素 |
| front() | 返回第一个元素 |
| get_allocator() | 返回list的配置器 |
| insert() | 插入一个元素到list中 |
| max_size() | 返回list能容纳的最大元素数量 |
| merge() | 合并两个list |
| pop_back() | 删除最后一个元素 |
| pop_front() | 删除第一个元素 |
| push_back() | 在list的末尾添加一个元素 |
| push_front() | 在list的头部添加一个元素 |
| rbegin() | 返回指向第一个元素的逆向迭代器 |
| remove() | 从list删除元素 |
| remove_if() | 按指定条件删除元素 |
| rend() | 指向list末尾的逆向迭代器 |
| resize() | 改变list的大小 |
| reverse() | 把list的元素倒转 |
| size() | 返回list中的元素个数 |
| sort() | 给list排序 |
| splice() | 合并两个list,源list的内容部分或全部元素删除，拼插入到目的list |
| swap() | 交换两个list |
| unique() | 删除list中重复的元素 |

**用法示例：**

```c++
 #include <iostream>

 #include <list>

 #include <numeric>

 #include <algorithm>

 using namespace std;

 //创建一个list容器的实例LISTINT

 typedef list<int> LISTINT;

 //创建一个list容器的实例LISTCHAR

 typedef list<int> LISTCHAR;

 int main()

 {

 //用list容器处理整型数据

 //用LISTINT创建一个名为listOne的list对象

 LISTINT listOne;

 //声明i为迭代器

 LISTINT::iterator i;

 //从前面向listOne容器中添加数据

 listOne.push_front (2);

 listOne.push_front (1);

 //从后面向listOne容器中添加数据

 listOne.push_back (3);

 listOne.push_back (4);

 //从前向后显示listOne中的数据

 cout<<"listOne.begin()--- listOne.end():"<<endl;

 for (i = listOne.begin(); i != listOne.end(); ++i)

 cout << *i << " ";

 cout << endl;

 //从后向后显示listOne中的数据

 LISTINT::reverse_iterator ir;

 cout<<"listOne.rbegin()---listOne.rend():"<<endl;

 for (ir =listOne.rbegin(); ir!=listOne.rend();ir++) {

 cout << *ir << " ";

 }

 cout << endl;

 //使用STL的accumulate(累加)算法

 int result = accumulate(listOne.begin(), listOne.end(),0);

 cout<<"Sum="<<result<<endl;

 cout<<"------------------"<<endl;

 //--------------------------

 //用list容器处理字符型数据

 //--------------------------

 //用LISTCHAR创建一个名为listOne的list对象

 LISTCHAR listTwo;

 //声明i为迭代器

 LISTCHAR::iterator j;

 //从前面向listTwo容器中添加数据

 listTwo.push_front ('A');

 listTwo.push_front ('B');

 //从后面向listTwo容器中添加数据

 listTwo.push_back ('x');

 listTwo.push_back ('y');

 //从前向后显示listTwo中的数据

 cout<<"listTwo.begin()---listTwo.end():"<<endl;

 for (j = listTwo.begin(); j != listTwo.end(); ++j)

 cout << char(*j) << " ";

 cout << endl;

 //使用STL的max_element算法求listTwo中的最大元素并显示

 j=max_element(listTwo.begin(),listTwo.end());

 cout << "The maximum element in listTwo is: "<<char(*j)<<endl;

 }

 /**输出结果：

 listOne.begin()--- listOne.end():

 1 2 3 4

 listOne.rbegin()---listOne.rend():

 4 3 2 1

 Sum=10

 ------------------

 listTwo.begin()---listTwo.end():

 B A x y

 The maximum element in listTwo is: y

 */

```

#### 有序关联容器

元素位置取决于key和特定的排序准则（红黑树），与插入顺序无关，包含 `set，multiset, map, multimap`
**Sets/Multisets：**
内部的元素依据其值自动排序，Set内的相同数值的元素只能出现一次，Multisets内可包含多个数值相同的元素，内部由二叉树实现（实际上基于红黑树(RB-tree）实现），便于查找；

**Maps/Multimaps：**
Map的元素是成对的键值/实值，内部的元素依据其值自动排序，Map内的相同数值的元素只能出现一次，Multimaps内可包含多个数值相同的元素，内部由二叉树实现（实际上基于红黑树(RB-tree）实现），便于查找；

另外有其他无序关联容器`unordered_map,unordered_set,unordered_multiset,unordered_multimap`。

**关联容器和顺序容器的本质区别：** 关联容器是通过键存取和读取元素、顺序容器通过元素在容器中的位置顺序存储和访问元素。因此，关联容器不提供`front、push_front、pop_front、back、push_back以及pop_back`，此外对于关联容器不能通过容器大小来定义，因为这样的话将无法知道键所对应的值什么。

**pair 类型**
在介绍关联容器之前，必须先介绍一种与它相关的简单的标准库类型–pair类型：

1.  pair类型的初始化 （在头文件utility中）

    ```c++
     pair<T1,T2> p1; // 创建一个pair对象，两个元素的类型分别是T1,T2类型，采用初值进行初始化

     pair<T1,T2> p1(v1,v2); //创建一个pair对象，两个元素的类型分别是T1,T2类型，采用v1,v2分别进行初始化

     make_pair(v1,v2); // 以v1、v2的值创建一个pair对象，类型分别是v1、v2的类型

     p.first // 返回p中第一个公有数据成员

     p.second // 返回p中第二个公有数据成员

    ```

2.  pair使用：

    ```c++
     #include<utility>

     pair<string,int> author("Peter",30);

     cout<<author.first<<"\t"<<author.second<<endl;//可以直接访问数据成员

     //使用typedef进行简化

     typedef pair<string,string> Student;

     Student s1,s2("aaa","bbb");

     s1.first="ccc";

     s1.second="ddd";

     //使用make_pair函数生成一个新的pair对象

     string first="eee",second="fff";

     Student s3=make_pair(first,second);

    ```

##### map

map就是一个容器，里面装的就是若干个pair。每个pair的第一个元素，称为键（**注意键的类型必须支持小于(<)操作**），第二个元素，称为值。对于普通的map，每个键都对应一个值。这样的看起来，键类似于数组的下标，而值类似于数组的值。map类定义了3种类型，分别为`key_type、mapped_type、以及value_type`。他们分别表示了键的类型、值的类型，以及一个pair类型，pair的第一个元素是键，第二个元素是值。
|Member type	|Definition
|---|---
|key_type	|Key
|mapped_type	|T
|value_type	|std::pair<const Key, T>

**map 的使用**

>插入元素
`map::insert`
pair<iterator, bool> insert(const value_type& Val);
`map::emplace`
Inserts an element constructed in place (no copy or move operations are performed) into a map.
template <class... Args>  
pair<iterator, bool> emplace(Args&&... args);
`map::operator[]`
Type& operator[](const Key& key);
如果已存在则修改，如果不存在，视为插入
使用make_pair初始化时需要include<unility> 

*   map 初始化：

    ```c++
     map<k,v> m1 // 创建一个名m1的空的map对形象，对其键和值的类型分别为k、v

     map<k,v> m(m2) // 创建m2的副本m,m与m2的类型必须相同的键值类型和值类型

     map<k,v> m(b,e) // 创建map类型的对象m，存储迭代器b和e标记范围内所有元素的副本，元素的类型必须转换为pair<const k, v>

    ```

    map定义的类型：

    ```c++
     map<K,V>::key_type //在map中用做索引的键的类型

     map<K,V>::mapped_type //在map中键所关联的值的类型

     map<K,V>::value_type //一个pair类型，typedef pair<const Key, T> value_type


    ```

    map迭代器进行解引用将产生pair类型的对象，如：

    ```c++
     map<string,int>::iterator map_it = word_count.begin();

     cout<<map_it->first<<""<<map_it->second<<endl;

    ```

*   给map添加成员：
    两种方法： 使用键（下标）或者 使用 insert 。
    使用下标访问map对象时，首先在map对象查找键值为x的元素如果找到则返回它的值（类型是map<k,v>::mapped_type），否则插入一个新的对象键值为x,值为map<k,v>中v的默认初值。因此，使用下标访问map与使用下标访问数组或vector的行为不同，用**下标访问不存在的元素将导致在map容器中添加一个新的元素，它的键即为该下标值**。这一特性可以使程序简练：

    ```c++
     map<string,int> word_count;

     word_count["Peter"]=10; //相当于增加一个键值对

     //创建一个map对象,用来记录每个单词出现的次数,十分简洁。

     //因为如果读取的是一个新单词，则将在word_count中添加以该单词为索引的新元素

     map<string,int> word_count;

     string word;

     while(cin>>word)

     {

     ++word_count[word];

     }

     // 使用Insert对map进行插入：

     m .insert(e) //e是一个用在m上的value_type类型的值，如果键值e.first不在m中,则插入一个值为e的新元素，如果该键值在m中已经存在，则原元素保持不变。该函数返回一个pair类型，包含一个指向键值为e.first的元素的map迭代器，以及一个bool类型的对象，表示是否插入新元素。

     m.insert(beg,end) //插入beg、end标记范围内的元素，如果该元素的m.first已经存在则不插入否则插入。返回void类型。

     m.insert(iter,e) //如果e.first不在m中，则创建新元素，并以迭代器iter为起点搜索新元素的存储位置，否则返回一个迭代器，指向m中具有的给定键的元素。

     //用insert方法重写单词统计程序

     map<string,int> word_count;

     word_count.insert(map<string,int>::value_type("aaa",1));

     map<string,int> word_count;

     string word;

     while(cin>>word)

     {

     pair<map<string,int>::iterator,bool> ret=word_count.insert(make_pair<string,int>(word,1));

     if(!ret.second)//如果没插入成功，证明原来已经存在键值,将统计值+1

     {

     ++ret.first->second;// first是一个迭代器，指向插入的键

     }

     }

    ```

*   查找和读取map中的元素：
    `m.count(k)`：返回k在m中出现的次数，在map中只是返回0、1
    `m.find(k)`： 如果k在m中的键值存在则返回相应的迭代器，否则返回超出来末端迭代器end

    ```c++
     //读取元素而又不插入新元素

     int occurs;

     map<string,int>::iterator it= word_count.find("foobar");//不存在，则返回end迭代器

     if(it!=word_count.end())//可能找不到

     {

     occurs=it.second;

     }

    ```

*   从map中删除元素 ，使用erase与顺序容器功能一样：
    `m.erase(k)`： 删除m中键为k的元素。返回值为被删除元素的个数，对于map容器而言，其值必然是0或1。
    `m.erase(p)` ： 从m中删除迭代器p所指向的元素。返回值为void类型。
    `m.erase(b,e)`： 从m中删除一段由一对迭代器范围的元素。返回值为void类型。

*   map对象的迭代遍历:

    ```c++
     map<string,int> word_count;

     map<string,int>::const_iterator iter = word_count.begin();

     while(iter!=word_count.end())

     {

     cout<<iter->second<<endl;

     iter++;

     }

    ```

**使用示例：**

```c++
 #include <iostream>

 #include <map>

 #include <string>

 #include <vector>

 using namespace std;

 int main()

 {

 string str;

 map<string,int> wordCount;

 while(cin>>str)

 {

 //对于每个单词，都尝试去插入它

 pair<map<string,int>::iterator,bool> ret = wordCount.insert(make_pair(str,1));

 //通过检测返回值来判断插入是否成功

 if(!ret.second)

 //插入失败表明map中有这个单词，只需要把对应键的值自增即可

 ++ret.first->second;

 }

 map<string,int>::iterator it_map = wordCount.begin();

 cout<<"word"<<"\t\t"<<"count"<<endl;

 for(;it_map != wordCount.end();++it_map)

 cout<<it_map->first<<"\t\t"<<it_map->second<<endl;

 //count方法：对于map，返回1或者0

 int cnt = 0;

 cnt = wordCount.count("bird");

 cout<<"cnt"<<cnt<<endl;

 //find方法：返回的是指向键的迭代器

 int occurs = 0;

 map<string,int>::iterator it = wordCount.find("bird");

 if(it != wordCount.end())

 occurs = it->second;

 cout<<"occurs = "<<occurs<<endl;

 //删除元素

 int del;

 string s1 = "hate";

 //使用值删除

 del = wordCount.erase(s1);

 if(del)

 cout<<s1<<" has been removed! "<<endl;

 else

 cout<<"can't find the word! "<<endl;

 //使用迭代器删除

 map<string,int>::iterator iter = wordCount.begin();

 wordCount.erase(iter);

 return 0;

 }

 /*

 输入：

 hi

 hi

 hi

 hi

 hi

 hello

 hello

 world

 world

 jack

 jack

 mali

 mali

 mary

 mary

 haha

 haha

 hi

 hell

 ^Z

 输出：

 word count

 haha 2

 hell 1

 hello 2

 hi 6

 jack 2

 mali 2

 mary 2

 world 2

 cnt0

 occurs = 0

 can't find the word!

 */

```

##### set

set只有键，没有值，所以他的`value_type`不是pair类型，而是`key_type`类型。同样的，它也支持insert、find、count操作。map比较适合于储存键值对应的情况，而set适合于储存键，判断键在不在这个集合中，比如黑名单之类的。
set的作用就是排序。每个元素的值不能直接被改变。 它是一个容器，它用于储存数据并且能从一个数据集合中取出数据。它的每个元素的值必须惟一，而且系统会根据该值来自动将数据排序。每个元素的值不能直接被改变。
大小可变的集合，支持通过键值实现的快速读取。对于单纯想知道一个值是否存在则set容器最适用。
在set容器中`value_type`不是pair类型，而是与`key_value`的类型相同，它的键值类型也是唯一的且不能修改
在set也支持find、count、insert、erase操作

在set中添加元素：

```c++
 set<int> set1;

 pair<set<int>::iterator,bool> p=set1.insert(1);//返回pair类型对象，包含一个迭代器和一个布尔值

 set1.insert(2);

 int arr[]={1,2,3};

 set<int> set2;

 set2.insert(arr,arr+3);//返回void类型

```

从set中获取元素:与map方法使用类似，使用find和count函数。

```c++
 #include <iostream>

 #include <map>

 #include <string>

 using namespace std;

 int main()

 {

 multimap<string,string> authors;

 string author,work,searchItem;

 //建立作者及其作品的容器

 do

 {

 cout<<"enter authors name"<<endl;

 cin>>author;

 if(!cin)

 break;

 cout<<"enter authors works"<<endl;

 while(cin>>work)

 authors.insert(make_pair(author,work));

 cin.clear();

 }while(cin);

 cin.clear();

 //删除元素

 cout<<"who is the author that you want erase:"<<endl;

 cin>>searchItem;

 /*

 //使用erase删除：输出对应键的所有值

 multimap<string,string>::iterator iter = authors.find(searchItem);

 if(iter != authors.end())

 authors.erase(searchItem);

 else

 cout<<"cannot find the author!"<<endl;

 */

 //使用equal_range或得迭代器删除

 typedef multimap<string,string>::iterator itType;

 pair<itType,itType> pos = authors.equal_range(searchItem);

 if(pos.first != pos.second)

 authors.erase(pos.first,pos.second);

 else

 cout<<"can not find this author!"<<endl;

 //输出删除结果

 cout<<"author\t\twork:"<<endl;

 multimap<string,string>::iterator itbegin = authors.begin();

 for(;itbegin != authors.end();++itbegin)

 cout<<itbegin->first<<"\t\t"<<itbegin->second<<endl;

 return 0;

 }

```

## C++的常用容器
### vector
vector和**数组**类似，拥有一段**连续**的内存空间，并且起始地址不变。
因此能高效的进行随机存取，时间复杂度为o(1);
但因为内存空间是连续的，所以在进行插入和删除操作时，会造成内存块的拷贝，时间复杂度为o(n)。
另外，当数组中内存空间不够时，会重新申请一块内存空间并进行内存拷贝。
### list
list是由**双向链表**实现的，因此内存空间是**不连续**的。
只能通过指针访问数据，所以list的随机存取非常没有效率，时间复杂度为o(n);
但由于链表的特点，能高效地进行插入和删除。
- list 没有重载[]、list::iterator没有重载+、<、>、但是重载了++

### 容器中的迭代器

- vector和string迭代器支持的运算（参与运算的两个迭代器必须指向的是同一个容器中的元素或者尾元素的下一位置，结果迭代器或者指示容器内的一个元素，或者指示容器尾元素的下一位置）
iter + n
迭代器加上一个整数值仍得一个迭代器，迭代器指示的新位置与原来相比向前移动了若干个元素。
iter - n
迭代器减去一个整数值仍得一个迭代器，迭代器指示的新位置与原来相比向后移动了若干个元素。
iter1 += n
迭代器加法的复合赋值语句，将iter1加n的结果赋给iter1
iter1 -= n
迭代器减法的复合赋值语句，将iter1减n的结果赋给iter1
iter1 - iter2
得到一个整数值，可以为负数
`>、 >=、 <、 <=`
迭代器的关系运算符，如果某迭代器指向的容器位置在另一个迭代器所指位置之前，则说前者小于后者。
std::distance(iter1,iter2）//defined in header<iterator>
求两个迭代器的间距，整数
>InputIt must meet the requirements of InputIterator. The operation is more efficient if InputIt additionally meets the requirements of RandomAccessIterator.
The number of increments needed to go from first to last. The value may be negative if random-access iterators are used and first is reachable from last .

- 交换迭代器指向的元素
    `swap(*iter1,*iter2)`注意解引用符`*`

- iterator 与 reverse_iterator转换 
迭代器（iterator）转逆向迭代器（reverse_iterator），只需要把迭代器转入逆向迭代器的构造函数即可；逆向迭代器转迭代器，调用逆向迭代器的base成员函数即可。
```c++
vector<int>::iterator pos;
vector<int>::reverse_iterator rpos(pos);
pos = rpos.base();
```
- 迭代器越界和试图读取end（）的内容
在vs2015实验时，正常编译，运行时报错。


## [C++ STL详解之算法](http://huqunxing.site/2016/09/29/C++STL%E8%AF%A6%E8%A7%A3%E4%B9%8B%E7%AE%97%E6%B3%95/)

### 简介

STL算法部分主要由头文件 `<algorithm>` ,`<numeric>`, `<functional>` 组成。要使用 STL中的算法函数必须包含头文件`<algorithm>`，对于数值算法须包含`<numeric>`，`<functional>`中则定义了一些模板类，用来声明函数对象。
<a id="more"></a>

### 分类

STL中算法大致分为四类：

1.  非可变序列算法：指不直接修改其所操作的容器内容的算法。
2.  可变序列算法：指可以修改它们所操作的容器内容的算法。
3.  排序算法：包括对序列进行排序和合并的算法、搜索算法以及有序序列上的集合操作。
4.  数值算法：对容器内容进行数值计算。

### 查找算法

**查找算法(13个)：** 判断容器中是否包含某个值

*   **adjacent_find:**

    > 在iterator对标识元素范围内，查找一对相邻重复元素，找到则返回指向这对元素的第一个元素的ForwardIterator。否则返回last。重载版本使用输入的二元操作符代替相等的判断。

*   **binary_search:**

    > 在有序序列中查找value，找到返回true。重载的版本实用指定的比较函数对象或函数指针来判断相等。

*   **count:**

    > 利用等于操作符，把标志范围内的元素与输入值比较，返回相等元素个数。

*   **count_if:**

    > 利用输入的操作符，对标志范围内的元素进行操作，返回结果为true的个数。

*   **equal_range:**

    > 功能类似equal，返回一对iterator，第一个表示lower_bound，第二个表示upper_bound。

*   **find:**

    > 利用底层元素的等于操作符，对指定范围内的元素与输入值进行比较。当匹配时，结束搜索，返回该元素的一个InputIterator。

*   **find_end:**

    > 在指定范围内查找”由输入的另外一对iterator标志的第二个序列”的最后一次出现。找到则返回最后一对的第一个ForwardIterator，否则返回输入的”另外一对”的第一个ForwardIterator。重载版本使用用户输入的操作符代替等于操作。

*   **find_first_of:**

    > 在指定范围内查找”由输入的另外一对iterator标志的第二个序列”中任意一个元素的第一次出现。重载版本中使用了用户自定义操作符。

*   **find_if:**

    > 使用输入的函数代替等于操作符执行find。

*   **lower_bound:**

    > 返回一个ForwardIterator，指向在有序序列范围内的可以插入指定值而不破坏容器顺序的第一个位置。重载函数使用自定义比较操作。

*   **upper_bound:**

    > 返回一个ForwardIterator，指向在有序序列范围内插入value而不破坏容器顺序的最后一个位置，该位置标志一个大于value的值。重载函数使用自定义比较操作。

*   **search:**

    > 给出两个范围，返回一个ForwardIterator，查找成功指向第一个范围内第一次出现子序列(第二个范围)的位置，查找失败指向last1。重载版本使用自定义的比较操作。
    C++17补充了不少新的查找算法 https://en.cppreference.com/w/cpp/algorithm/search

*   **search_n:**

    > 在指定范围内查找val出现n次的子序列。重载版本使用自定义的比较操作。

### 排序和通用算法

**排序和通用算法(14个)：** 提供元素排序策略

| 算法名 | 算法描述 |
| --- | --- |
| inplace_merge: | 合并两个有序序列，结果序列覆盖两端范围。重载版本使用输入的操作进行排序。 |
| merge: | 合并两个有序序列，存放到另一个序列。重载版本使用自定义的比较。 |
| nth_element: | 将范围内的序列重新排序，使所有小于第n个元素的元素都出现在它前面，而大于它的都出现在后面。重载版本使用自定义的比较操作。 |
| partial_sort: | 对序列做部分排序，被排序元素个数正好可以被放到范围内。重载版本使用自定义的比较操作。 |
| partial_sort_copy: | 与partial_sort类似，不过将经过排序的序列复制到另一个容器。 |
| partition: | 对指定范围内元素重新排序，使用输入的函数，把结果为true的元素放在结果为false的元素之前。 |
| random_shuffle: | 对指定范围内的元素随机调整次序。重载版本输入一个随机数产生操作。 |
| reverse: | 将指定范围内元素重新反序排序。 |
| reverse_copy: | 与reverse类似，不过将结果写入另一个容器。 |
| rotate: | 将指定范围内元素移到容器末尾，由middle指向的元素成为容器第一个元素。 |
| rotate_copy: | 与rotate类似，不过将结果写入另一个容器。 |
| sort: | 以升序重新排列指定范围内的元素。重载版本使用自定义的比较操作。 |
| stable_sort: | 与sort类似，不过保留相等元素之间的顺序关系。 |
| stable_partition: | 与partition类似，不过不保证保留容器中的相对顺序。 |

### 删除和替换算法

**删除和替换算法(15个)**

| 算法名 | 算法描述 |
| --- | --- |
| copy: | 复制序列 |
| copy_backward: | 与copy相同，不过元素是以相反顺序被拷贝。 |
| iter_swap: | 交换两个ForwardIterator的值。 |
| remove: | 删除指定范围内所有等于指定元素的元素。注意，该函数不是真正删除函数。内置函数不适合使用remove和remove_if函数。 |
| remove_copy: | 将所有不匹配元素复制到一个制定容器，返回OutputIterator指向被拷贝的末元素的下一个位置。 |
| remove_if: | 删除指定范围内输入操作结果为true的所有元素。 |
| remove_copy_if: | 将所有不匹配元素拷贝到一个指定容器。 |
| replace: | 将指定范围内所有等于vold的元素都用vnew代替。 |
| replace_copy: | 与replace类似，不过将结果写入另一个容器。 |
| replace_if: | 将指定范围内所有操作结果为true的元素用新值代替。 |
| replace_copy_if: | 与replace_if，不过将结果写入另一个容器。 |
| swap: | 交换存储在两个对象中的值。 |
| swap_range: | 将指定范围内的元素与另一个序列元素值进行交换。 |
| unique: | 清除序列中重复元素，和remove类似，它也不能真正删除元素。重载版本使用自定义比较操作。 |
| unique_copy: | 与unique类似，不过把结果输出到另一个容器。 |

### 排列组合算法

**排列组合算法(2个)：** 提供计算给定集合按一定顺序的所有可能排列组合

| 算法名 | 算法描述 |
| --- | --- |
| next_permutation: | 取出当前范围内的排列，并重新排序为下一个排列。重载版本使用自定义的比较操作。 |
| prev_permutation: | 取出指定范围内的序列并将它重新排序为上一个序列。如果不存在上一个序列则返回false。重载版本使用自定义的比较操作。 |

### 算术算法

**算术算法(4个)**

| 算法名 | 算法描述 |
| --- | --- |
| accumulate: | iterator对标识的序列段元素之和，加到一个由val指定的初始值上。重载版本不再做加法，而是传进来的二元操作符被应用到元素上。 |
| partial_sum: | 创建一个新序列，其中每个元素值代表指定范围内该位置前所有元素之和。重载版本使用自定义操作代替加法。 |
| inner_product: | 对两个序列做内积(对应元素相乘，再求和)并将内积加到一个输入的初始值上。重载版本使用用户定义的操作。 |
| adjacent_difference: | 创建一个新序列，新序列中每个新值代表当前元素与上一个元素的差。重载版本用指定二元操作计算相邻元素的差。 |

### 生成和异变算法

**生成和异变算法(6个)**

| 算法名 | 算法描述 |
| --- | --- |
| fill: | 将输入值赋给标志范围内的所有元素。 |
| fill_n: | 将输入值赋给first到first+n范围内的所有元素。 |
| for_each: | 用指定函数依次对指定范围内所有元素进行迭代访问，返回所指定的函数类型。该函数不得修改序列中的元素。 |
| generate: | 连续调用输入的函数来填充指定的范围。 |
| generate_n: | 与generate函数类似，填充从指定iterator开始的n个元素。 |
| transform: | 将输入的操作作用与指定范围内的每个元素，并产生一个新的序列。重载版本将操作作用在一对元素上，另外一个元素来自输入的另外一个序列。结果输出到指定容器。 |

### 关系算法

**关系算法(8个)**

| 算法名 | 算法描述 |
| --- | --- |
| equal: | 如果两个序列在标志范围内元素都相等，返回true。重载版本使用输入的操作符代替默认的等于操作符。 |
| includes: | 判断第一个指定范围内的所有元素是否都被第二个范围包含，使用底层元素的<操作符，成功返回true。重载版本使用用户输入的函数。 |
| lexicographical_compare | 比较两个序列。重载版本使用用户自定义比较操作。 |
| max: | 返回两个元素中较大一个。重载版本使用自定义比较操作。 |
| max_element: | 返回一个ForwardIterator，指出序列中最大的元素。重载版本使用自定义比较操作。 |
| min: | 返回两个元素中较小一个。重载版本使用自定义比较操作。 |
| min_element: | 返回一个ForwardIterator，指出序列中最小的元素。重载版本使用自定义比较操作。 |
| mismatch: | 并行比较两个序列，指出第一个不匹配的位置，返回一对iterator，标志第一个不匹配元素位置。如果都匹配，返回每个容器的last。重载版本使用自定义的比较操作。 |

### 集合算法

**集合算法(4个)**

| 算法名 | 算法描述 |
| --- | --- |
| set_union: | 构造一个有序序列，包含两个序列中所有的不重复元素。重载版本使用自定义的比较操作。 |
| set_intersection: | 构造一个有序序列，其中元素在两个序列中都存在。重载版本使用自定义的比较操作。 |
| set_difference: | 构造一个有序序列，该序列仅保留第一个序列中存在的而第二个中不存在的元素。重载版本使用自定义的比较操作。 |
| set_symmetric_difference: | 构造一个有序序列，该序列取两个序列的对称差集(并集-交集) |

### 堆算法

**堆算法(4个)**

| 算法名 | 算法描述 |
| --- | --- |
| make_heap: | 把指定范围内的元素生成一个堆。重载版本使用自定义比较操作。 |
| pop_heap: | 并不真正把最大元素从堆中弹出，而是重新排序堆。它把first和last-1交换，然后重新生成一个堆。可使用容器的back来访问被”弹出”的元素或者使用pop_back进行真正的删除。重载版本使用自定义的比较操作。 |
| push_heap: | 假设first到last-1是一个有效堆，要被加入到堆的元素存放在位置last-1，重新生成堆。在指向该函数前，必须先把元素插入容器后。重载版本使用指定的比较操作。 |
| sort_heap: | 对指定范围内的序列重新排序，它假设该序列是个有序堆。重载版本使用自定义比较操作。 |



## STL算法
### 排序
参考：http://feihu.me/blog/2014/sgi-std-sort/

#### 快排
在C语言的标准库中，stdlib.h头文件有qsort算法,使用的是快排。然而，快速排序虽然平均复杂度为O(N logN)，却可能由于不当的pivot选择，导致其在最坏情况下复杂度恶化为O(N2)。另外，由于快速排序一般是用递归实现，我们知道递归是一种函数调用，它会有一些额外的开销，比如返回指针、参数压栈、出栈等，在分段很小的情况下，过度的递归会带来过大的额外负荷，从而拉缓排序的速度。

#### 堆排序
#### 插入排序
#### std::sort()
STL中的sort采用的是Introspective Sorting(内省式排序)，是一种混合式排序算法，集合了快排堆排插入排序的优点：
- 在数据量很大时采用正常的快速排序，此时效率为O(NlogN)。
- 一旦分段后的数据量小于某个阈值，就改用插入排序，因为此时这个分段是基本有序的，这时效率可达O(N)。
- 在递归过程中，如果递归层次过深，分割行为有恶化倾向时，它能够自动侦测出来，使用堆排序来处理，在此情况下，使其效率维持在堆排序的O(N logN)，但这又比一开始使用堆排序好。

std::sort适合哪些容器

这么高效的算法，是不是所有的容器都可以使用呢？我们常规数组是否也能使用？我们知道在STL中的容器可以大致分为：

- 序列式容器：vector, list, deque
- 关联式容器：set, map, multiset, multimap
- 配置器容器：queue, stack, priority_queue
- 无序关联式容器：unordered_set, unordered_map, unordered_multiset, unordered_multimap。这些是在C++ 11中引入的
对于所有的关联式容器如map和set，由于它们底层是用红黑树实现，因此已经具有了自动排序功能，不需要std::sort。至于配置器容器，因为它们对出口和入口做了限制，比如说先进先出，先进后出，因此它们也禁止使用排序功能。

由于std::sort算法内部需要去取中间位置元素的值，为了能够让访问元素更迅速，因此它只接受有随机访问迭代器的容器。对于所有的无序关联式容器而言，它们只有前向迭代器，因而无法调用std::sort。但我认为更为重要的是，从它们名称来看，本身就是无序的，它们底层是用哈希表来实现。它们的作用像是字典，为的是根据key快速访问对应的元素，所以对其排序是没有意义的。

剩下的三种序列式容器中，vector和deque拥有随机访问迭代器，因此它们可以使用std::sort排序。而list只有双向迭代器，所以它无法使用std::sort，但好在它提供了自己的sort成员函数。

另外，我们最常使用的数组其实和vector一样，它的指针本质上就是一种迭代器，而且是随机访问迭代器，因此也可以使用std::sort。

>list容器使用的排序方法与<algorithms>中的sort()不同，使用的是归并排序
参见：[std::list::sort 用了什么算法？为什么速度这么快？](https://www.zhihu.com/question/31478115/answer/52104149)

#### std::partial_sort()
部分排序，默认按升序。
```c++
template<class RandomAccessIterator>     
void partial_sort(RandomAccessIterator first, RandomAccessIterator sortEnd, RandomAccessIterator last);
template<class RandomAccessIterator, class BinaryPredicate>
void partial_sort(RandomAccessIterator first, RandomAccessIterator sortEnd, RandomAccessIterator last, BinaryPredicate comp);
```

## 迭代器
根据STL中的分类，iterator包括：
Input Iterator：只能单步向前迭代元素，不允许修改由该类迭代器引用的元素。
Output Iterator：该类迭代器和Input Iterator极其相似，也只能单步向前迭代元素，不同的是该类迭代器对元素只有写的权力。
Forward Iterator：该类迭代器可以在一个正确的区间中进行读写操作，它拥有Input Iterator的所有特性，和Output Iterator的部分特性，以及单步向前迭代元素的能力。
Bidirectional Iterator：该类迭代器是在Forward Iterator的基础上提供了单步向后迭代元素的能力。
Random Access Iterator：该类迭代器能完成上面所有迭代器的工作，它自己独有的特性就是可以像指针那样进行算术计算，而不是仅仅只有单步向前或向后迭代。
    这五类迭代器的从属关系，如下图所示，其中箭头A→B表示，A是B的强化类型，这也说明了如果一个算法要求B，那么A也可以应用于其中。

```
input   output
     \  /
    forward
       |
bidirectional
       |
random access
```

vector 和deque提供的是RandomAccessIterator，list提供的是BidirectionalIterator，set和map提供的 iterators是 ForwardIterator，关于STL中iterator迭代器的操作如下：
说明：每种迭代器均可进行包括表中前一种迭代器可进行的操作。
迭代器操作                      说明
(1)所有迭代器
|p++                              |后置自增迭代器|
|---|---|
|++p                              |前置自增迭代器|
(2)输入迭代器
|*p                                 |复引用迭代器，作为右值|
|---|---|
|p=p1                             |将一个迭代器赋给另一个迭代器|
|p==p1                           |比较迭代器的相等性|
|p!=p1                            |比较迭代器的不等性|
(3)输出迭代器
|*p                                 |复引用迭代器，作为左值|
|---|---|
|p=p1                             |将一个迭代器赋给另一个迭代器|
(4)正向迭代器
提供输入输出迭代器的所有功能
(5)双向迭代器
|--p     |                           前置自减迭代器|
|---|---|
|p--     |                           后置自减迭代器|
(6)随机迭代器
|p+=i                              |将迭代器递增i位|
|---|---|
|p-=i                               |将迭代器递减i位|
|p+i                                |在p位加i位后的迭代器|
|p-i                                 |在p位减i位后的迭代器|
|p[i]                                |返回p位元素偏离i位的元素引用|
|p<p1                             |如果迭代器p的位置在p1前，返回true，否则返回false|
|p<=p1                           |p的位置在p1的前面或同一位置时返回true，否则返回false|
|p>p1                             |如果迭代器p的位置在p1后，返回true，否则返回false|
|p>=p1                           |p的位置在p1的后面或同一位置时返回true，否则返回false|

只有顺序容器和关联容器支持迭代器遍历，各容器支持的迭代器的类别如下：
|容器           |      支持的迭代器类别   |         容器     |          支持的迭代器类别    |        容器   |              支持的迭代器类别
|---|---|---|---|---|---|
|vector|              随机访问|                      deque|              随机访问|                       list|                   双向|
|set|                   双向|                            multiset|            双向|                           map|                 双向|
|multimap|          双向|                             stack|                不支持|                        queue|              不支持|
|priority_queue|   不支持|
参考：
http://www.cnblogs.com/yc_sunniwell/archive/2010/06/25/1764934.html