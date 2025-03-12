#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::mutex mutex_;
int main(){
    size_t number_of_threads = std::thread::hardware_concurrency();
    std::cout << "number_of_threads:" << number_of_threads << std::endl;
//    std::vector<std::thread> vec;
    std::cout << "Before  for loop ....." << std::endl;
    for (size_t i = 0; i < number_of_threads; i++)
    {
        // vec.emplace_back(std::thread([i](){ 
        //     std::lock_guard<std::mutex> lock(mutex_);
        //     std::cout << "i: " << i << std::endl;}));

        // Without vector 
        std::thread([i](){
            std::lock_guard<std::mutex> lock(mutex_);
            std::cout << "i: " << i << std::endl;
        }).join();
    }
    std::cout << "After for loop ....." << std::endl;
    // for (auto& v: vec)
    // {
    //     v.join();
    //     /* code */
    // }
    
}