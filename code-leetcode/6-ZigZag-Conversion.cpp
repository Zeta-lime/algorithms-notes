// version1 zigzag pattern也是循环的，循环的周期为2*numRows-2,先建立一个该周期的index映射表，然后每次进行转换。速度慢，想复杂了。
class Solution
{
  public:
    string convert(string s, int numRows)
    {
        vector<string> v(numRows);
        string str;
        vector<int> index;
        if (numRows == 1)
            return s;
        else
        {
            for (int i = 0; i < numRows; ++i)
                index.push_back(i);
            for (int i = 0; i < numRows - 2; ++i)
                index.push_back(numRows - 2 - i);
        }
        for (int i = 0; i < s.length(); ++i)
            v[index[i % (2 * numRows - 2)]].push_back(s[i]);
        for (int i = 0; i < numRows; ++i)
            str += v[i];
        return str;
    }
};

// version2 把行数row想象成兵乓球，在边界0和边界numRows-1间来回运动，只需在两个边界处改变运动方向即可

class Solution
{
  public:
    string convert(string s, int numRows)
    {
        vector<string> v(numRows);
        string str;
        if (numRows <= 1)
            return s;
        for (int row = 0, i = 0, step = 1; i < s.length(); ++i)
        {
            v[row].push_back(s[i]);
            if (row == 0)
                step = 1;
            if (row == numRows - 1)
                step = -1;
            row += step;
        }
        for (int i = 0; i < numRows; i++)
        {
            str.append(v[i]);
        }
        return str;
    }
};