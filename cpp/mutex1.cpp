#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>

using namespace  std;

bool isTrue = false;
std::mutex mtx;
std::condition_variable cv;

void doSomething()
{
    cout << "this is : " << this_thread::get_id() << endl;
}

void thread_Func()
{
    unique_lock<mutex> loc(mtx);
    while(!isTrue)
        cv.wait(loc);

    doSomething();
}



int main()
{
    vector<thread> v;
    v.reserve(10);

    for(int i = 0; i < 10; i++) {
        v.emplace_back(thread_Func);
    }

    this_thread::sleep_for(chrono::seconds(2));

    {
        unique_lock<mutex> loc(mtx);
        isTrue = true;
        cv.notify_all();
    }

    for(auto& t : v) {
        t.join();
    }
    return 1;
}
