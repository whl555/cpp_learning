#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <time.h>
#include <vector>
#include <queue>
#include <future>
#include <mutex>
#include <queue>
#include <functional>
#include <utility>
#include <vector>
#include <condition_variable>
#include <string>
#include <shared_mutex>
using namespace std;

/**
 * 1. 引用折叠, F &&f
 * 2. 返回值后置: auto xxx(xx) -> std::future<decltype(f(args...))>  std::future<decltype(f(args...))>
 * 3. decltype--推断类型
 * 4. [task_ptr]() -- 参数列表为空, 但捕获task_ptr; [&f, args...]()
 *
 * 1. 加锁实现safe_queue √
 * 2. 利用完美转发获取可调用对象的函数签名 x
 * 3. lambda与function包装任务 √
 * 4. RAII管理线程池的生命周期 x
 */

/**
 * todo: use shared_mutex to lock all methods
 */
template <typename T>
struct safe_queue
{
    queue<T> que;
    shared_mutex _m;
    bool empty()
    {
        shared_lock<shared_mutex> lc(_m);
        return que.empty();
    }
    auto size()
    {
        shared_lock<shared_mutex> lc(_m);
        return que.size();
    }
    void push(T &t)
    {
        unique_lock<shared_mutex> lc(_m);
        que.push(t);
    }
    bool pop(T &t)
    {
        unique_lock<shared_mutex> lc(_m);
        if (que.empty())
            return false;
        t = move(que.front());
        que.pop();
        return true;
    }
};

class ThreadPool
{
private:
    class worker
    {
    public:
        ThreadPool *pool;
        worker(ThreadPool *_pool) : pool{_pool} {}

        // invoke in ThreadPool constructor
        void operator()()
        {
            while (!pool->is_shut_down)
            {
                {
                    // lock + use lambda to decide whther has tasks if pool has started
                    unique_lock<mutex> lock(pool->_m);
                    pool->cv.wait(lock, [this]()
                                  { return this->pool->is_shut_down ||
                                           !this->pool->que.empty(); });
                }
                // Worker工作逻辑: remove task, if success, run this task
                function<void()> func;
                bool flag = pool->que.pop(func);
                if (flag)
                {
                    func();
                }
            }
        }
    };

public:
    bool is_shut_down;
    safe_queue<std::function<void()>> que;
    vector<std::thread> threads;
    mutex _m;
    condition_variable cv;
    ThreadPool(int n) : threads(n), is_shut_down{false}
    {
        // todo migrate to thread factory
        // per thread to per Worker
        for (auto &t : threads)
            t = thread{worker(this)};
    }
    ThreadPool(const ThreadPool &) = delete;
    ThreadPool(ThreadPool &&) = delete;
    ThreadPool &operator=(const ThreadPool &) = delete;
    ThreadPool &operator=(ThreadPool &&) = delete;

    // Args... type ; ...args arguments; F: function; future: task run results;
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    {
        // use another lambda to wrapper f, pass arguments to f
        function<decltype(f(args...))()> func = [&f, args...]()
        { return f(args...); }; // typename... Args 拿到了函数的参数，然后下面用到了f(args...)??
        // create a shared_ptr task_ptr to point to wrapper func
        auto task_ptr = std::make_shared<std::packaged_task<decltype(f(args...))()>>(func);
        // use third lambda to wrap task_ptr to warpper_func(such as function(void()))
        std::function<void()> warpper_func = [task_ptr]()
        {
            (*task_ptr)();
        };
        // push task into safe_queue, and at the same time use condition_variable to notify one thread to run the task
        que.push(warpper_func);
        cv.notify_one();
        // return task result
        return task_ptr->get_future();
    }

    ~ThreadPool()
    {
        // RAII?
        // when destroy, submit null, reset flags, through join to destroy threads
        auto f = submit([]() {});
        f.get();
        is_shut_down = true;
        cv.notify_all(); // 通知，唤醒所有工作线程
        for (auto &t : threads)
        {
            if (t.joinable())
                t.join();
        }
    }
};
mutex _m;
int main()
{

    ThreadPool pool(8);
    int n = 20;
    // API submit
    // auto submit(F &&f, Args &&...args) -> std::future<decltype(f(args...))>
    //
    for (int i = 1; i <= n; i++)
    {
        pool.submit([](int id)
                    {
                if (id % 2 == 1) {
                    this_thread::sleep_for(0.2s);
                }
                unique_lock<mutex> lc(_m);
                cout << "id : " << id << endl; },
                    i);
    }

    cout << "hello world" << endl;
}