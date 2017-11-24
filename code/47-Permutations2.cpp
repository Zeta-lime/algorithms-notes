// Given a collection of numbers that might contain duplicates, return all possible unique permutations.

//     For example,
//     [ 1, 1, 2 ] have the following unique permutations :
//     [
//         [ 1, 1, 2 ],
//         [ 1, 2, 1 ],
//         [ 2, 1, 1 ]
//     ]
// 递归法，交换前加入判断

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
                auto iter2 = find(iter+1,nums0.end(),*iter);
                if(iter2 != nums0.end())
                    continue;
                swap(*iter, *iter1);
                pmtu_recursion(results, nums0, iter1 + 1);
                swap(*iter, *iter1);
            }
        }
    }
};