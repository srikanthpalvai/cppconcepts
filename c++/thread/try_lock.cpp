#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx;

void launch_thread(int id) {
    if (mtx.try_lock()) {  // ✅ Try to acquire lock without waiting
        std::cout << "Thread " << id << " acquired the lock.\n";
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulating work
        mtx.unlock();
    } else { // Non-blocking execution (if failure is okay)
        // Thread 2 loses work if it fails to acquire the lock with try_lock()
        std::cout << "Thread " << id << " could NOT acquire the lock.\n";
    }

}

void launch_thread_while(int id) {
    while (!mtx.try_lock()) {  // Keep retrying if lock is not available
        std::cout << "Thread " << id << " retrying...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Avoid busy-waiting
    }
    
    std::cout << "Thread " << id << " acquired the lock.\n";
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    mtx.unlock();
}


int main() {
    std::thread t1(launch_thread, 1);
    std::thread t2(launch_thread, 2);

    std::thread t3(launch_thread_while, 3);
    std::thread t4(launch_thread_while, 4);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}
