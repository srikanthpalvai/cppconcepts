# C++ Mutex Locking Mechanisms: Key Points

## 1. std::lock() Requires Multiple Mutexes
- **Correct Usage:** `std::lock(mtx1, mtx2);` (locks multiple mutexes atomically)
- **Error:** `std::lock(lock1);` (needs at least two mutexes)
- **Fix:** Use `.lock()` for a single mutex with `std::unique_lock`.

## 2. std::adopt_lock Without Prior Locking Causes Undefined Behavior
- **Correct Usage:** Lock the mutex first, then use `std::unique_lock` with `std::adopt_lock`.
- **Error:** Using `std::adopt_lock` on an unlocked mutex leads to undefined behavior.

## 3. std::try_to_lock Doesn’t Block
- **Correct Usage:** `std::unique_lock<std::mutex> lock(mtx, std::try_to_lock);`
- **Note:** It attempts to lock once and does not wait.

## 4. std::defer_lock Requires Manual Locking
- **Usage:** Use `std::defer_lock` and call `.lock()` manually later.

## 5. std::unique_lock vs std::lock_guard
| Feature                          | std::unique_lock | std::lock_guard |
|----------------------------------|------------------|------------------|
| Supports deferred locking?       | ✅ Yes            | ❌ No            |
| Supports try-to-lock?           | ✅ Yes            | ❌ No            |
| Supports adopt lock?             | ✅ Yes            | ❌ No            |
| Supports manual unlocking?        | ✅ Yes            | ❌ No            |
| Performance                      | Slightly slower   | Faster           |

## 6. Mutex Ownership and Lifetime
- The mutex must outlive the `std::unique_lock` to avoid undefined behavior.

## 7. Deadlock Risk With Nested Locks
- Be cautious of locking order; use `std::lock(mtx1, mtx2);` to prevent deadlocks.

## 8. Recursive Mutex (std::recursive_mutex)
- Use `std::recursive_mutex` for functions that call themselves recursively.

## 9. std::timed_mutex for Time-Limited Lock Attempts
- Use `std::timed_mutex` to attempt locking with a timeout.

# Interview Questions
1. What happens if you use `std::adopt_lock` on an unlocked mutex?
2. Why does `std::lock(lock1);` fail, but `std::lock(lock1, lock2);` work?
3. What’s the difference between `std::try_to_lock` and `std::lock()`?
4. When would you use `std::recursive_mutex` instead of `std::mutex`?
5. Why does `std::defer_lock` require a manual `.lock()` call?
