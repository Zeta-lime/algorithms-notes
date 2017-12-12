// Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. You may assume that each input would have exactly one solution.

//     For example, given array S = {-1 2 1 -4}, and target = 1.

//     The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).


// 采用与3sum相似的左右夹逼的策略
// 一个疑问是这种策略能让diff=abs(currentsum-target)收敛吗？答案是不能，但是不会遍历所有的情形，左右夹逼的时候有些情况会被排除

class Solution
{
  public:
    int threeSumClosest(vector<int> &nums, int target)
    {
        int ans;
        int diff = INT_MAX;
        int len = nums.size();
        if (len == 3)
            return accumulate(nums.begin(), nums.end(), 0);
        sort(nums.begin(), nums.end());
        for (int left = 0, right, mid; left < len - 2; left++)
        {
            mid = left + 1;
            right = len - 1;  //mid和right每次循环都会变，别写到for里面去了
            while (mid < right)
            {
                int sum = nums[left] + nums[mid] + nums[right];
                int newdiff = sum - target;
                if (newdiff == 0)
                    return target;
                if (abs(newdiff) < diff)
                {
                    diff = abs(newdiff);
                    ans = sum;
                }
                if (newdiff < 0)
                {
                    mid++;
                }
                else
                {
                    right--;
                }
            }
        }
        return ans;
    }
};