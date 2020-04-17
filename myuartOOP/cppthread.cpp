#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>
#include <unistd.h>
#include <mutex>

/*mutex是用来保证线程同步的，防止不同的线程同时操作同一个共享数据。
使用lock_guard则相对安全，它是基于作用域的，能够自解锁，当该对象创建时，
它会像m.lock()一样获得互斥锁，当生命周期结束时，它会自动析构(unlock)，
不会因为某个线程异常退出而影响其他线程*/
std::mutex m;

void f1(int n)
{
    //std::lock_guard<std::mutex> lockGuard(m);
    for (int i = 0; i < 7; ++i) {
        std::cout << "f1-->Thread " << n++ << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
   // std::cout << "由于t1线程加锁了，所有t2线程会等待t1执行结束" << std::endl;
}

void f2(int& r)
{
  //  std::lock_guard<std::mutex> lockGuard(m);
    for (int i = 0; i < 5; ++i) {
        std::cout << "f2-->Thread " << r++ << " executing\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

int main()
{
    std::cout<< std::endl;
    std::cout << "main函数开始执行" << std::endl;
    int n = 0, r = 0;
    std::thread t1(f1, n); //pass by value
    std::thread t2(f2, std::ref(r)); //pass by reference
    /*join：调用该函数会阻塞当前线程。阻塞调用者(caller)所在的线程直至被join的std::thread对象标识
    的线程执行结，必须将线程join或者detach 等待子线程结束主进程才可以退出 */
    t1.join();//等待t1退出
    t2.join();//等待t2退出
    //n值不会改变，因为是传值
    std::cout << "Final value of n is " << n << '\n';
    //r值会变化，因为传的是引用，参数是引用跟指针都是修改参数指向的对象
    std::cout << "Final value of r is " << r << '\n';
    std::cout << "main函数执行结束" << std::endl;
    std::cout<< std::endl;
}