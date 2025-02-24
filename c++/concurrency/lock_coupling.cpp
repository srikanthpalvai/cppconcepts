#include <iostream>
#include <mutex>
#include <thread>

struct BankAccount {
    explicit BankAccount(int balance) : balance(balance) {}
    int balance;
    std::mutex m;
};

// Function to transfer money safely between accounts
void transfer(BankAccount& from, BankAccount& to, int amount) {
    if (&from == &to) return; // Prevent self-transfer

    std::scoped_lock lock(from.m, to.m); // Locks both mutexes atomically 🔒
    
    from.balance -= amount;
    to.balance += amount;
    
    std::cout << "Transferred " << amount << " | From: " << &from << " To: " << &to << "\n";
}

int main() {
    BankAccount acc1(100), acc2(50);

    std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
    std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

    t1.join();
    t2.join();

    std::cout << "Final Balance - Acc1: " << acc1.balance << ", Acc2: " << acc2.balance << "\n";
}
