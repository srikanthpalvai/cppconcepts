#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>

// Shared queue to hold tasks
std::queue<int> taskQueue;
std::mutex mtx;
std::condition_variable cv;
bool done = false;  // To signal when to exit

void worker() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, []() { return !taskQueue.empty() || done; });  // Wait for tasks or shutdown signal

        if (done && taskQueue.empty()) {
            break;  // Exit the loop if done and no more tasks
        }

        // Process task
        int task = taskQueue.front();
        taskQueue.pop();
        std::cout << "Worker processing task: " << task << std::endl;
    }
}

void producer() {
    for (int i = 1; i <= 5; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Simulate work
        std::unique_lock<std::mutex> lock(mtx);
        taskQueue.push(i);  // Add task to queue
        std::cout << "Producer added task " << i << std::endl;
        cv.notify_one();  // Notify worker thread
    }

    std::this_thread::sleep_for(std::chrono::seconds(1));
    done = true;  // Signal the worker thread to exit
    std::cout << "notify_all" << std::endl;
    cv.notify_all();  // Notify the worker thread to stop waiting
}

int main() {
    std::thread t1(worker);  // Worker thread
    std::thread t2(producer);  // Producer thread

    t1.join();
    t2.join();

    return 0;
}
