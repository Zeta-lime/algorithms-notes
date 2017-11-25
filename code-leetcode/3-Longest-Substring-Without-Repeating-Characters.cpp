// Given a string, find the length of the longest substring without repeating characters.

// Examples:

// Given "abcabcbb", the answer is "abc", which the length is 3.

// Given "bbbbb", the answer is "b", with the length of 1.

// Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0;
            unordered_set<char> char_set;
        for (int i = 0; i < s.length(); ++i)
        {
            if (ans > s.length() - i)
                return ans;
            int j = i, temp = 0;
            while (char_set.insert(s[j]).second && j < s.length())
            {
                ++temp;
                ++j;
            }
            char_set.clear();
            ans = ans < temp ? temp : ans;
        }
        return ans;
    }
};