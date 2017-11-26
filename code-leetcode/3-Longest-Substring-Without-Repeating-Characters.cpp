// Given a string, find the length of the longest substring without repeating characters.

// Examples:

// Given "abcabcbb", the answer is "abc", which the length is 3.

// Given "bbbbb", the answer is "b", with the length of 1.

// Given "pwwkew", the answer is "wke", with the length of 3. Note that the answer must be a substring, "pwke" is a subsequence and not a substring.

//version 1.0 very slow **(266 ms)**
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

//version1.1 index i to j - 1 is already checked to have no duplicate characters, it is unnecessary to check again in next loop **(38 ms)**
class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0;
        unordered_set<char> char_set;
        for (int i = 0, j = 0; i < s.length(); ++i)
        {
            if (ans >= s.length() - i)
                return ans;
            while (char_set.insert(s[j]).second && j < s.length())
            {
                ++j;
            }
            ans = ans < (j - i) ? (j - i) : ans;
            char_set.erase(s[i]);
        }
        return ans;
    }
};

//version1.2 using HashSet as a sliding window, checking if next character is already in the current substring **(39ms)**

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0;
        int s_length = s.size();
        unordered_set<char> char_set;
        int i = 0, j = 0;
        while (i < s_length && j < s_length)
        {
            if (ans >= s_length - i)
                return ans;
            if (char_set.insert(s[j]).second)
            {
                ++j;
                ans = ans < char_set.size() ? char_set.size() : ans;
            }
            else
                char_set.erase(s[i++]);
        }
        return ans;
    }
};

//version1.3 sliding windows optimized The above solution requires at most 2n steps. In fact, it could be optimized to require only n steps. Instead of using a set to tell if a character exists or not, we could define a mapping of the characters to its index. Then we can skip the characters immediately when we found a repeated character. The reason is that if s[j] have a duplicate in the range [i, j) with index j' ​​ , we don't need to increase i little by little. We can skip all the elements in the range [i, j'] and let i to be j' + 1 directly. **(29 ms)**

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0, s_length = s.size();
        unordered_map<char, int> charint_map;
        for (int i = 0, j = 0; j < s_length; j++)
        {
            if (charint_map.find(s[j]) != charint_map.end())
            {
                i = max(charint_map[s[j]] + 1, i);
            }
            ans = max(ans, j - i + 1);
            charint_map[s[j]] = j;
        }
        return ans;
    }
};

// vesion1.4
// The previous implements all have no assumption on the charset of the string s.
// If we know that the charset is rather small, we can replace the Map with an integer array as direct access table.
// Commonly used tables are:
// int[26] for Letters 'a' - 'z' or 'A' - 'Z'
// int[128] for ASCII
// int[256] for Extended ASCII

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        vector<int> charIndex(256, -1);
        int longest = 0;
        int m = -1;
        for (int i = 0; i < s.length(); i++)
        {
            m = max(charIndex[s[i]] + 1, m);
            longest = max(longest, i - m + 1);
            charIndex[s[i]] = i;
        }
        return longest;
    }
};

class Solution
{
  public:
    int lengthOfLongestSubstring(string s)
    {
        int ans = 0, s_length = s.size();
        int string_array[128] = {};
        for (int j = 0, i = 0; j < s_length; j++)
        {
            // i = max(string_array[s[j]] + 1, i);
            // ans = max(ans, j - i + 1);
            // string_array[s[j]] = j;  
            //it will make mistake when input is a single character.
            i = max(string_array[s[j]], i);
            ans = max(ans, j - i + 1);
            string_array[s[j]] = j + 1;
        }
        return ans;
    }
};