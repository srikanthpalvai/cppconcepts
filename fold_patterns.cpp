#include <iostream>

template <typename... Args>
auto right_fold_sum(Args... args) {
    return (args + ... + 0);  // Right fold with addition
}

template <typename... Args>
auto left_fold_sum(Args... args) {
    return (0 + ... + args);  // Left fold with addition
}

template <typename... Args>
auto binary_right_fold_sum(int init, Args... args) {
    return (args + ... + (init));  // Binary right fold with initial value
}

template <typename... Args>
auto binary_left_fold_sum(int init, Args... args) {
    return (init + ... + args);  // Binary left fold with initial value
}

int main() {
    std::cout << "Right Fold Sum: " << right_fold_sum(1, 2, 3, 4) << std::endl;  // Expected: 10
    std::cout << "Left Fold Sum: " << left_fold_sum(1, 2, 3, 4) << std::endl;   // Expected: 10
    std::cout << "Binary Right Fold Sum (init = 5): " << binary_right_fold_sum(5, 1, 2, 3, 4) << std::endl; // Expected: 15
    std::cout << "Binary Left Fold Sum (init = 5): " << binary_left_fold_sum(5, 1, 2, 3, 4) << std::endl;   // Expected: 15

    return 0;
}

// right_fold_sum
/*
1 + (2 + (3 + (4 + 0)))
= 1 + (2 + (3 + 4))
= 1 + (2 + 7)
= 1 + 9
= 10
*/

//left_fold_sum
/*
((((0 + 1) + 2) + 3) + 4)    // Starting with base case 0
= ((0 + 1) + 2) + 3 + 4       // First operation: (0 + 1) = 1
= (1 + 2) + 3 + 4             // Second operation: (1 + 2) = 3
= 3 + 3 + 4                   // Third operation: (3 + 3) = 6
= 6 + 4                       // Final operation: (6 + 4) = 10
= 10                          // Final result: 10
*/

//binary_right_fold_sum
/*
Expansion:
(1 + (2 + (3 + (4 + 5))))
Step-by-step evaluation:
1 + (2 + (3 + (4 + 5))) // Start with init value 5
= 1 + (2 + (3 + 9)) // (4 + 5) = 9
= 1 + (2 + 12) // (3 + 9) = 12
= 1 + 14 // (2 + 12) = 14
= 15 // (1 + 14) = 15
*/


//binary_left_fold_sum
/*
((((5 + 1) + 2) + 3) + 4)    // Start with init value 5
= (5 + 1) + 2 + 3 + 4        // (5 + 1) = 6
= 6 + 2 + 3 + 4              // (6 + 2) = 8
= 8 + 3 + 4                  // (8 + 3) = 11
= 11 + 4                     // (11 + 4) = 15
= 15                          // Final result: 15
*/


/*

Why Do We Need the Base Case (+ 0 or 0 +)?
When folding over a parameter pack, we essentially need to make sure that:

The fold stops when the parameter pack is empty.
The empty case should return a sensible result (in this case, 0 because it’s the identity element for addition).
For instance:

Empty Pack Handling: Without the base case (+ 0 or 0 +), we would run into compilation errors because the fold would have no way of terminating when the parameter pack is empty.

Identity Element for Addition: Using 0 as the base case ensures that the result doesn’t change when we add 0 (because 0 is the identity for addition). It allows the fold expression to work for both non-empty and empty packs.
*/