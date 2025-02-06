# Understanding `std::variant` and Related Features in C++

This README provides an overview of how to work with `std::variant`, `std::holds_alternative`, `std::visit`, and related features in C++.

## Key Features Explained

### 1. **`std::variant`**
   - A **type-safe union** that can hold one value from a set of types. In this case, `int`, `double`, and `std::string`.
   - The type of `var` can **change at runtime**.
   - This is a key feature for working with **multiple possible types** within the same variable.

### 2. **`std::holds_alternative<T>`**
   - This function checks if the `std::variant` currently holds a value of type `T`. 
   - It's useful when you need to **inspect the current type** stored in the variant before accessing it.
   - This avoids errors and ensures **type safety** by ensuring that you only access a value when it's of the correct type.

### 3. **`std::get<T>`**
   - This retrieves the value of the specified type `T` from the `std::variant`. 
   - It will throw an exception (`std::bad_variant_access`) if the current type doesn't match `T`.
   - It’s used after ensuring with `std::holds_alternative<T>` that the type inside the variant is **safe to access**.

### 4. **`std::visit`**
   - This function allows you to apply a **visitor** (a function or lambda) to the value stored inside a `std::variant`.
   - It works by matching the appropriate type in the variant and calling the corresponding lambda or function for that type.
   - **Without `std::visit`**, you would have to manually check the type and cast, which can be error-prone.

### 5. **Lambda with `if constexpr`**
   - `if constexpr` is used inside the lambda to **conditionally execute** code based on the **type** of the value.
   - Here, `val += 3.14;` is only executed if `val` is of type `double`, and the code won't compile if the types don't match.
   - It ensures that the code is **type-safe** and allows **compile-time decisions**.

### 6. **`overloaded` Struct**
   - This is a helper struct used to **combine multiple lambdas** into a single function object.
   - It allows you to handle **multiple types** in a `std::variant` without writing separate visitors for each type.
   - This is useful for **code simplification** and for **handling various types** in a clean and modular way.

### 7. **Capture-by-reference in Lambdas**
   - In cases like `var = "Hello variant";`, the lambda captures `val` by reference to modify the **value** inside the variant.
   - This allows for **modifying the value directly** inside the variant without needing to manually assign a new value to `var` outside the lambda.

---

## Breakdown of Key Operations

### 1. **`std::variant` Initialization**

```cpp
std::variant<int, double, string> var = { "hello" };
```

### 2. Type Checking (std::holds_alternative)

```cpp
if (std::holds_alternative<int>(var)) { ... }
```
Ensures that you only access the value of the correct type inside the variant.

### 3. Using std::visit with Lambdas
```cpp
std::visit([](const auto& val) { std::cout << "Value: " << val << endl; }, var);
```
This allows you to apply a single lambda to handle any type stored inside the variant without manual type checking.

### 4. Modifying Variant Value
```cpp
std::visit([](auto&& val) { if constexpr (std::is_same_v<std::decay_t<decltype(val)>, double>) { val += 3.14; } }, var);
```
This allows modifying the value of the variant inside the lambda, but only if the value is of the type double.

### 5. Using overloaded to Handle Multiple Types
```cpp
std::visit(overloaded{
    [](int val) { std::cout << "Integer: " << val + 5 << std::endl; },
    [](double val) { std::cout << "Double: " << val * 2 << std::endl; },
    [](const std::string& val) { std::cout << "String: " << val << std::endl; }
}, var);
```
Here, the overloaded struct is used to handle multiple types without manually checking the type each time.

### 6. Modifying the Variant's Value
```cpp
std::visit(overloaded{
    [](int& val) { val += 5; },
    [](double& val) { val += 5.0; },
    [](std::string& val) { val += " with variadic Template"; }
}, var);
```

### Example:
```cpp

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
```
