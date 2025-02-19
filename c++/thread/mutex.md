# Mutex Locking with `mtx.lock()` vs `lock_guard<mutex>`

This document outlines the differences between using `mtx.lock()` and `mtx.unlock()` versus using `std::lock_guard<mutex>` in C++ for locking and unlocking mutexes.

## Difference Between `mtx.lock()`/`mtx.unlock()` and `lock_guard<mutex>`

| Feature                | `mtx.lock()` / `mtx.unlock()` | `lock_guard<mutex>`            |
|------------------------|------------------------------|--------------------------------|
| **Manual Locking**      | ✅ Yes                       | ❌ No                         |
| **Automatic Unlocking** | ❌ No (must call `mtx.unlock()`) | ✅ Yes (unlocks when `lock_guard` goes out of scope) |
| **Exception Safety**    | ❌ Unsafe (if an exception occurs, `mtx.unlock()` might be skipped) | ✅ Safe (automatically releases lock even if an exception is thrown) |
| **Ease of Use**         | ❌ More error-prone (requires manual lock & unlock) | ✅ More convenient (RAII - Resource Acquisition Is Initialization) |

## Explanation of Key Differences

### 1. **Manual Locking**
   - `mtx.lock()` requires you to manually call `mtx.unlock()` to release the lock. If you forget to unlock the mutex, it can lead to **deadlocks** or **blocked execution**.
   - `std::lock_guard<mutex>` automatically locks the mutex when the `lock_guard` object is created and automatically unlocks it when the object goes out of scope.

### 2. **Automatic Unlocking**
   - With `mtx.lock()`, you must explicitly call `mtx.unlock()` to release the lock.
   - `std::lock_guard<mutex>` unlocks the mutex when it is destroyed (e.g., when the scope in which it is defined ends).

### 3. **Exception Safety**
   - Using `mtx.lock()`/`mtx.unlock()` is **not exception-safe**. If an exception is thrown between `mtx.lock()` and `mtx.unlock()`, the lock will not be released, potentially causing deadlocks.
   - `std::lock_guard<mutex>` is **exception-safe**. Even if an exception is thrown, the lock is automatically released when the `lock_guard` object goes out of scope, preventing deadlocks.

### 4. **Ease of Use**
   - `mtx.lock()`/`mtx.unlock()` is more **error-prone** because you have to manage the lock/unlock manually. Forgetting to unlock the mutex is a common mistake.
   - `std::lock_guard<mutex>` is **more convenient** because it follows the RAII (Resource Acquisition Is Initialization) principle, which automatically handles locking and unlocking in a scope-based manner.

## When to Use Each

- **Use `mtx.lock()`/`mtx.unlock()`** if you need more **fine-grained control** over when the lock is acquired and released, and you are confident you can manage it manually without errors.
  
- **Use `std::lock_guard<mutex>`** for **most scenarios** where the lock should be released as soon as the critical section ends, as it ensures automatic and exception-safe unlocking.

## Conclusion

While `mtx.lock()` gives you manual control over the mutex, `std::lock_guard<mutex>` provides a safer and more convenient alternative, ensuring that the mutex is always unlocked properly, even in the presence of exceptions.
