#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono> // for sleep

std::mutex mutex_;

void print_thread_id(int i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    std::lock_guard<std::mutex> lock(mutex_);
    std::cout << "Thread " << i << " finished work" << std::endl;
}

int main() {
    size_t number_of_threads = 3;  // For simplicity, we use 3 threads
    std::cout << "number_of_threads: " << number_of_threads << std::endl;

    std::vector<std::thread> threads;

    // Using join()
    for (size_t i = 0; i < number_of_threads; ++i) {
        threads.push_back(std::thread(print_thread_id, i));  // Create thread
    }

    std::cout << "Main thread waiting for all threads to join..." << std::endl;
    for (auto& t : threads) {
        t.join();  // Wait for each thread to complete
    }

    // Using detach()
    for (size_t i = 0; i < number_of_threads; ++i) {
        std::thread t(print_thread_id, i);
        t.detach();  // Detach the thread, main thread doesn't wait for it
    }

    std::cout << "Main thread finished, detached threads are running in the background." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Give time for detached threads to finish

    return 0;
}
