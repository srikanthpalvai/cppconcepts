## Lock_guard

std::lock_guard<std::mutex> is designed for RAII (Resource Acquisition Is Initialization), meaning it locks a mutex when the object is created and automatically unlocks it when the object goes out of scope. This is why lock_guard does not provide an unlock() method—to prevent misuse and ensure safe resource management.

## Key Reasons Why lock_guard Doesn’t Have an unlock() Method

1️⃣ Prevents Accidental Unlocking
std::lock_guard ensures the mutex stays locked as long as the guard exists.
If you had to manually call unlock(), you might forget, leading to deadlocks or race conditions.
```
void threadFunction() {
    std::lock_guard<std::mutex> lock(mtx); // Locks automatically
    std::cout << "Thread is executing.\n"; // Mutex is locked
} // Automatically unlocks here when `lock` goes out of scope

```

2️⃣ Ensures Exception Safety
If an exception occurs inside the critical section, the mutex is still released when lock_guard goes out of scope.
Without RAII, you’d have to manually unlock in every possible exit path, which is error-prone.

```
void badFunction() {
    mtx.lock();  // Manual lock
    throw std::runtime_error("Oops! Exception!"); // Mutex remains locked forever 😨
    mtx.unlock();  // This line is NEVER reached!
}



void safeFunction() {
    std::lock_guard<std::mutex> lock(mtx); // Mutex is locked
    throw std::runtime_error("Oops! Exception!"); // Mutex unlocks automatically 😃
} // Unlocks here, even though an exception was thrown!

```

3️⃣ Encourages Simplicity
std::lock_guard is meant for simple scope-based locking.
If you need manual unlocking/relocking, use std::unique_lock.
