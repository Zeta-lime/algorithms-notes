// approach1
class Solution {
public:
    int reverse(int x) {
        int x_abs=abs(x);
        string s =to_string(x_abs);
        for(auto i=s.begin(),j=s.end()-1;i<j;++i,--j)
            swap(*i,*j);
        long res=stol(s);
        if(res>long(INT_MAX))
            return 0;
        return x>=0?int(res):int(-res);
    }
};
// approach2
class Solution {
public:
    int reverse(int x) {
        long result = 0;
        while(x) {
            result = result * 10 + x % 10;
            x /= 10;
        };
        if (result > INT_MAX || result < INT_MIN) {
            return 0;
        }
        return (int)result;
    }
};
