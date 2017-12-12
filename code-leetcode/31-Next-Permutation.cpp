
// Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

// If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).

// The replacement must be in-place, do not allocate extra memory.

// Here are some examples. Inputs are in the left-hand column and its corresponding outputs are in the right-hand column.
// 1,2,3 → 1,3,2
// 3,2,1 → 1,2,3
// 1,1,5 → 1,5,1

//字典序法

class Solution
{
  public:
	void nextPermutation(vector<int> &nums)
	{
		auto riter_select1 = nums.rbegin() + 1;
		while (riter_select1 != nums.rend() && *riter_select1 >= *(riter_select1 - 1)) //两个判断不能交换位置，否则nums的size为1时引发错误
			++riter_select1;
		if (riter_select1 == nums.rend()) //若输入字典序已经是最大，反转输出最小字典序
		{
			reverse(nums.begin(), nums.end());
			return;
		}
		auto riter_select2 = nums.rbegin();
		while (*riter_select2 <= *riter_select1 && riter_select2 != riter_select1)
			++riter_select2;
		swap(*riter_select1, *riter_select2);
		reverse(nums.rbegin(), riter_select1);
	}
};