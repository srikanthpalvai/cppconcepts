#include <iostream>
#include <thread>
#include <mutex>
#include <shared_mutex>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

std::shared_mutex mutex_;

int shared_count;

void read_count() {
    std::shared_lock lock(mutex_);
    std::this_thread::sleep_for(std::chrono::microseconds(60));
    std::cout << "shared count" << shared_count << std::endl;
}
void write_count(){
    std::unique_lock lock(mutex_);
    shared_count++;
}
int main() {

    std::vector<std::thread> vec_t;

    // back_inserter is must and should 
    std::generate_n(std::back_inserter(vec_t), 10, [](){ return std::thread(read_count); });

    vec_t.emplace_back(std::thread(write_count));

    std::for_each(vec_t.begin(), vec_t.end(), [](std::thread &t) {
        t.join();
    });

    return 0;
}