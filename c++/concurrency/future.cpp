#include <iostream>
#include <future>

using namespace std;

int add (int x, int y) {

    return x+y;
}

int main() {

    std::promise<int> promise;
    std::future<int> future = promise.get_future();

    std::thread thread([&promise](){
        int result = add(1,2);
        promise.set_value(result);
    });

    std::cout << "Doing some work in the main thread ..." << std::endl; 
    
    thread.join();
    std::cout << "result:" << future.get() << std::endl;

    return 0;
}