#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;

//std::atomic<int> counter;
int counter;
int count = 1000000;
//std::mutex mutex_;
void thread_function(){

    for (size_t i = 0; i < count; i++)
    {
//        mutex_.lock();
        counter++;
//        mutex_.unlock();
    }

}

int main () {

    std::thread t1(thread_function);
    std::thread t2(thread_function);

    t1.join();
    t2.join();

    std::cout << "counter: " << counter << std::endl;
    return 0;
}