#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx1, mtx2;

void exampleFunction() {
    // Using defer_lock to construct the lock without locking initially
    std::unique_lock<std::mutex> lock1(mtx1, std::defer_lock);
    std::unique_lock<std::mutex> lock2(mtx2, std::defer_lock);

    // Lock both mutexes atomically to avoid deadlock
    std::lock(lock1, lock2);
    std::cout << "Thread " << std::this_thread::get_id() << " acquired both locks using defer_lock\n";
}

void tryLockExample() {
    std::unique_lock<std::mutex> lock(mtx1, std::try_to_lock);
    if (lock.owns_lock()) {
        std::cout << "Thread " << std::this_thread::get_id() << " acquired lock using try_to_lock\n";
    } else {
        std::cout << "Thread " << std::this_thread::get_id() << " failed to acquire lock using try_to_lock\n";
    }
}

void adoptLockExample() {
    mtx2.lock();  // Lock manually
    std::unique_lock<std::mutex> lock(mtx2, std::adopt_lock);  // Take ownership of the already locked mutex
    std::cout << "Thread " << std::this_thread::get_id() << " adopted lock using adopt_lock\n";
}

int main() {
    std::thread t1(exampleFunction);
    std::thread t2(tryLockExample);
    std::thread t3(adoptLockExample);

    t1.join();
    t2.join();
    t3.join();

    return 0;
}
