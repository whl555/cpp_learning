#include <iostream>
using namespace std;

template<typename T>
void func(T &param) {
    cout << "left refer" << endl;
}

template<typename T>
void func(T &&param) {
    cout << "right refer" << endl;
}

// 只写一个模板函数即可以接收左值又可以接收右值
template<typename T>
void func1(T &&param) {
    cout << "refer" << endl;
}

// 不完美转发版本
template<typename T>
void func2(T &&param) {
    func(param);
}

// 完美转发版本
template<typename T>
void func3(T &&param) {
    func(forward<T>(param));
}


/**
 * 本文内容, 完美转发 = 万能引用 + forward + 引用折叠
 */
int main()
{
    // 测试左值右值
    int a = 0;
    func(a);
    func(0);

    // 只写一个模板函数即可以接收左值又可以接收右值
    func1(a);
    func1(0);

    // 转发场景下, 如何保持引用类型不变? 如果万能引用
    // left refer left refer why?
    // 第一个, 根据引用折叠规则, param是左值引用
    // 第二个, 根据引用折叠规则, param是右值引用, 但是因为参数有了名称, 所以从右值引用变成了左值, 触发了func的左值引用版本
    func2(a);
    func2(0);

    // 测试完美转发
    // left refer right refer
    func3(a);
    func3(0);
}