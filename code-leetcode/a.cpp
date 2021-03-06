#include <algorithm>
#include <vector>
#include <iostream>
#include <climits>
#include <numeric>

using namespace std;

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
            right = len - 1;
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

int main()
{

    vector<int> nums = {1,2,4,8,16,32,64,128};
    int target = 82;

    int ret = Solution().threeSumClosest(nums, target);
    cout << ret << endl;
    system("pause");
    return 0;
}