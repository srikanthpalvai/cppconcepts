#include <iostream>
#include <mutex>

std::once_flag flag;

void runOnce() {
    std::call_once(flag, []() {
        std::cout << "This function is called only once!\n";
    });
}

int main() {
    runOnce();
    runOnce();  // This call will be ignored.
    runOnce();  // This call will be ignored.
    
    return 0;
}
