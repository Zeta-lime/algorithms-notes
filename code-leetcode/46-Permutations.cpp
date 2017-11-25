// Given a collection of distinct numbers, return all possible permutations.

//     For example,
//     [ 1, 2, 3 ] have the following permutations :
//     [
//         [ 1, 2, 3 ],
//         [ 1, 3, 2 ],
//         [ 2, 1, 3 ],
//         [ 2, 3, 1 ],
//         [ 3, 1, 2 ],
//         [ 3, 2, 1 ]
//     ]
// 用递归法如下
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
                swap(*iter, *iter1);
            }
        }
    }
};
