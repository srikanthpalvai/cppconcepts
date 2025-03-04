#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
bool ready = false; // Shared flag

void worker() {
    while (true) {
        {
            std::cout << "Worker thread before lock" << std::endl;
            std::lock_guard<std::mutex> lock(mtx);
            if (ready) break; // If ready is set, exit loop
        }
        std::cout << "Worker thread before yield" << std::endl;
        //std::this_thread::yield(); // Let other threads run
        std::cout << "Worker thread after yield" << std::endl;
    }
    std::cout << "Worker thread proceeding...\n";
}

void producer() {
    std::this_thread::sleep_for(std::chrono::seconds(1)); // Simulate work
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true; // Set flag
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
