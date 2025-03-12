#include <iostream>
#include <functional>

class Calculator {
public:
    // A function that takes three arguments: x, y, and operator type
    void calculate(int x, int y, const std::string& operation) {
        if (operation == "add") {
            std::cout << "Result: " << x + y << std::endl;
        } else if (operation == "subtract") {
            std::cout << "Result: " << x - y << std::endl;
        } else {
            std::cout << "Unknown operation!" << std::endl;
        }
    }
};

int main() {
    Calculator calc;

    // Bind the 'calculate' function with placeholders
    // _1 is for 'x', _2 is for 'y', and _3 is for 'operation'
    auto calculateAdd = std::bind(&Calculator::calculate, &calc, std::placeholders::_1, std::placeholders::_2, "add");
    auto calculateSubtract = std::bind(&Calculator::calculate, &calc, std::placeholders::_1, std::placeholders::_2, "subtract");

    // Now we can call these bound functions with the first two arguments, the third argument is fixed.
    calculateAdd(10, 5);        // Output: Result: 15
    calculateSubtract(10, 5);   // Output: Result: 5

    return 0;
}
