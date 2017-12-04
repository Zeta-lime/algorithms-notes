- 使用assert宏，在编译器编译时选择Nodebug参数编译release版的程序时，assert语句将被将被忽略掉
- 结构体内存对齐
    1. 结构体内的成员，在结构内的偏移是其大小的整数倍.
    2. 整个结构体的大小必须是其中最大成员大小的整数倍。
    https://www.zhihu.com/question/27862634
    https://software.intel.com/en-us/articles/coding-for-performance-data-alignment-and-structures

- C++数值限制
    定义于头文件<limits>
    std::numeric_limits<type>
    参考：http://www.cplusplus.com/reference/limits/numeric_limits/

- 左值、右值、移动语义、完美转发
    https://codinfox.github.io/dev/2014/06/03/move-semantic-perfect-forward/