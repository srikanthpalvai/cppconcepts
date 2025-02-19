#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;
#ifndef USE_LOCK_GUARD 
#define USE_LOCK_GUARD
#endif

std::mutex mtx;
int count = 0;

int launch_thread(){

#ifndef USE_LOCK_GUARD     
    mtx.lock(); // this lock make sure's that it will not overlap 
    std::cout << "Thread " << std::this_thread::get_id() << " .... STARTED" << endl;
    std::cout << "count: " << ++count << std::endl;
    std:this_thread::sleep_for(chrono::microseconds(10)); // Slow down for better overlap visibility 
    std::cout << "Thread " << std::this_thread::get_id() << " ... END" << endl;

    // Dead lock here 
    // int ret = launch_thread(); // check recusrive call here  

    mtx.unlock();

#else
    {
        // using the lock_guard
        std::cout << "using lock_guard" << std::endl;
        {
            lock_guard<mutex> lock(mtx);
            std::cout << "Thread " << std::this_thread::get_id() << " .... STARTED" << endl;    
            std::cout << "count: " << ++count << std::endl;
        }

        std:this_thread::sleep_for(chrono::microseconds(10)); // Slow down for better overlap visibility 

        {
            lock_guard<mutex> lock(mtx);
            std::cout << "Thread " << std::this_thread::get_id() << " ... END" << endl;    
        }
    }

#endif

}

int main(){

    std::thread t;
    std::vector<std::thread> vec;

    vec.emplace_back(std::thread{launch_thread});
    vec.emplace_back(std::thread{launch_thread});

    for(auto& v: vec) {
        v.join();
    }

    return 0;
}
