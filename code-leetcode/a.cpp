#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <string>
using namespace std;

class Solution
{
  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size(), len2 = nums2.size(), len3 = (len1 + len2) / 2 + 1;
        int i = 0, j = 0;
        vector<int> nums3;
        while (i < len1 && j < len2 && i+j < len3)
        {
            if (nums1[i] < nums2[j])
                nums3.push_back(nums1[i++]);
            else
                nums3.push_back(nums2[j++]);
        }
        if (i < len1)
            while (i+j < len3)
                nums3.push_back(nums1[i++]);
        else
            while (i+j < len3)
                nums3.push_back(nums2[j++]);
        return (len1 + len2) % 2 ? static_cast<double>(nums3[len3 - 1]) : (nums3[len3 - 1] + nums3[len3 - 2]) / 2.0;
    }
};

// void trimLeftTrailingSpaces(string &input) {
//     input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
//         return !isspace(ch);
//     }));
// }

// void trimRightTrailingSpaces(string &input) {
//     input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
//         return !isspace(ch);
//     }).base(), input.end());
// }

// vector<int> stringToIntegerVector(string input) {
//     vector<int> output;
//     trimLeftTrailingSpaces(input);
//     trimRightTrailingSpaces(input);
//     input = input.substr(1, input.length() - 2);
//     stringstream ss;
//     ss.str(input);
//     string item;
//     char delim = ',';
//     while (getline(ss, item, delim)) {
//         output.push_back(stoi(item));
//     }
//     return output;
// }

int main() {
    string line;
    // while (getline(cin, line)) {
        // vector<int> nums1 = stringToIntegerVector(line);
        // getline(cin, line);
        // vector<int> nums2 = stringToIntegerVector(line);
        vector<int> nums1 = {1,3};
        vector<int> nums2 = {2};
        double ret = Solution().findMedianSortedArrays(nums1, nums2);

        string out = to_string(ret);
        cout << out << endl;
        system("pause");
    // }
    return 0;
}