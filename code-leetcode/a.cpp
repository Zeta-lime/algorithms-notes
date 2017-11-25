#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> charIndex(256, -1);
        int longest = 0;
        int m = -1;
        for(int i=0;i<s.length();i++)
        {
            m=max(charIndex[s[i]]+1,m);
            charIndex[s[i]] = i; 
            longest = max(longest, i-m+1);
        
        }
    return longest;
}
};

// string stringToString(string input) {
//     assert(input.length() >= 2);
//     string result;
//     for (int i = 1; i < input.length() -1; i++) {
//         char currentChar = input[i];
//         if (input[i] == '\\') {
//             char nextChar = input[i+1];
//             switch (nextChar) {
//                 case '\"': result.push_back('\"'); break;
//                 case '/' : result.push_back('/'); break;
//                 case '\\': result.push_back('\\'); break;
//                 case 'b' : result.push_back('\b'); break;
//                 case 'f' : result.push_back('\f'); break;
//                 case 'r' : result.push_back('\r'); break;
//                 case 'n' : result.push_back('\n'); break;
//                 case 't' : result.push_back('\t'); break;
//                 default: break;
//             }
//             i++;
//         } else {
//           result.push_back(currentChar);
//         }
//     }
//     return result;
// }

int main() {
    string line;
    // while (getline(cin, line)) {
    //     string s = stringToString(line);
        string s = "abcabcbb";
        int ret = Solution().lengthOfLongestSubstring(s);

        string out = to_string(ret);
        cout << out << endl;
    // }
    return 0;
}