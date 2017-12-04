// Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

// Note: The solution set must not contain duplicate triplets.

// For example, given array S = [-1, 0, 1, 2, -1, -4],

// A solution set is:
// [
//   [-1, 0, 1],
//   [-1, -1, 2]
// ]

// wrong version
// class Solution
// {
//   public:
//     vector<vector<int>> threeSum(vector<int> &nums)
//     {
//         vector<vector<int>> result;
//         if (nums.size() < 3)
//             return result;
//         if (nums.size() == 3)
//         {
//             if (nums[0] + nums[1] + nums[2] == 0)
//                 result.push_back(nums);
//             return result;
//         }
//         unordered_set<int> hashset;
//         for (int i = 0; i < nums.size() - 2; ++i)
//         {
//             if (hashset.insert(nums[i]).second)
//             {
//                 vector<vector<int>> temp = twoSum(nums.begin() + i + 1, nums.end(), -nums[i]);
//                 if (!temp.empty())
//                     for (int i = 0; i < temp.size(); ++i)
//                         result.push_back(temp[i].insert(temp[i].begin(), sums[i]));
//             }
//         }
//         return result;
//     }
//     vector<vector<int>> twoSum(vector<int>::iterator &t1, vector<int>::iterator &t2, int num)
//     {
//         unordered_set<int> hashset;
//         vector<vector<int>> result;
//         for (auto it = t1; it != t2; ++it)
//         {
//             if (hashset.find(*it) != hashset.end())
//             {
//                 if (hashset.find(num - (*it)) != hashset.end())
//                 {
//                     vector<int> temp
//                         temp.push_back(*it);
//                     temp.push_back(num - (*it));
//                     result.push_back(temp);
//                 }
//             }
//             else
//                 hashset.insert(*it);
//         }
//         return result
//     }
// };

// left+mid+right=0 ，循环left 将mid、right左右夹逼
class Solution
{
  public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        vector<vector<int>> result;
        int len = nums.size();
        if (len < 3)
            return result;
        sort(nums.begin(), nums.end());
        for (int left = 0, right, mid; left < len - 2; left++)
        {
            if (left > 0 && nums[left] == nums[left - 1])
                continue;
            mid = left + 1;
            right = len - 1;
            while (mid < right)
            {
                if (nums[left] + nums[mid] + nums[right] == 0)
                    result.push_back({nums[left], nums[mid++], nums[right--]});
                else if (nums[left] + nums[mid] + nums[right] < 0)
                    mid++;
                else
                    right--;
            }
        }
        result.erase(unique(result.begin(), result.end()), result.end());
        return result;
    }
};