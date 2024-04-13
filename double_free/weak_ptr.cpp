#include <iostream>
#include <memory>
using namespace std;

/**
 * AB相互引用
 */
#include <iostream>
#include <memory>
class B; // 前向声明
class A
{
public:
    std::shared_ptr<B> b_ptr;
    ~A()
    {
        std::cout << "A destructor called" << std::endl;
    }
};

class B
{
public:
    // std::shared_ptr<A> a_ptr;
    std::weak_ptr<A> a_ptr;
    ~B()
    {
        std::cout << "B destructor called" << std::endl;
    }
};

int main()
{
    {
        std::shared_ptr<A> a = std::make_shared<A>();
        std::shared_ptr<B> b = std::make_shared<B>();
        a->b_ptr = b; // A 指向 B
        b->a_ptr = a; // B 指向 A
    }                 // a 和 b 离开作用域，但由于循环引用，它们的析构函数不会被调用

    std::cout << "End of main" << std::endl;
    return 0;
}