#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;

void threadFunction() {
    std::lock_guard<std::mutex> lock(mtx); // Locks automatically
    std::cout << "Thread is executing.\n"; // Mutex is locked
} // Automatically unlocks here when `lock` goes out of scope

int main() {
    std::thread t1(threadFunction);
    std::thread t2(threadFunction);

    t1.join();
    t2.join();

    return 0;
}
