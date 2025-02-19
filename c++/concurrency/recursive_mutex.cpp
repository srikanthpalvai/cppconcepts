#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

std::recursive_mutex rmtx;

int fibonacci(int n) {
    rmtx.lock();
    int  fab;
    if (n <= 1) return n; // Base cases: Fib(0) = 0, Fib(1) = 1
    fab = fibonacci(n - 1) + fibonacci(n - 2); // Recursion
    rmtx.unlock();
    cout << fab << endl;
    return fab;
}

int main(){

    std::thread t(fibonacci,10);
    t.join();

}