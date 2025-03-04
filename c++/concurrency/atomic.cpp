#include <iostream>
#include <atomic>
#include <thread>
#include <vector>
#include <chrono>

void basic_operations() {
    std::atomic<int> atomicInt(10);  // C++11

    std::cout << "Initial value: " << atomicInt.load() << "\n";  // load() (C++11)
    
    atomicInt.store(20);  // store() (C++11)
    std::cout << "After store(20): " << atomicInt.load() << "\n";
    
    int oldValue = atomicInt.exchange(30);  // exchange() (C++11)
    std::cout << "After exchange(30), old value was: " << oldValue << ", new value: " << atomicInt.load() << "\n";
}

void memory_ordering() {
    std::atomic<int> atomicVal(0);  // C++11
    
    atomicVal.store(10, std::memory_order_relaxed);  // store with relaxed ordering (C++11)
    std::cout << "Stored with relaxed memory order: " << atomicVal.load(std::memory_order_relaxed) << "\n";
}

void compare_exchange() {
    std::atomic<int> atomicInt(100);  // C++11
    int expected = 100;

    if (atomicInt.compare_exchange_strong(expected, 200)) {  // compare_exchange_strong (C++11)
        std::cout << "CAS strong succeeded, new value: " << atomicInt.load() << "\n";
    } else {
        std::cout << "CAS strong failed, expected: " << expected << ", actual: " << atomicInt.load() << "\n";
    }

    expected = 200;
    atomicInt.compare_exchange_weak(expected, 300);  // compare_exchange_weak (C++11)
    std::cout << "CAS weak (may fail spuriously), new value: " << atomicInt.load() << "\n";
}

void fetch_operations() {
    std::atomic<int> atomicCounter(0);  // C++11

    atomicCounter.fetch_add(10);  // fetch_add (C++11)
    std::cout << "After fetch_add(10): " << atomicCounter.load() << "\n";

    atomicCounter.fetch_sub(5);  // fetch_sub (C++11)
    std::cout << "After fetch_sub(5): " << atomicCounter.load() << "\n";
}

void flag_operations() {
    std::atomic_flag flag = ATOMIC_FLAG_INIT;  // C++11

    if (!flag.test_and_set()) {  // test_and_set() (C++11)
        std::cout << "Flag was not set, now set.\n";
    }
    if (!flag.test_and_set()) {  // test_and_set() (C++11)
        std::cout << "Flag was not set, now set.\n";
    }else{
        std::cout << "Flag was set...\n";
    }

    flag.clear();  // clear() (C++11)
    std::cout << "Flag cleared.\n";
}

void notify_wait_operations() {
#if __cplusplus >= 202002L  // C++20 only
    std::atomic<int> atomicVal(0);

    std::thread waiter([&]() {
        std::cout << "Waiting for atomicVal to change...\n";
        atomicVal.wait(0);  // wait() (C++20)
        std::cout << "Wait finished, new value: " << atomicVal.load() << "\n";
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));
    atomicVal.store(1);
    atomicVal.notify_one();  // notify_one() (C++20)

    waiter.join();
#endif
}

void type_aliases() {
    std::atomic<int> atomicInt;  // C++11
    std::atomic<bool> atomicBool;  // C++11
    std::atomic<void*> atomicPtr;  // C++11

    using intType = std::atomic<int>::value_type;  // value_type (C++11)
    using boolType = std::atomic<bool>::value_type;  // value_type (C++11)

    std::cout << "Atomic int type: " << typeid(intType).name() << "\n";
    std::cout << "Atomic bool type: " << typeid(boolType).name() << "\n";
}

int main() {
    std::cout << "--- Basic Operations ---\n";
    basic_operations();

    std::cout << "\n--- Memory Ordering ---\n";
    memory_ordering();

    std::cout << "\n--- Compare and Exchange ---\n";
    compare_exchange();

    std::cout << "\n--- Fetch and Arithmetic ---\n";
    fetch_operations();

    std::cout << "\n--- Flag Operations ---\n";
    flag_operations();

#if __cplusplus >= 202002L
    std::cout << "\n--- Notify and Wait (C++20) ---\n";
    notify_wait_operations();
#endif

    std::cout << "\n--- Type Aliases ---\n";
    type_aliases();

    return 0;
}
