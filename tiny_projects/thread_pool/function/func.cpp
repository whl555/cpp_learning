#include <iostream>
#include <functional>
using namespace std;

/**
 * c++函数进化史
 * 输出一个int数组中大于10的数的个数
 */
int count_arr(int *start, int *end)
{
    int count = 0;
    while (start != end)
    {
        if (*start > 10)
            count++;
        start++;
    }
    return count;
}

bool lessThan(int num, int target)
{
    return num < target;
}

bool greaterThan(int num, int target)
{
    return num > target;
}

/**
 * 输出一个int数组中大于10的数的个数
 * 将大于10作为一个条件抽象出来
 * @param bool (*condition)(int, int), 大于 or 小于的判断条件
 */
int count_arr(int *start, int *end, bool (*condition)(int, int))
{
    int count = 0;
    while (start != end)
    {
        if (condition(*start, 10))
            count++;
        start++;
    }
    return count;
}

/**
 * 判断一个数是否是奇数
 */
bool isOdd(int num)
{
    return num % 2 != 0;
}

/**
 * 求数组中满足某条件的元素个数
 * 从int数组扩展到其他类型的数组
 * @param bool (*condition)(T), T元素是否满足条件
 */
template <typename T>
int count_arr2(T *start, T *end, bool (*condition)(T))
{
    int count = 0;
    while (start != end)
    {
        if (condition(*start))
            count++;
        start++;
    }
    return count;
}

/**
 * 引入function
 */
template <class T, class E>
int count_arr3(T *start, T *end, E condition)
{
    int count = 0;
    while (start != end)
    {
        if (condition(*start))
            count++;
        start++;
    }
    return count;
}

/**
 * 引入仿函数, 对function进一步抽象
 * 设想如果条件是大于5、大于7、大于9...，每个数字均对应于一个bigger函数
 */
template <typename T>
struct bigger
{
    T target;
    bigger(T t) : target(t){};

    // 定义操作符()函数
    bool operator()(T num)
    {
        return num > target;
    }
};

template <class T, class E>
int count_arr4(T *start, T *end, E condition)
{
    int count = 0;
    while (start != end)
    {
        if (condition(*start))
            count++;
        start++;
    }
    return count;
}

/**
 * 仿函数 + operator() --> lambda
 * 
 * 
 * 引入C++ lambda
 * 1. 引入捕获机制, 解决了仿函数解决的"额外全局变量问题"
 * 2. 
 */
template <class T, class E>
int count_arr5(T *start, T *end, E condition)
{
    int count = 0;
    while (start != end)
    {
        if (condition(*start))
            count++;
        start++;
    }
    return count;
}

int main()
{
    // test count_arr
    int nums[] = {11, 12, 13, 4, 5, 6, 17, 177, 7, 9};
    cout << "res: " << count_arr(nums, nums + 10) << endl; // res: 5

    // test  count_arr(int *start, int *end, bool (*condition)(int, int)
    cout << "res: " << count_arr(nums, nums + 10, greaterThan) << endl; // res: 5
    cout << "res: " << count_arr(nums, nums + 10, lessThan) << endl;    // res: 5

    // test count_arr2(T *start, T *end, bool (*condition)(T))
    cout << "res: " << count_arr2(nums, nums + 10, isOdd) << endl; // res: 7

    // test count_arr3 function version
    function<bool(int)> isEven = [&](int num) -> bool
    {
        return num % 2 == 0;
    };
    cout << "res: " << count_arr3(nums, nums + 10, isEven) << endl; // res: 3

    // test count_arr4 global func version
    cout << "res: " << count_arr4(nums, nums + 10, bigger<int>(10)) << endl;  // res: 5
    cout << "res: " << count_arr4(nums, nums + 10, bigger<int>(176)) << endl; // res: 1

    // test lambda
    int target = 176;
    cout << "res: " << count_arr5(nums, nums + 10, [target](int num) { return num > target; }) << endl; // res: 1

    return 0;
}