### Scoped_lock

What is std::scoped_lock?
std::scoped_lock is a RAII-based locking mechanism introduced in C++17 that allows multiple mutexes to be locked at once in a deadlock-free manner.

std::scoped_lock locks multiple mutexes in a single call, ensuring a consistent order and avoiding deadlocks.



Key Features:
✅ Locks multiple mutexes at once (prevents deadlocks).
✅ Ensures a consistent lock order across all threads.
✅ Automatically unlocks mutexes when going out of scope.
✅ More efficient than manually locking multiple mutexes.