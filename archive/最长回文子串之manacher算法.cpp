// http://www.cnblogs.com/grandyang/p/4475985.html
#include <vector>
#include <iostream>
#include <string>

using namespace std;

string Manacher(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0); // 长度数组记录每个位置回文子串长
    int mx = 0, id = 0, resLen = 0, resCenter = 0; //id 是已知具有最右边界回文字符子串中心, mx为该回文子串右边界位置，resCenter记录最长回文字符子串中心，reslen记录最长回文字符子串半径（以1起始）
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1; //如果i在最右边界回文子串内，先利用有效信息
        while (t[i + p[i]] == t[i - p[i]]) ++p[i]; //朴素扩展
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }    //新的最右边界更新
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        } //记录结果
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1); //substr方法产生以第一个参数为起始，长度为第二个参数的子串，这里的转换基于s与s的扩展字符串t的对应关系
}

int main() {
    string s1 = "12212";
    cout << Manacher(s1) << endl;
    string s2 = "122122";
    cout << Manacher(s2) << endl;
    string s = "waabwswfd";
    cout << Manacher(s) << endl;
}