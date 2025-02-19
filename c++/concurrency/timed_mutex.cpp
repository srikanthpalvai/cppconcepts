#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::timed_mutex t_mutex;

void try_lock_example() {
    if (t_mutex.try_lock_for(std::chrono::milliseconds(100))) {
        std::cout << "Thread " << std::this_thread::get_id() << " acquired the lock.\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        t_mutex.unlock();
    } else {
        std::cout << "Thread " << std::this_thread::get_id() << " could not acquire the lock in time.\n";
    }
}

int main() {
    std::thread t1(try_lock_example);
    std::thread t2(try_lock_example);
    std::thread t3(try_lock_example);

    t1.join();
    t2.join();
    t3.join();
    return 0;
}
