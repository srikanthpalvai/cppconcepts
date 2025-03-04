#include <iostream>
#include <future>
#include <chrono>
#include <unistd.h>
#include <thread>

using namespace std;

int addition (int x, int y) {
    std::cout << "In Addition" << std::endl;
    // this will will running in the other thread check the thread id 
    std::cout << "addition thread ID:" << std::this_thread::get_id() << std::endl;
    return x+y;
}
int subtraction (int a, int b) {
    std::cout << std::endl <<  "In subtraction" << std::endl;
    // Find the observation substraction is tkaen place at the call sub.get();
    std::cout << "addition thread ID:" << std::this_thread::get_id() << std::endl;
    return a - b;
}
int main () {

    std::cout << "main thread ID:" << std::this_thread::get_id() << std::endl;

    std::future<int> add = std::async(std::launch::async, addition, 1, 2);
    sleep(1);
    std::cout << "Do some work in the main thread ..." << std::endl;
    std::cout << "Result:" << add.get() << std::endl;

    std::future<int> sub = std::async(std::launch::deferred, subtraction, 10, 5);  
    sleep(1);
    std::cout << "Do some more work in the main thread ..." << std::endl;
    std::cout << "Result:" << sub.get() << std::endl;
    return 0;
}