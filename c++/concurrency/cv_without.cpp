#include <iostream>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>

std::queue<int> taskQueue;
std::mutex mtx;
bool done = false;  // Flag to indicate termination

void worker() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // Busy-waiting instead of condition_variable
        if (taskQueue.empty()) {
            if (done) break;  // Exit if producer is finished and no tasks remain
            lock.unlock();
            std::this_thread::sleep_for(std::milliseconds(100));  // Reduce CPU usage
            continue;
        }

        int task = taskQueue.front();
        taskQueue.pop();
        lock.unlock();  // Unlock before processing
        std::cout << "Worker processing task: " << task << std::endl;
    }
}

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate work
        
        std::unique_lock<std::mutex> lock(mtx);
        taskQueue.push(i);
        std::cout << "Producer added task " << i << std::endl;
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::unique_lock<std::mutex> lock(mtx);
    done = true;
    std::cout << "Producer finished, setting done = true\n";
}

int main() {
    std::thread t1(worker);
    std::thread t2(producer);

    t1.join();
    t2.join();

    return 0;
}
