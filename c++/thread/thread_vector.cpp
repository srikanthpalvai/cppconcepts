
#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

// Simple thread function
void threadFunction() {
    std::cout << "Thread " << std::this_thread::get_id() << " is running.\n";
}

int main() {
    const int numThreads = 5;
    std::vector<std::thread> threads;

    // Use std::generate_n to create threads
    std::generate_n(std::back_inserter(threads), numThreads, []() {
        return std::thread(threadFunction);
    });

    // Use std::for_each to join threads
    std::for_each(threads.begin(), threads.end(), [](std::thread &t) {
        t.join();
    });

    return 0;
}
