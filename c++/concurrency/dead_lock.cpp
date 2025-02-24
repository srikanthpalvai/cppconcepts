#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex imageBuffer, cache; // Shared resources

void blurFilter() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work before locking

    // Lock imageBuffer first, then cache
    std::lock_guard<std::mutex> lock1(imageBuffer);
    std::cout << "Thread 1 locked imageBuffer for blur processing.\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    
    std::lock_guard<std::mutex> lock2(cache); // Try to lock cache
    std::cout << "Thread 1 locked cache for blur processing.\n";
    
    // Process the image with the blur filter...
}

void sharpenFilter() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work before locking
    
    // Lock cache first, then imageBuffer
    std::lock_guard<std::mutex> lock1(cache);
    std::cout << "Thread 2 locked cache for sharpen processing.\n";
    
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Simulate work
    
    std::lock_guard<std::mutex> lock2(imageBuffer); // Try to lock imageBuffer
    std::cout << "Thread 2 locked imageBuffer for sharpen processing.\n";
    
    // Process the image with the sharpen filter...
}

int main() {
    std::thread t1(blurFilter);
    std::thread t2(sharpenFilter);

    t1.join();
    t2.join();

    return 0;
}
