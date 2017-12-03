http://www-igm.univ-mlv.fr/~lecroq/string/index.html
## KMP字符串匹配算法
算法复杂度O(n+m)
参考：
1. http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html
2. http://blog.csdn.net/yutianzuijin/article/details/11954939

在字符串T（text）中匹配字符串P（pattern）
算法要点：
- 将T固定,从左到右移动P逐字符匹配，到第P[i]个字符与T[j]不匹配时，不是仅仅简单的右移一位重复开始，而是尽可能地多移动。
- 这种想法之所以可以实现，在于当第P[i]位不匹配时，前i位(P[0]~P[i-1])是匹配的，如果这i位子串的前缀和后缀中有公共字符串,最长的公共字符串长度为m[i],则可以最多向右移动i-m[i]位，而不是只移动一位。且由于前缀后缀已经匹配，重新开始比较的位置仍是T[j]。
- m[i]通常称为next数组，这个数组只与pattern有关。
- 那么**关键在于如何求next[i]**
    假设我们现在已经求得next[0]、next[1]、……next[i-1]，分别表示长度为1到i的字符串的前缀和后缀最大公共长度，现在要求next[i]。由下图我们可以看到，如果P[i]和P[next[i]]的两个字符相同，则next[i]等于next[i-1]+1。如果两个位置的字符不相同，我们可以将长度为next[i]的字符串继续分割，其前后缀最大公共长度为next[next[i]]，然后比较P[next[next[i]]]与P[i]，如果位置next[next[i]]和位置i的字符相同，则next[i]就等于next[next[i]]+1。如果不相等，就可以继续分割长度为next[next[i]]的字符串，直到next[next[...next[i]]]=0,比较P[0]与P[i],相同next[i]=0+1=1,不相同，next[i]=0。
    ![20130924000843031](/assets/20130924000843031.jpg)

## BM(Boyer-Moore)算法
http://www.cnblogs.com/gaochundong/p/boyer_moore_string_matching_algorithm.html
mooer的个人网站 http://www.cs.utexas.edu/users/moore/welcome.html
http://www.iti.fh-flensburg.de/lang/algorithmen/pattern/bmen.htm
http://www.cnblogs.com/lanxuezaipiao/p/3452579.html
http://blog.jobbole.com/52830/
https://www.61mon.com/index.php/archives/210/
http://igm.univ-mlv.fr/~lecroq/string/node14.html
good suffix规则比较复杂，，参考[zblock算法](http://yaowhat.com/2014/08/08/week-str-zblock.html)，也可以考虑用Bruce-force法求解规则
## Boyer-Moore-Horspool算法
http://www.mathcs.emory.edu/~cheung/Courses/323/Syllabus/Text/Matching-Boyer-Moore2.html
简化版的BM算法，只有bad character rule，优化了坏字符规则，分P中不存在T[j],P中存在T[j]且位置在i后，存在且在i前
## Sunday算法
Sunday算法由Daniel M.Sunday在1990年提出，它的思想跟BM算法很相似：
只不过Sunday算法是从前往后匹配，在匹配失败时关注的是文本串中参加匹配的最末位字符的下一位字符。
如果该字符没有在模式串中出现则直接跳过，即移动位数 = 匹配串长度 + 1；
否则，其移动位数 = 模式串中最右端的该字符到末尾的距离+1。
http://blog.csdn.net/v_july_v/article/details/7041827