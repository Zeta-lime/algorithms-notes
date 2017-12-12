# 第五章 算法
---
## 排序
### 全排序(permutation)(leetcode31\46\47)
- 字典序法，求next_permutation(STL里采用的方法)
思路：
对给定的字符集中的字符组合规定一种排序方式（一般按照ASCII码大小），在此基础上按照顺序依次产生每个排列。
例如字符集{1,2,3},较小的数字较先,这样按字典序生成的全排列是:123,132,213,231,312,321。
给出一个排序后求下一个排序，这就要求下一个与已有排序**有尽可能长的公共前缀，尽可能短的公共后缀**。
设P是{1,2,3...,n}的一个全排列。
P=P~1~P~2~...P~j-1~P~j~P~j+1~...P~k-1~P~k~P~k+1~...P~n~ , 
j=max{i|P~i~<P~i+1~}, k=max{i|P~i~>P~j~} ,
交换P~j~，P~k~，
将P~j+1~...P~n~翻转，
即得到P的下一个全排序
>例子:839647521的下一个排列.
从最右开始,找到第一个比右边小的数字4(因为4<7，而7>5>2>1),再从最右开始,找到4右边比4大的数字5(因为4>2>1而4<5),交换4、5,此时5右边为7421,倒置为1247,即得下一个排列:839651247.
该方法支持存在重复字符的情况，且在C++ STL中被采用。

代码：
```c++
class Solution
{
public:
	void nextPermutation(vector<int> &nums)
	{
		auto riter_select1 = nums.rbegin() + 1;
		while (riter_select1 != nums.rend() && *riter_select1 >= *(riter_select1 - 1))
			++riter_select1;
		if (riter_select1 == nums.rend())
		{
			reverse(nums.begin(), nums.end());
			return;
		}
		auto riter_select2 = nums.rbegin();
		while (*riter_select2 <= *riter_select1&&riter_select2 != riter_select1)
			++riter_select2;
		swap(*riter_select1, *riter_select2);
		reverse(nums.rbegin(),riter_select1);
	}
};
```


- 递归法
    - 输入向量中没有重复的元素
    思路：
    ![全排序递归法](/assets/全排序递归法.png)
    代码：
```c++
class Solution
{
  public:
    vector<vector<int>> permute(vector<int> nums)
    {
        vector<vector<int>> results;
        auto iter1 = nums.begin();
        pmt_recursion(results, nums, iter1);
        return results;
    }

  private:
    void pmt_recursion(vector<vector<int>> &results, vector<int> &nums0, vector<int>::iterator iter1)
    {
        if (iter1 == nums0.end() - 1)
            results.push_back(nums0);
        else
        {
            for (auto iter = iter1; iter != nums0.end(); ++iter)
            {
                swap(*iter, *iter1);
                pmt_recursion(results, nums0, iter1 + 1);
                swap(*iter, *iter1); //注意到这里需要交换回来
            }
        }
    }
};
```
注意：在交换递归后需要交换回来，比如a~1~与a~2~交换后，for的下个循环是a~1~与a~3~交换，故需要将a~1~与a~2~再交换回来。
    - 输入向量中有重复的元素
    思路：在上面的基础上，在每次交换前做一次检查，检查被交换的元素的后面是否有与该元素一样的，如果有就跳过本次for循环。
    代码：
```c++
    class Solution
{
  public:
    vector<vector<int>> permuteUnique(vector<int> nums)
    {
        vector<vector<int>> results;
        auto iter1 = nums.begin();
        pmtu_recursion(results, nums, iter1);
        return results;
    }

  private:
    void pmtu_recursion(vector<vector<int>> &results, vector<int> &nums0, vector<int>::iterator iter1)
    {
        if (iter1 == nums0.end() - 1)
            results.push_back(nums0);
        else
        {
            for (auto iter = iter1; iter != nums0.end(); ++iter)
            {
                auto iter2 = find(iter+1,nums0.end(),*iter); //检查是否有重复元素
                if(iter2 != nums0.end())
                    continue;
                swap(*iter, *iter1);
                pmtu_recursion(results, nums0, iter1 + 1);
                swap(*iter, *iter1);
            }
        }
    }
};
```

- 康托(cantor)编码与康托展开

康托展开是一个全排列到一个自然数的双射，常用于构建hash表时的空间压缩。

公式为:

```
X = a[n - 1] * (n - 1)! + a[n - 2] * (n - 2)! + ... + a[0] * 0!,
其中, a[i]为整数，并且0 <= a[i] <= i, 0 <= i < n, 表示当前未出现的的元素
中排第几个。
```
比如31254, 

* 在3后面比3小的有2个，分别为1,2
* 在1后面比1小的有0个
* 在2后面比2小的有0个
* 在5后面比5小的有1个，为4
* 在4后面比4小的有0个

因此a数组序列为2 0 0 1 0
```
X = 2 * 4! + 0 * 3! + 0 * 2! + 1 * 1! + 0 * 0!
  = 2 * 24 + 1
  = 49
```
既然是双射关系那一定可以反推出来31254这个序列。
首先我们需要推出a序列。

* 49 / 4! = 2,因此a[4] = 2, 此时49 % 4! = 1, 
* 1 / 3! = 1 / 2! = 0,因此a[3] = a[2] = 0,
* 而 1 / 1 = 1, 因此a[1] = 1,1 % 1! = 0,
* 0 / 0! = 0,因此a[0] = 0
* 所以得到a数组为2 0 0 1 0

再由a数组推出序列，根据a数组的意义反推。

* a[4] = 2, 表示它在1 2 3 4 5 序列中比它小的有2个，即它自己排第3，它等于3
* a[3] = 0, 表示它在1 2 4 5序列中比它小的有0个，即最小数，等于1
* a[2] = 0, 表示它在2 4 5 中最小，等于2
* a[1] = 1, 表示它在4 5中比它小的有一个，即排第2,等于5
* a[0] = 0, 表示它在4中最小，只能是4

因此序列为3 1 2 5 4


一个直观的应用就是给定一个自然数集合和一个序列，求这个序列中按从小到大的顺序
排第几个?

比如1 2 3 4 5, 3 1 2 5 4比它小的序列有49个，即它排第50

另一个应用就是逆推第K个排列是多少，比如第50个全排列是多少？则首先减1得到49,
再反推即可得到3 1 2 5 4

另外在保存一个序列，我们可能需要开一个数组，如果能够把它映射成一个自然数，
则只需要保存一个整数，大大压缩空间.



计算包括编码（根据序列求对应的自然数）和解码（康托展开）。

    - 编码
```c
static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
int cantor(int *a, int n)
{
	assert(n < 10);
	int x = 0;
	for (int i = 0; i < n; ++i) {
		int smaller = 0;
		for (int j = i + 1; j < n; ++j) {
			if (a[j] < a[i])
				smaller++;
		}
		x += FAC[n - i - 1] * smaller;
	}
	return x;
}
```

    -  解码
```c
int decantor(int *a, int n, int k)
{
	int *num = malloc(sizeof(int) * n );
	int len = n;
	for (int i = 0; i < n; ++i)
		num[i] = i + 1;
	int cur = 0;
	for (int i = n - 1; i > 0; --i) {
		int index = k / FAC[i];
		k %= FAC[i];
		a[cur++] = num[index];
		listRemove(num, &len, index);
	}
	a[cur] = num[0];
	free(num);
	return 0;
}
```



### 快排(quick sort)
快排的基本思想却是极其简单的：接收一个数组，挑一个数，然后把比它小的那一摊数放在它的左边，把比它大的那一摊数放在它的右边，然后再对这个数左右两摊数递归的执行快排过程，直到子数组只剩一个数为止。
参考：
1. http://blog.csdn.net/morewindows/article/details/6684558
2. http://www.cnblogs.com/figure9/archive/2010/12/10/1902711.html

### 堆排序
调整的堆的sift算法

### 归并排序
将带排序的集合分化成细小的子集，将每个子集分别排序，逐渐归并成大的集合，直到整个集合。由于是从局部到整体排序，可用于数据量大内存有限制的情景下。
另外设计程序时可递归也可以非递归进行

## 查找
### 树表查找
二叉排序树->RB-tree红黑树->平衡二叉树(AVL树)
对应STL中的<set><multiset><map><multimap>都是基于红黑树的数据结构实现的，'multi'在于允许key重复。

### 散列表
hash表（这是一种数据结构）：根据key，通过hash函数计算散列值制成的表，hash的英文意思即为弄散。
vector顺序储存，随机读取，复杂度O（1），但是插入删除复杂度O(n)。
list双向链表，随机插入删除，复杂度O(1)，但是查找要从头遍历，复杂度O(n)。
hash表正是融合了两者的思路，现将key通过哈希函数得到散列值，根据散列值制成vector，相同的散列值产生冲突，通过list将冲突值制成链表得到解决（拉链法），这样插入删除快，查找也快。
`hash_set`、 `hash_map`就是基于以上方式，不过STL中称为<unorder_set><unorder_multiset><unoder_map><unoder_multimap>



## 遍历
### 深度优先（DFS）和广度优先（BFS）
### 前序遍历、中序遍历、后序遍历

##
### GCD最大公约数 LCM最小公倍数
辗转相除法， 又名欧几里德算法（Euclidean algorithm），是求最大公约数的一种方法。它的具体做法是：用较小数除较大数，再用出现的余数（第一余数）去除除数，再用出现的余数（第二余数）去除第一余数，如此反复，直到最后余数是0为止。如果是求两个数的最大公约数，那么最后的除数就是这两个数的最大公约数。
c++
```c++
template < typename T >
T GCD(T a, T b) {
	if(b) while((a %= b) && (b %= a));
	return a + b;   //a,b中一个为0，一个为gcd
}
template < typename T >
T LCM(T a, T b) {
	return a * b / GCD(a, b);
}
```

python
```python
GCD = lambda a, b: (GCD(b, a % b) if a % b else b)
```

## 分治
### 分割时遇到奇偶不定的解决办法(leetcode4)
首先分析一个数组的中位数(median)如何表示，比如A[0],A[1],...,A[i]...A[m-1]。
数组的长度不确定奇偶，将**数组A的每一个元素复制**一次，得到数组A'=A[0],A[0],A[1],A[1],...A[m-1],A[m-1].**数组A'的长度2m为偶数，且必定与A具有相同的中位数**。数组A'的中位数=`(A'[(m-1)]+A'[m])/2`,而A'[x]=A[x/2].所以median(A)=`(A[(m-1)/2]+A[m/2])/2`。

接下来看A与B= B[0],B[1],...B[j]...B[n]两个数组的中位数，两个数组长度之和为m+n，由上述分析可知，中位数应该是AB[(m+n-1)/2],与AB[(m+n)/2]两个数的平均。
分别划分A、B两个数组，
          分割思路：AB[(m+n-1)/2]  |  AB[(m+n)/2]
          leftpart                |        rightpart
           A[0], A[1], ..., A[i]  |  A[i+1], ..., A[m-1]
           B[0], B[1], ..., B[j]  |  B[j+1], ..., B[n-1]

分割线在中位数处时，`i+1+j+1=(m+n-1)/2+1, j=(m+n-1)/2-1-i`，为保证j属于0到n-1,i搜寻起点为begin=max(`(m+n-1)/2-n`,0),终点end=min(`m-1`,`(m+n-1)/2-1`).
使用二分查找，令i=(begin+end)/2,开始搜寻
whiles(begin<end)
i=(begin+end)/2,j=(m+n-1)/2-1-i;
否则，
1. if A[i]>B[j+1],表明i取值偏大，继续在左边搜索，begin=begin, end=i-1;
2. else B[j]>A[i+1],表明i取值偏小，继续在右边搜索，begin=i+1, end=end;
3. else break;

结束时若i=0 或者 m,出现问题了，需要引入`INT_MIN`,`INT_MAX`平衡


