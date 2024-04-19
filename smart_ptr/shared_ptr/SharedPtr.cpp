#include <iostream>

template <typename T>
class SharedPtr
{
public:
    explicit SharedPtr(T *ptr) : ptr_(ptr), count_(ptr ? new size_t(1) : nullptr) {}

    ~SharedPtr()
    {
        release();
    }

    // 拷贝构造函数
    SharedPtr(const SharedPtr &other) : ptr_(other.ptr_), count_(other.count_)
    {
        std::cout << "copy constructor" << std::endl;
        if (count_)
        {
            ++(*count_);
        }
    }

    // =等于
    SharedPtr &operator=(const SharedPtr &other)
    {
        std::cout << "operator=" << std::endl;
        if (this != &other)
        {
            release(); // 删除旧有数据
            ptr_ = other.ptr_;
            count_ = other.count_;
            if (count_)
            {
                ++(*count_);
            }
        }
        return *this;
    }

    T *operator->() const
    {
        return ptr_;
    }

    T &operator&() const
    {
        return *ptr_;
    }

    T *get() const
    {
        return ptr_;
    }

    size_t use_count() const
    {
        return count_ ? *count_ : 0;
    }

private:
    T *ptr_;
    size_t *count_;

    // 每次引用计数-1, 直到最后一个引用离开作用域, 释放内存
    void release()
    {
        if (count_ && --(*count_) == 0)
        {
            delete ptr_;
            delete count_;
        }
    }
};

class MyClass
{
public:
    MyClass() { std::cout << "MyClass constructor\n"; }
    ~MyClass() { std::cout << "MyClass ~constructor\n"; }
    void do_something() { std::cout << "MyClass::do_something() invoked\n"; }
};

int main()
{
    {
        SharedPtr<MyClass> ptr1(new MyClass());
        {
            // SharedPtr<MyClass> ptr2(nullptr);
            // ptr2 = ptr1;
            SharedPtr<MyClass> ptr2 = ptr1;
            ptr1->do_something();
            ptr2->do_something();
            std::cout << "count: " << ptr1.use_count() << std::endl;
        }
        std::cout << "count: " << ptr1.use_count() << std::endl;
    }

    return 0;
}