#include <iostream>
#include <type_traits>

// Base case: when there are no types left in the pack, return true
constexpr bool isUnique() {
    return true;
}

// Recursive case: checks if the first type T is different from all other types in Args...
template <typename T, typename... Args>
constexpr bool isUnique() {
    if constexpr (sizeof...(Args) == 0) {
        return true;
    } else {
        return (!std::is_same_v<T, Args> && ...) && isUnique<Args...>();
    }
}

int main() {
    std::cout << std::boolalpha;
    std::cout << isUnique<int, char, double>() << std::endl;  // Output: true
    std::cout << isUnique<int, char, int>() << std::endl;     // Output: false
    return 0;
}
