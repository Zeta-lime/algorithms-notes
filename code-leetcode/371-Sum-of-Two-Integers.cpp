// Calculate the sum of two integers a and b, but you are not allowed to use the operator + and -.

// Example:
// Given a = 1 and b = 2, return 3.

// Credits:
// Special thanks to @fujiaozhu for adding this problem and creating all test cases.

class Solution {
public:
    int getSum(int a, int b) {
        while(b != 0){
            int t = a;
            a = t ^ b;
            b = (t & b) << 1;
        }
        return a ^ b;
    }
};