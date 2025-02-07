#include <iostream>

template <typename... Args>
auto right_fold_sum_without_zero(Args... args) {
    return (args + ...);  // Right fold without +0 base case
}

int main() {
    // With +0, it should compile and run without issues.
    // Without +0, it will likely compile and run for non-empty packs, but may fail for empty packs.
    std::cout << "Right Fold Sum without +0: " << right_fold_sum_without_zero(1, 2, 3, 4) << std::endl;  // Expected: 10
    return 0;
}
