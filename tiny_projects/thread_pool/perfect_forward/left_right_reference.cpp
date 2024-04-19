#include <iostream>
using namespace std;

void func(int &&a)
{
    cout << a << endl;
}

/**
 * 本文内容, 左值 + 右值 + move
 */
int main()
{
    int a = 5;
    // func(a); error: 右值引用不能指向左值
    func(5);
    func(a + 3);
    // int &&b = a; error: 右值引用不能指向左值
    int &&c = 5;

    // move函数使用, std::move作用主要可以将一个左值转换成右值引用，从而可以调用C++11右值引用的拷贝构造函数
    func(move(a));

    // forward函数使用, std::move作用是传入的是什么引用, 传出的就是什么引用
}