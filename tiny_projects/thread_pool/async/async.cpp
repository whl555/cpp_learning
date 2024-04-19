#include <iostream>
#include <thread>
#include <future>
#include <functional>
#include <mutex>
using namespace std;

// t2等待t1func任务完成, t2可以执行其他任务, t1完成任务后通知t2
int main()
{
    mutex _m;
    packaged_task<int(int, int)> func([](int a, int b) { return a + b; });
    auto ret = func.get_future();

    thread t1{[&]()
              {
                  {
                      unique_lock<mutex> lc(_m);
                      cout << "======1=======\n";
                  }
                  this_thread::sleep_for(2s);
                  func(3, 5);
                  {
                      unique_lock<mutex> lc(_m);
                      cout << "======1=======\n";
                  }
              }};

    thread t2{[&]()
              {
                  int count = 0;
                  {
                      unique_lock<mutex> lc(_m);
                      cout << "======2=======\n";
                  }
                //   while (ret.valid())
                //   {
                //       count++;
                //       cout << "count: " << count << endl;
                //       this_thread::sleep_for(2s);
                //   }
                  cout << ret.get() << "\n";
                  {
                      unique_lock<mutex> lc(_m);
                      cout << "======2=======\n";
                  }
              }};
    t1.join();
    t2.join();
}