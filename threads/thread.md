### C++ concurrency and threading

## 1. Thread Management
✅ Creating and Joining Threads:

Using std::thread to spawn threads.
thread.join() vs. thread.detach().
Why joining is necessary (to prevent resource leaks).
✅ Thread Lifecycle & Issues:

What happens if you don’t join/detach a thread?
RAII for threads using std::jthread (C++20).
✅ Lambda Functions & Thread Execution:

Passing arguments to threads (std::ref, std::move).
✅ Thread Synchronization Mechanisms:

std::mutex (basic locking) vs. std::shared_mutex (C++17, reader-writer locks).
std::lock_guard and std::unique_lock.
std::condition_variable (Producer-Consumer pattern).
std::atomic (lock-free operations).

## 2. Synchronization Primitives
✅ Mutex & Locking Strategies:

std::mutex (basic lock).
std::recursive_mutex (avoid deadlock in recursive functions).
std::timed_mutex and std::try_lock (timeout-based locking).
std::shared_mutex for read/write access (C++17).
✅ Deadlocks & Prevention Strategies:

Deadlock causes (e.g., circular waiting).
Avoiding deadlocks (lock hierarchy, std::lock, try-lock pattern).
✅ Condition Variables (std::condition_variable)

Used for signaling between threads.
wait() and notify_one() / notify_all().
✅ Atomic Variables (std::atomic)

Used for lock-free programming.
fetch_add(), compare_exchange_strong().
Memory ordering (std::memory_order).

## 3. Advanced Topics
✅ Thread-Local Storage (thread_local)

Variables specific to each thread.
✅ Futures and Promises (std::future, std::promise)

How to return values from threads asynchronously.
std::async for launching async tasks.
✅ Task-Based Concurrency (std::packaged_task)

Wrapping functions for delayed execution.
✅ Executors and Thread Pools (C++23)

Using std::jthread and std::stop_token (graceful stopping).

## 4. Common Interview Questions
🟢 Conceptual Questions:

What’s the difference between a thread and a process?
When would you use std::atomic over std::mutex?
How does std::condition_variable work?
What’s the ABA problem, and how can it be avoided?
Explain deadlocks, livelocks, and starvation.
🟢 Coding Problems:

Producer-Consumer Problem (using std::condition_variable).
Dining Philosophers Problem (avoid deadlocks).
Thread-safe Singleton Pattern (std::call_once).
Implement a thread pool (managing worker threads).

## 5. Best Practices for Multithreading in C++
✔ Avoid data races by minimizing shared data.
✔ Use std::atomic for lightweight synchronization.
✔ Use std::condition_variable for signaling.
✔ Prefer std::jthread (C++20) over std::thread for automatic cleanup.
✔ Minimize locking duration to improve performance.