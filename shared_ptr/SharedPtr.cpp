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

int main()
{
    return 0;
}