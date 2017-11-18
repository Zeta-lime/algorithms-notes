# 常用的编程TIPS(C++)
--- 
[toc]

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
std::distance(iter1,iter2）
求两个迭代器的间距，正整数

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

## 输入输出
### c风格
printf()\scanf()\getchar()\putchar() //#include <cstdio>
### C++风格
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
### 字符与数字转换
- c风格(a->ascii i->int)
    atoi (表示 ascii to integer)(不是C标准，依赖编译器，后来加入了c98中？)


### how to interpret complex C/C++ declarations
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