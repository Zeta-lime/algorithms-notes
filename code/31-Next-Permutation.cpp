// Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

//                             If such arrangement is not possible,
//     it must rearrange it as the lowest possible order(ie, sorted in ascending order).

//         The replacement must be in
//         - place,
//     do not allocate extra memory.

//             Here are some examples.Inputs are in the left
//             - hand column
//         and its corresponding outputs are in the right - hand column.1,
//     2, 3 → 1, 3, 2 3, 2, 1 → 1, 2, 3 1, 1, 5 → 1, 5, 1
class Solution
{
    public:
    void nextPermutation(vector<int> &nums)
    {
        auto riter_selcet1 = find1(nums.rbegin(),nums.rend());
        auto riter_select2 = find_if(nums.rbegin(),riter_select1,bind2nd(isbigger2, *iter_select1));
        swap(*riter_select1,*riter_select2);
        reverse(riter_select1.base()+1,nums.end());
    }
    private:
    vector<int>::iterator find1(vector<int>::reverse_iterator iter1,vector<int>::reverse_iterator iter2)
    {
        while(*iter1<=*(iter1+1) && iter1!=iter2-1)
        ++iter1;
        return iter1+1
    }
    bool isbigger(int n1,int n2)
    {
        return n1>n2;
    }
};