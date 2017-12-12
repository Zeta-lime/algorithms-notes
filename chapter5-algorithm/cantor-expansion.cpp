//康托展开

class CantorExp
{
  public:
    int cantorencode(vector<int> nums)
    {
        int cantornum = 0;
        int len = nums.size();
        for (int i = 0; i < len; ++i)
        {
            int cout = 0;
            for (int j = i + 1; j < len; ++j)
            {
                if (nums[j] < nums[i])
                    ++cout;
            }
            cantornum += cout * factorial(len - i - 1);
        }
        return cantornum;
    }
    vector<int> cantordecode(vector<int> nums, int k)
    {
        vector<int> tempvect;
        int len = nums.size();

        for (int i = len - 1; i >= 0; --i)
        {
            int d = factorial(i);
            int index = k / d;
            k %= d;
            tempvect.push_back(nums[index]);
            nums.erase(nums.begin() + index);
        }
        return tempvect;
    }

  private:
    static const int FAC[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    int factorial(int n)
    {
        // if (n == 0 || n == 1)
        //     return 1;
        // else
        //     return n * factorial(n - 1);
        return FAC[n];
    }
};