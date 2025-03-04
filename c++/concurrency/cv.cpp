#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
bool ready = false; // Shared flag

void worker() {
    while (!ready) {  // Polling (wasting CPU cycles)
        std::lock_guard<std::mutex> lock(mtx);  // Lock the mutex every time
        std::cout << "ready flag is false\n";    
        // No need to unlock explicitly, lock_guard will handle it automatically
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Reduce CPU usage
    }
    std::cout << "Worker thread proceeding...\n";
}

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx); // Lock mutex
        ready = true;
    }
    std::cout << "Producer has set ready to true\n";
}

int main() {
    std::thread t1(worker);
    std::thread t2(producer);

    t1.join();
    t2.join();
    return 0;
}
