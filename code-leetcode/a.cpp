#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

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

int main()
{
    vector<int> v {0,-4,-1,-4,-2,-3,2};
    vector<vector<int>> result;
    Solution s;
    result=s.threeSum(v);
    for(auto i:result)
    {
        for(auto j:i)
        {
            cout<<j<<" ";
        }
        cout<<endl;
    }
    system("pause");
    
}