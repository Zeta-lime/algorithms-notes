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