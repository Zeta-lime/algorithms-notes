# 第五章 算法
---
##
### 全排序(permutation)(leetcode31\46\47)
- 字典序法，求next_permutation(STL里采用的方法)


- 递归法
    - 输入向量中没有重复的元素
    思路：
    ![全排序递归法](/assets/全排序递归法.png)
    代码：
```
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

- 康托(cantor)编码与康托展开