#include <iostream>
#include <variant>
#include <string>

using namespace std;

template<class... Ts>
struct overloaded : Ts... {using Ts::operator()...;};
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

int main() {
    // Variant initialized with a string
    std::variant<int, double, string> var = { "hello" };

    // Checking the type held by the variant using std::holds_alternative<T>
    if (std::holds_alternative<int>(var)) {
        std::cout << "Integer value: " << std::get<int>(var) << std::endl;
    } else if (std::holds_alternative<double>(var)) {
        std::cout << "Double value: " << std::get<double>(var) << std::endl;
    } else if (std::holds_alternative<std::string>(var)) {
        std::cout << "String value: " << std::get<std::string>(var) << std::endl;
    }

    // Assigning new values of different types to the variant
    var = 1;              // Holds an int
    std::cout << std::get<int>(var) << std::endl;

    var = 3.14;           // Now holds a double
    std::cout << std::get<double>(var) << std::endl;

    // Using std::visit to process the value inside the variant without type checking
    std::visit([](const auto& val) { std::cout << "Value: " << val << endl; }, var);

    // Modifying the value inside the variant in visit using if constexpr
    std::visit([](auto&& val) {
        if constexpr (std::is_same_v<std::decay_t<decltype(val)>, double>) {
            val += 3.14;  // Only executed for double, ignored for other types
        }
    }, var);

    std::cout << std::get<double>(var) << std::endl;

    // Using overloaded to handle different types dynamically
    std::visit(overloaded{
        [](int val) { std::cout << "Integer: " << val + 5 << std::endl; },
        [](double val) { std::cout << "Double: " << val * 2 << std::endl; },
        [](const std::string& val) { std::cout << "String: " << val << std::endl; }
    }, var);

    // Modify the value directly inside the variant using std::visit and overloaded
    var = "Hello variant";
    std::visit(overloaded{
        [](int& val) { val += 5; },          // Modify int
        [](double& val) { val += 5.0; },     // Modify double
        [](std::string& val) { val += " with variadic Template"; } // Modify string
    }, var);

    // Print the modified value outside the lambda
    if (std::holds_alternative<int>(var)) {
        std::cout << "Modified value outside: " << std::get<int>(var) << std::endl;
    } else if (std::holds_alternative<double>(var)) {
        std::cout << "Modified value outside: " << std::get<double>(var) << std::endl;
    } else if (std::holds_alternative<std::string>(var)) {
        std::cout << "Modified value outside: " << std::get<std::string>(var) << std::endl;
    }

    return 0;
}
