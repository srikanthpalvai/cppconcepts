#include <iostream>

template <typename... Args>
auto left_fold_sum_with_zero(Args... args) {
    return (0 + ... + args );  // Left fold with addition and base case + 0
}

int main() {
    // With 0 +, it should compile and run without issues.
    // Without 0 +, it will likely compile and run for non-empty packs, but may fail for empty packs.

    std::cout << "Left Fold Sum with +0: " << left_fold_sum_with_zero(1, 2, 3, 4) << std::endl;  // Expected: 10
    return 0;
}

/*
((((0 + 1) + 2) + 3) + 4)    // Starting with base case 0
= ((0 + 1) + 2) + 3 + 4       // First operation: (0 + 1) = 1
= (1 + 2) + 3 + 4             // Second operation: (1 + 2) = 3
= 3 + 3 + 4                   // Third operation: (3 + 3) = 6
= 6 + 4                       // Final operation: (6 + 4) = 10
= 10                          // Final result: 10
*/