#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> res;
        if(nums.size() < 2)
            return res;
        unordered_map<int,int> stat;
        for(int i = 0; i < nums.size(); i++){
            int temp = target - nums[i];
            if(stat.find(temp) != stat.end()){
                res.push_back(stat[temp]);
                res.push_back(i);
            }
            else
                stat[nums[i]] = i;
        }
        
        return res;
    }
};
// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         for (int i=0;i<nums.size();++i){
//             // int rest = target-nums[i];
//             // auto iter=find(nums.begin(),nums.end(),rest);
//             // if (iter!=nums.end()&&iter!=(nums.begin()+i))
//             //     return vector<int> {i,distance(nums.begin(),iter)};
//             for(int j=i+1;j<nums.size();++j){
//                 if(nums[i]+nums[j]==target)
//                     return vector<int> {i,j};
//             }
//         }
//     }
// };

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

int stringToInteger(string input) {
    return stoi(input);
}

string integerVectorToString(vector<int> list, int length = -1) {
    if (length == -1) {
        length = list.size();
    }

    if (length == 0) {
        return "[]";
    }

    string result;
    for(int index = 0; index < length; index++) {
        int number = list[index];
        result += to_string(number) + ", ";
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> nums = stringToIntegerVector(line);
        getline(cin, line);
        int target = stringToInteger(line);
        
        vector<int> ret = Solution().twoSum(nums, target);

        string out = integerVectorToString(ret);
        cout << out << endl;
    }
    system("pause");
    return 0;
}


// class Solution {
// public:
//     vector<int> twoSum(vector<int>& nums, int target) {
//         unordered_map<int, int>m;
//         vector<int> res;
//         for(int i = 0; i < nums.size(); i++){
//             if(m.find(target - nums[i]) != m.end()){
//                 res.push_back(i);
//                 res.push_back(m[target - nums[i]]);
//                 return res;
//             }
//             m[nums[i]] = i;
//         }
//         return res;
//     }
// };
