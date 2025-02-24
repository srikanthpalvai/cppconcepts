# **`std::shared_lock` in C++ (C++17 and Later)**  

## **What is `std::shared_lock`?**  
`std::shared_lock` is a **RAII-based** locking mechanism introduced in **C++17** that allows **multiple threads to read (shared access) while still preventing writes (exclusive access).**  

### **Key Concept:**  
- ✅ **Multiple readers allowed** (shared ownership)  
- ✅ **Only one writer allowed** (exclusive ownership)  

It is used with **`std::shared_mutex`**, which allows both **shared (read) and exclusive (write) locking.**  

---

## **Why Use `std::shared_lock`?**
- ✅ **Improves performance** → Multiple readers can access a resource simultaneously.  
- ✅ **Prevents contention** → Threads don’t block each other unnecessarily.  
- ✅ **Automatic unlocking** → Lock is released when going out of scope.  
- ✅ **Works with `std::shared_mutex`** → Ensures safe shared/exclusive access.

---

## **Example: Using `std::shared_lock`**

### **Before (`std::mutex` Only - Blocks Reads and Writes)**  
```cpp
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

std::mutex mtx;
int data = 0;

void readData(int id) {
    std::lock_guard<std::mutex> lock(mtx);  // Blocks all other readers & writers
    std::cout << "Reader " << id << " reads: " << data << "\n";
}

void writeData(int newValue) {
    std::lock_guard<std::mutex> lock(mtx);  // Blocks all readers & writers
    data = newValue;
    std::cout << "Writer updated data to " << newValue << "\n";
}

int main() {
    std::thread t1(readData, 1);
    std::thread t2(readData, 2);
    std::thread t3(writeData, 10);

    t1.join();
    t2.join();
    t3.join();
}
```