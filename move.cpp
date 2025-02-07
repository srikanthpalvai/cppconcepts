#include <iostream>
#include <vector>
#include <chrono>

void testVectorCopy() {
    std::vector<int> vecA(1'000'000, 42);  // A large vector with 1 million elements

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vecB = vecA;  // Copying the entire vector
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Convert to microseconds
    std::cout << "Vector Copy Time: " << microseconds.count() << " microseconds\n";
}

void testVectorMove() {
    std::vector<int> vecA(1000000, 42);  // A large vector with 1 million elements

    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vecB = std::move(vecA);  // Moving the vector (no copy)
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Convert to microseconds
    std::cout << "Vector Move Time: " << microseconds.count() << " microseconds\n";

}

int main() {
    std::cout << "Testing Vector Copy and Move Operations:\n";
    
    // Test copying
    testVectorCopy();
    
    // Test moving
    testVectorMove();

    return 0;
}
