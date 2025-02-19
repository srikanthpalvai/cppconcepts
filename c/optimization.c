#include <stdio.h>

// 🔹 (1) INLINE FUNCTION (Avoids function call overhead) ➡ **Enabled in -O2, -O3**
inline int square(int x) {  
    return x * x;  // Compiler replaces function call with direct multiplication
}

// 🔹 (2) CONSTANT FOLDING & PROPAGATION ➡ **Enabled in -O1, -O2, -O3**
void constant_folding_propagation() {
    int result = 4 * 2 + 3 - 1;  // Compiler simplifies this to result = 10

    // 🔹 Optimized Version:
    // int result = 10;  // (Compiler replaces expression with precomputed value)

    printf("Constant Folding Result: %d\n", result);
}

// 🔹 (3) DEAD CODE ELIMINATION ➡ **Enabled in -O2, -O3**
void dead_code_elimination() {
    int a = 5;
    int b = 10;
    int c = a + b;  // If 'c' is never used, compiler removes it.

    // 🔹 Optimized Version (if printf is removed, 'c' is removed)
    printf("Dead Code Prevention: %d\n", c);
}

// 🔹 (4) LOOP UNROLLING ➡ **Enabled in -O2, -O3**
void loop_unrolling() {
    int arr[4] = {1, 2, 3, 4};
    int sum = 0;

    // ✅ Original Version:
    for (int i = 0; i < 4; i++) {
        sum += arr[i];
    }

    // 🔹 Optimized Version (Compiler may unroll like this):
    // sum += arr[0];
    // sum += arr[1];
    // sum += arr[2];
    // sum += arr[3];

    printf("Loop Unrolling Example: Sum = %d\n", sum);
}

// 🔹 (5) VECTORIZATION (Using SIMD instructions) ➡ **Enabled in -O2, -O3**
void vectorization() {
    int A[4] = {1, 2, 3, 4};
    int B[4] = {5, 6, 7, 8};
    int C[4];

    // ✅ Original Version:
    for (int i = 0; i < 4; i++) {
        C[i] = A[i] + B[i];
    }

    // 🔹 Optimized Version (Compiler may use SIMD vectorized instructions):
    // C[0] = A[0] + B[0];
    // C[1] = A[1] + B[1];
    // C[2] = A[2] + B[2];
    // C[3] = A[3] + B[3];

    printf("Vectorization Result: %d %d %d %d\n", C[0], C[1], C[2], C[3]);
}

// 🔹 (6) STATIC SINGLE ASSIGNMENT (SSA) ➡ **Enabled in -O2, -O3**
void ssa_example() {
    int x = 5;  // SSA: Compiler assigns x1 = 5
    int y = 10; // SSA: Compiler assigns y1 = 10
    int z;

    if (x > 3) {
        z = x + y;  // SSA: z1 = x1 + y1
    } else {
        z = x - y;  // SSA: z2 = x1 - y1
    }

    // 🔹 Optimized Version (Compiler introduces SSA Phi Function):
    // z = φ(z1, z2);  // (Compiler decides which value of 'z' to use)

    printf("SSA Example: z = %d\n", z);
}

// 🔹 (7) UPDATED REGISTER ALLOCATION ➡ **Enabled in -O1, -O2, -O3**
void register_allocation() {
    int a = 5, b = 10, c = 0;

    for (int i = 0; i < 1000000; i++) {
        c += a * b;  // 'a' and 'b' are frequently used, so likely stored in registers
    }

    printf("Register Allocation Example: c = %d\n", c);
}

int main() {
    printf("🔹 Running Compiler Optimization Examples 🔹\n\n");

    printf("🔸 Optimization Level Required: -O1, -O2, -O3\n");
    constant_folding_propagation();  

    printf("\n🔸 Optimization Level Required: -O2, -O3\n");
    dead_code_elimination();         

    printf("\n🔸 Optimization Level Required: -O2, -O3\n");
    loop_unrolling();                

    printf("\n🔸 Optimization Level Required: -O2, -O3\n");
    vectorization();                 

    printf("\n🔸 Optimization Level Required: -O2, -O3\n");
    ssa_example();                    

    printf("\n🔸 Optimization Level Required: -O1, -O2, -O3\n");
    register_allocation();            

    return 0;
}
