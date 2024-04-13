#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

class LockGuard
{
private:
    mutex &mutex_;

public:
    LockGuard(std::mutex &mtx) : mutex_(mtx)
    {
        mutex_.lock();
    }

    ~LockGuard()
    {
        mutex_.unlock();
    }
};

mutex m;
int shared_data = 0;

void increment()
{
    for (int i = 0; i < 100000; i++)
    {
        // 临界区上锁
        LockGuard lock(m);
        shared_data++;
    }
}

void decrement()
{
    for (int i = 0; i < 100000; i++)
    {
        // 临界区上锁
        LockGuard lock(m);
        shared_data--;
    }
}

int main()
{
    thread t1(increment);
    thread t2(decrement);

    t1.join();
    t2.join();

    cout << "shared_data: " << shared_data << endl;
    return 0;
}