#include <iostream>
#include <memory>
using namespace std;

class MyClass
{
public:
    MyClass() { cout << "MyClass constructor" << endl; }
    ~MyClass() { cout << "MyClass ~constructor" << endl; }
    void do_something() { cout << "MyClass::do_something()" << endl; }
};

/**
 * 原始指针
 * count: 1
 * count: 1
 */
// int main()
// {
//     MyClass *c = new MyClass();
//     {
//         // std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
//         shared_ptr<MyClass> ptr1(c);
//         {
//             shared_ptr<MyClass> ptr2(c); // 这里共享 MyClass 对象的所有权
//             ptr1->do_something();
//             ptr2->do_something();
//             std::cout << "count: " << ptr1.use_count() << std::endl;
//         } // 这里 ptr2 被销毁，但是 MyClass 对象不会被删除，因为 ptr1 仍然拥有它的所有权
//         std::cout << "count: " << ptr1.use_count() << std::endl;
//     } // 这里 ptr1 被销毁，同时 MyClass 对象也会被删除，因为它是最后一个拥有对象所有权的 shared_ptr

//     return 0;
// }

/**
 * count: 2
 * count: 1
 */
int main()
{
    MyClass *c = new MyClass();
    {
        // std::shared_ptr<MyClass> ptr1 = std::make_shared<MyClass>();
        shared_ptr<MyClass> ptr1(c);
        {
            shared_ptr<MyClass> ptr2 = ptr1; // 这里共享 MyClass 对象的所有权
            ptr1->do_something();
            ptr2->do_something();
            std::cout << "count: " << ptr1.use_count() << std::endl;
        } // 这里 ptr2 被销毁，但是 MyClass 对象不会被删除，因为 ptr1 仍然拥有它的所有权
        std::cout << "count: " << ptr1.use_count() << std::endl;
    } // 这里 ptr1 被销毁，同时 MyClass 对象也会被删除，因为它是最后一个拥有对象所有权的 shared_ptr

    return 0;
}