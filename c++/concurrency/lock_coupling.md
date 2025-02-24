
# **Lock Coupling in C++**

## **What is Lock Coupling?**
Lock coupling is a technique where two or more mutexes are locked at the **same time** to ensure thread safety while accessing shared resources. It is used in situations where multiple resources (such as variables, data structures, or objects) need to be protected from concurrent access.

Lock coupling helps to avoid **deadlocks** by ensuring that mutexes are locked in a consistent order.

## **Why Use Lock Coupling?**
When multiple threads are accessing multiple shared resources (e.g., two bank accounts or two objects), we need to lock the corresponding mutexes. If mutexes are locked in inconsistent orders across different threads, a **deadlock** can occur.

By using lock coupling, we lock multiple mutexes **simultaneously** (or in a known order) to prevent such issues.

---

## **Deadlock Scenario Without Lock Coupling**
Consider the scenario where two threads are trying to transfer money between two bank accounts:

1. **Thread 1** locks `mutex1` (for `account1`), then tries to lock `mutex2` (for `account2`).
2. **Thread 2** locks `mutex2` (for `account2`), then tries to lock `mutex1` (for `account1`).

If both threads lock the mutexes in a different order, a **deadlock** occurs:
- Thread 1 holds `mutex1` and waits for `mutex2`.
- Thread 2 holds `mutex2` and waits for `mutex1`.

Since neither thread can proceed, the program is stuck in a deadlock.

---

## **How Lock Coupling Solves This?**

Lock coupling ensures that mutexes are locked in a **consistent order** across all threads. This eliminates the possibility of deadlocks.

### **Steps:**
1. **Lock both mutexes at the same time** using `std::lock` (or manually locking in a specific order).
2. **Unlock both mutexes** in a consistent order once the critical section is complete.

---

## **Example: Bank Account Transfer with Lock Coupling**

In the example below, two bank accounts are being used by multiple threads, and we want to ensure that a transfer is safe from a deadlock.

```cpp
#include <iostream>
#include <mutex>
#include <thread>

struct BankAccount {
    int balance;
    std::mutex m;
    BankAccount(int b) : balance(b) {}
};

void transfer(BankAccount& from, BankAccount& to, int amount) {
    // Lock both mutexes at once, avoiding deadlocks
    std::lock(from.m, to.m);
    
    // Adopt the locks without re-locking (since std::lock already acquired them)
    std::lock_guard<std::mutex> lock1(from.m, std::adopt_lock);
    std::lock_guard<std::mutex> lock2(to.m, std::adopt_lock);

    if (from.balance >= amount) {
        from.balance -= amount;
        to.balance += amount;
        std::cout << "Transferred " << amount << " from Account 1 to Account 2\n";
    } else {
        std::cout << "Insufficient funds\n";
    }
}

int main() {
    BankAccount account1(100);
    BankAccount account2(50);

    std::thread t1(transfer, std::ref(account1), std::ref(account2), 10);
    std::thread t2(transfer, std::ref(account2), std::ref(account1), 5);

    t1.join();
    t2.join();

    std::cout << "Account 1 Balance: " << account1.balance << "\n";
    std::cout << "Account 2 Balance: " << account2.balance << "\n";
}
```

# **Comparison: `std::lock + std::adopt_lock` vs `std::scoped_lock`**

| **Use Case**                              | **Use std::lock + std::adopt_lock**                           | **Use std::scoped_lock**                                          |
|-------------------------------------------|---------------------------------------------------------------|-------------------------------------------------------------------|
| **C++11 or C++14 (Older codebases)**      | ✅ Yes, since `std::scoped_lock` is not available              | ❌ Not available                                                  |
| **C++17 or later (Modern codebases)**     | ❌ More verbose                                               | ✅ Preferred                                                      |
| **Multiple mutexes (Deadlock prevention)**| ✅ Yes                                                        | ✅ Yes (simpler)                                                   |
| **Readability & Maintainability**         | ❌ More complex                                              | ✅ Cleaner & easier to understand                                  |
