#include <iostream>

template <typename... Args>
auto right_fold_sum_with_zero(Args... args) {
    return (args + ... + 0);  // Right fold with addition and base case + 0
}

int main() {
    // With +0, it should compile and run without issues.
    // Without +0, it will likely compile and run for non-empty packs, but may fail for empty packs.

    std::cout << "Right Fold Sum with +0: " << right_fold_sum_with_zero(1, 2, 3, 4) << std::endl;  // Expected: 10
    return 0;
}

/*
1 + (2 + (3 + (4 + 0)))
= 1 + (2 + (3 + 4))
= 1 + (2 + 7)
= 1 + 9
= 10
*/