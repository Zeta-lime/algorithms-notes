// There are two sorted arrays nums1 and nums2 of size m and n respectively.

// Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).

// Example 1:
// nums1 = [1, 3]
// nums2 = [2]

// The median is 2.0
// Example 2:
// nums1 = [1, 2]
// nums2 = [3, 4]

// The median is (2 + 3)/2 = 2.5

//version 1.0 nums1和nums2都是有序数组，对他们的合成数列进行排序，再取中位数。

class Solution
{
  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size(), len2 = nums2.size(), len3 = (len1 + len2) / 2 + 1;
        int i = 0, j = 0, k = 0;
        vector<int> nums3;
        while (i < len1 && j < len2 && k < len3)
        {
            if (nums1[i] < nums2[j])
                nums3[k++] = nums1[i++];
            else
                nums3[k++] = nums2[j++];
        }
        if (i < len1)
            while (k < len3)
                nums3[k++] = nums1[i++];
        else
            while (k < len3)
                nums3[k++] = nums2[j++];
        return (len1 + len2) % 2 ? static_cast<double>(nums3[len3 - 1]) : (nums3[len3 - 1] + nums3[len3 - 2]) / 2.0;
    }
};

/*version 2.0 
*           left_part                |        right_part
*           A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
*           B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
*           len(left_part)=len(right_part)
*           max(left_part)≤min(right_part)
*           median= ​(max(left_part)+min(right_part))/​2
*       ​
*       ​​
*       首先，两个数组的合成数组的中位数必定在两个数组各自个中位数之间，
*       min(nums1_mediam,nums2_median)<=SortArray_mediam<=max(nums1_mediam,nums2_median),且nums1和nums2有序，所以寻找范围如下：
*       i>=len1/2,j<=len2/2+1 或者 j>=len2/2,i<=len1/2+1。另外中位数两边的数的数量相等，i,j满足i+j=(n+m+1)/2.
*       接下来寻找分割点，只需满足B[j−1]≤A[i] && A[i−1]≤B[j]
*       When the object i is found, the median is:
*       max(A[i−1],B[j−1]),  when m+n is odd 奇数 ​
*       ​(max(A[i−1],B[j−1])+min(A[i],B[j]))/2,  when m + nm+n is even 偶数
*/

class Solution
{
  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int len1 = nums1.size(), len2 = nums2.size();
        if (len1 == 0)
            return len2 % 2 ? nums2[len2 / 2 + 1] : (nums2[len2 / 2] + nums2[len2 / 2 + 1]) / 2;
        if (len2 == 0)
            return len1 % 2 ? nums1[len1 / 2 + 1] : (nums1[len1 / 2] + nums1[len1 / 2 + 1]) / 2;
        int median1, median2;
        median1 = len1 % 2 ? nums1[len1 / 2 + 1] : (nums1[len1 / 2] + nums1[len1 / 2 + 1]) / 2;
        median2 = len2 % 2 ? nums2[len2 / 2 + 1] : (nums2[len2 / 2] + nums2[len2 / 2 + 1]) / 2;
        if (len1 == 1 && len2 != 1)
            return len2 % 2 ? (max(nums1[0], nums2[len2 / 2]) + nums2[len2 / 2 + 1]) / 2 : max(nums1[0], nums1[len2 / 2 - 1]);
        if (len2 == 1 && len1 != 1)
            return len1 % 2 ? (max(nums2[0], nums1[len1 / 2]) + nums1[len1 / 2 + 1]) / 2 : max(nums2[0], nums1[len1 / 2 - 1]);
        if (len1 == 1 && len2 == 1)
            return (nums1[0] + nums2[0]) / 2;
        vector<int>::iterator p1, p2;
        if (median1 < median2)
        {
            p1 = nums1.begin() + (len1 - 1) / 2;
            p2 = nums2.begin() + (len2 - 1) / 2;
        }
        else
        {
            p1 = nums2.begin() + (len2 - 1) / 2;
            p2 = nums1.begin() + (len1 - 1) / 2;
        }
        while (*p2 > *(p1 + 1))
        {
            ++p1;
            --p2;
        }
        if ((len1 + len2) % 2)
            return max(*p1, *p2);
        else
            return (max(*p1, *p2) + min(*(p1 + 1), *(p2 + 1))) / 2;
    }
};


// version 3
// 二分查找，比较，丢弃不可能的部分，修正目标，迭代
// http://blog.csdn.net/zxzxy1988/article/details/8587244