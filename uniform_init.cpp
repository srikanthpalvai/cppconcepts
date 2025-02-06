#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <optional>
#include <variant>
#include <tuple>
#include <map>
#include <fstream>

class A {
public:
    A(int x) { std::cout << "A initialized with " << x << "\n"; }
    void display() { std::cout << "A object is being used.\n"; }
};

struct Point {
    int x, y, z;
    
    // No constructor required, just uniform initialization
    void show() {
        std::cout << "Point coordinates: " << x << ", " << y << ", " << z << "\n";
    }
};

// C++17 features
std::optional<int> getValue(bool flag) {
    if (flag) return {42};  // Uniform initialization
    return std::nullopt;
}

class C {
public:
    int arr[3];
    C(int x, int y, int z) : arr{x, y, z} {}
    
    void show() {
        std::cout << "Array contents: ";
        for (int i = 0; i < 3; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    // 1. Prevents Narrowing Conversions (C++17)
    std::cout << "\nExample 1: Prevents Narrowing Conversions\n";
    double d = 3.14;
    // Uncommenting the next line would give a compile-time error due to narrowing conversion
    // int x{d};  // Error in C++11 and later (narrowing)
    std::cout << "Narrowing conversion prevention works!\n";

    // 2. Improved `std::vector` and `std::array` Initialization
    std::cout << "\nExample 2: Improved std::vector and std::array Initialization\n";
    std::vector<int> v{1, 2, 3, 4, 5};  // Uniform initialization
    std::array<int, 3> arr{10, 20, 30}; // Uniform initialization

    for (int i : v) std::cout << i << " ";
    std::cout << "\n";

    for (int i : arr) std::cout << i << " ";
    std::cout << "\n";

    // 3. Consistent Initialization in struct and class
    std::cout << "\nExample 3: Consistent Initialization in struct and class\n";
    Point p{1, 2, 3};  // Uniform initialization
    p.show();  // Accessing public members directly

    // 4. `std::optional` Initialization (C++17)
    std::cout << "\nExample 4: std::optional Initialization\n";
    std::optional<int> val = getValue(true);
    if (val) std::cout << "Value: " << *val << "\n";
    else std::cout << "No value\n";

    // 5. `std::variant` and `std::tuple` Initialization (C++17)
    std::cout << "\nExample 5: std::variant and std::tuple Initialization\n";
    std::variant<int, double, std::string> v2{3.14};  // Works perfectly
    std::tuple<int, double, std::string> t{1, 2.5, "Hello"};

    std::cout << std::get<2>(t) << "\n"; // Prints "Hello"

    // 6. Avoids "Most Vexing Parse" Issue
    std::cout << "\nExample 6: Avoids 'Most Vexing Parse' Issue\n";
    A a1{7};  // Uniform initialization avoids ambiguity (Most Vexing Parse issue)
    a1.display();

    // 7. Efficient Memory Allocation for Containers (std::vector)
    std::cout << "\nExample 7: Efficient Memory Allocation for Containers\n";
    std::vector<std::vector<int>> matrix{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    for (const auto& row : matrix) {
        for (int num : row) std::cout << num << " ";
        std::cout << "\n";
    }

    // 8. Smart Pointer Initialization (std::unique_ptr)
    std::cout << "\nExample 8: Smart Pointer Initialization (std::unique_ptr)\n";
    auto p2 = std::make_unique<A>(8);  // Uniform initialization
    p2->display();  // Accessing object via unique_ptr

    // 9. `std::map` and `std::unordered_map` Initialization
    std::cout << "\nExample 9: std::map Initialization\n";
    std::map<std::string, int> myMap{
        {"Apple", 5},
        {"Banana", 2},
        {"Cherry", 10}
    };

    for (const auto& [key, value] : myMap) {
        std::cout << key << ": " << value << "\n";
    }

    // 10. File Handling with RAII (C++17)
    std::cout << "\nExample 10: File Handling with RAII (C++17)\n";
    std::ifstream file{"data.txt"};  // Automatically closes file when goes out of scope

    if (file) std::cout << "File opened successfully!\n";
    else std::cout << "Failed to open the file.\n";

    // 11. Manually creating and deleting object with new (Not recommended)
    std::cout << "\nExample 11: Manual Memory Management (new and delete)\n";
    A* p3 = new A(9);  // Using raw pointer with new
    p3->display();  // Using the object
    delete p3;  // Don't forget to delete the memory

    // 12. Implicit Initialization with a Function Returning a Smart Pointer
    std::cout << "\nExample 12: Implicit Initialization with Smart Pointer in a Function\n";
    auto p5 = []() { return std::make_unique<A>(12); }();  // Implicit initialization via lambda
    p5->display();

    // 13. Direct object initialization using uniform initialization (stack allocation)
    std::cout << "\nExample 13: Direct Object Initialization (Stack Allocation)\n";
    A a2{11};  // Direct initialization using uniform initialization
    a2.display();  // Accessing the object

    // 14. Using `new` with Uniform Initialization (Not recommended, but valid)
    std::cout << "\nExample 14: Using `new` with Uniform Initialization (Not recommended)\n";
    std::unique_ptr<A> p6{new A(16)};  // Directly using `new` with uniform initialization
    p6->display();

    return 0;
}
