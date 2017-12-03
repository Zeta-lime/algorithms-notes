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