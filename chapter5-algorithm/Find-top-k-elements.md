问题描述：
查找无序数组的中的前（第）K个最小（大）元素。
以查找第k个最小元素为例。

方法一：
完全排序，取第k个元素
sort(array);
array[k-1];

方法二：
最小堆；
构建整个数组的一个最小堆，将堆顶元素取出k次（每次取出顶部元素，将堆尾元素放到堆顶，调整剩余堆）

方法三：
最大堆；
将数组的前k个元素构建一个最大堆，依次将第array[k],array[k+1],array[k+2],...array[n]与堆顶元素比较，若大于则pass，若小于，则交换，调整堆，最后堆中的元素即为最小的k个元素，堆顶为第k小的元素。

方法四；
仿照快排的思想，进行不完全的快排，The idea is, not to do complete quicksort, but stop at the point where pivot itself is k’th smallest element. Also, not to recur for both left and right sides of pivot, but recur for one of them according to the position of pivot.；
1.选取任意一个元素作为做pivot，将小于pivot的元素放于其前面，大于的放于后面。
2.排完后pivot位置为i，若i=k-1，循环结束，pivot为所求元素；若i>k则在前半部分重复步骤1,2;若i<k则在后半部分重复步骤1,2。