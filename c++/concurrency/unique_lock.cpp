#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>

std::mutex mtx;

// Function demonstrating defer locking
void deferLockExample() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Do not lock immediately
    std::cout << "[Defer Locking] Preparing to acquire lock...\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate some work

    lock.lock(); // Manually lock
    std::cout << "[Defer Locking] Lock acquired!\n";

    // Lock will automatically be released when going out of scope
} 

// Function demonstrating manual unlock/relock
void unlockRelockExample() {
    std::unique_lock<std::mutex> lock(mtx); // Lock mutex
    std::cout << "[Unlock/Relock] Lock acquired, processing data...\n";
    
    lock.unlock(); // Manually unlock
    std::cout << "[Unlock/Relock] Mutex unlocked, doing other work...\n";

    std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulate other work
    
    lock.lock(); // Re-lock
    std::cout << "[Unlock/Relock] Lock re-acquired, finishing up...\n";

    // Lock will automatically be released when going out of scope
}

// Function demonstrating moving the lock ownership
void processLock(std::unique_lock<std::mutex> lock) {
    std::cout << "[Move Ownership] Lock is now owned by processLock function.\n";
    // After this function, the lock object will be out of scope, and the mutex will be released
}

void moveLockExample() {
    std::unique_lock<std::mutex> lock(mtx); // Acquire lock
    std::cout << "[Move Ownership] Lock acquired in moveLockExample.\n";

    processLock(std::move(lock)); // Move ownership of lock
    std::cout << "[Move Ownership] Lock ownership transferred, cannot use lock anymore.\n";
}

int main() {
    // Start threads to demonstrate defer-locking, unlock/relock, and move lock ownership
    std::thread t1(deferLockExample);
    std::thread t2(unlockRelockExample);
    std::thread t3(moveLockExample);

    // Wait for threads to finish execution
    t1.join();
    t2.join();
    t3.join();

    return 0;
}
