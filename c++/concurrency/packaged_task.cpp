#include <iostream>
#include <future>
#include <thread>

using namespace std;

int add (int x, int y) {

    return x+y;
}

int main() {

    std::packaged_task<int(int,int)> task(add);
    std::future<int> future = task.get_future();

    std::thread thread(std::move(task), 10 ,20);
    thread.join();

    std::cout << "Doing some work in the main thread ..." << std::endl; 
    std::cout << "Result:" << future.get() << std::endl;

    return 0;
}