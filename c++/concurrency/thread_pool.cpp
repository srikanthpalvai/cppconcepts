#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <condition_variable>

class ThreadPool {
public:
    explicit ThreadPool(size_t num_threads);
    ~ThreadPool();

    void AddTask(std::function<void()> task);

private:
    void ExecuteTask();

    std::vector<std::thread> workers_;
    std::queue<std::function<void()>> task_queue_;

    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_ = false;
};

// === Constructor: Create Worker Threads ===
ThreadPool::ThreadPool(size_t num_threads) {
    for (size_t i = 0; i < num_threads; ++i) {
        workers_.emplace_back([this] { ExecuteTask(); });
    }
}

// === Destructor: Stop Threads ===
ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        stop_ = true;
    }
    condition_.notify_all();  // Wake up all threads

    for (std::thread& worker : workers_) {
        worker.join();  // Wait for all threads to finish
    }
}

// === Add Task to Queue ===
void ThreadPool::AddTask(std::function<void()> task) {
    {
        std::unique_lock<std::mutex> lock(queue_mutex_);
        task_queue_.emplace(std::move(task));  // Use move for efficiency
    }
    condition_.notify_one();
}

// === Worker Function: Process Tasks ===
void ThreadPool::ExecuteTask() {
    while (true) {
        std::function<void()> task;
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            condition_.wait(lock, [this] { return stop_ || !task_queue_.empty(); });

            if (stop_ && task_queue_.empty()) return;  // Exit if stopping

            task = std::move(task_queue_.front());  // Move the task to avoid copying
            task_queue_.pop();
        }
        task();  // Execute the task
    }
}

// === Main Function ===
int main() {
    ThreadPool pool(3);  // Create a thread pool with 3 worker threads

    for (int i = 1; i <= 5; ++i) {
        pool.AddTask([i] {
            std::cout << "Task " << i << " is running in thread " 
                      << std::this_thread::get_id() << "\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        });
    }

    std::this_thread::sleep_for(std::chrono::seconds(3));  // Give time to finish tasks
    return 0;
}
