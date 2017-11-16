// Implement pow(x, n).

// Example 1:

// Input: 2.00000, 10
// Output: 1024.00000
// Example 2:

// Input: 2.10000, 3
// Output: 9.26100
#include <iostream>
#include <cmath>
using namespace std;
class Solution
{
  public:
    double myPow(double x, int n)
    {
        unsigned n_pos = abs((double)n); //in case of n=INT_MIN,the abs of n overflow
        double result = 1;
        for (; n_pos; x *= x, n_pos >>= 1)
        {
            if (n_pos & 1)
                result *= x;
        }
        return (n < 0) ? (1.0 / result) : result;
    }
};

/*
Consider the binary representation of n. For example, if it is "10001011", then x^n = x^(1+2+8+128) = x^1 * x^2 * x^8 * x^128. Thus, we don't want to loop n times to calculate x^n. To speed up, we loop through each bit, if the i-th bit is 1, then we add x^(1 << i) to the result. Since (1 << i) is a power of 2, x^(1<<(i+1)) = square(x^(1<<i)). The loop executes for a maximum of log(n) times.
*/

int main()
{
    double x = 2.0;
    int n = 10;
    double result = 0;
    Solution s;
    result = s.myPow(x, n);
    cout << "result:" << result << endl;
    system("pause");
    return 0;
}