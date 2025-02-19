### Unique_lock 
std::unique_lock is more flexible than std::lock_guard because it supports deferred locking, unlocking, and moving.

## 1. Can Defer Locking (std::defer_lock)
You can create a std::unique_lock without immediately locking the mutex. This is useful when you need to perform some operations before acquiring the lock.

```cpp
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx, std::defer_lock); // Do not lock immediately

    // Some pre-lock processing
    std::cout << "Preparing to lock...\n";

    lock.lock(); // Lock when needed
    std::cout << "Thread acquired lock!\n";

    // Mutex is automatically released when `lock` goes out of scope
}
```
## 2. Can Manually Unlock and Relock
std::unique_lock allows you to manually unlock and relock the mutex, which is useful when you want to perform a long operation without blocking other threads.

```cpp
void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Thread acquired lock, performing task...\n";

    lock.unlock(); // Unlock to allow other threads to proceed
    std::this_thread::sleep_for(std::chrono::seconds(2)); // Simulate a long task

    lock.lock(); // Re-lock before modifying shared resource
    std::cout << "Thread re-acquired lock after sleeping.\n";
}
```

## 3. Supports Moving Between Scopes
A std::unique_lock can be moved to another function or scope, transferring ownership of the lock.

```cpp
void processLock(std::unique_lock<std::mutex> lock) {
    // Ownership of lock is transferred to this function
    std::cout << "Lock is now owned by processLock function.\n";
}

void threadFunction() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Lock acquired in threadFunction.\n";

    processLock(std::move(lock)); // Move lock ownership
    std::cout << "Lock ownership transferred. Cannot use lock in threadFunction anymore.\n";
}
```
std::move(lock) transfers ownership of the lock to another function.
After moving, lock in the original function is no longer valid.
This is useful when passing a lock to another function for handling critical sections.


| Feature                          | Example                                                     |
|----------------------------------|-------------------------------------------------------------|
| **Defer Locking (`std::defer_lock`)** | Creates `std::unique_lock` without immediately locking it.   |
| **Manually Unlock/Relock**       | Allows unlocking and relocking as needed for efficiency.   |
| **Supports Moving**              | `std::move(lock)` transfers ownership to another function. |


### conclusion
std::unique_lock provides powerful flexibility beyond std::lock_guard. Use it when:

You need deferred locking (std::defer_lock).
You want to manually unlock and relock.
You need to move the lock between functions.
