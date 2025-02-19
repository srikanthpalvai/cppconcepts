#include <iostream>
#include <cstring>
#include <memory>

class String {
private:
    std::unique_ptr<uint8_t[]> str;  // Unique pointer to handle memory

public:
    // Default constructor
    String() : str(std::make_unique<uint8_t[]>(1)) {}  // Empty string

    // Parameterized constructor
    String(const char* s)
        : str(s ? std::make_unique<uint8_t[]>(strlen(s) + 1) : std::make_unique<uint8_t[]>(1)) {
        if (s) {
            std::memcpy(str.get(), s, strlen(s) + 1);
        }
    }

    // // Copy constructor
    // String(const String& other)
    //     : str(std::make_unique<uint8_t[]>(strlen(reinterpret_cast<const char*>(other.str.get())) + 1)) {
    //     std::memcpy(str.get(), other.str.get(), strlen(reinterpret_cast<const char*>(other.str.get())) + 1);
    // }

    // // Move constructor
    // String(String&& other) noexcept : str(std::move(other.str)) {}

    // // Copy assignment operator
    // String& operator=(const String& other) {
    //     if (this != &other) {  // Avoid self-assignment
    //         str = std::make_unique<uint8_t[]>(strlen(reinterpret_cast<const char*>(other.str.get())) + 1);
    //         std::memcpy(str.get(), other.str.get(), strlen(reinterpret_cast<const char*>(other.str.get())) + 1);
    //     }
    //     return *this;
    // }

    // // Move assignment operator
    // String& operator=(String&& other) noexcept {
    //     if (this != &other) {  // Avoid self-assignment
    //         str = std::move(other.str);
    //     }
    //     return *this;
    // }

    // Destructor is handled automatically by unique_ptr

    // Method to display the string
    void print() const {
        std::cout << (str ? reinterpret_cast<const char*>(str.get()) : "null") << std::endl;
    }
};

int main() {
    String s1("Hello");
    String s2 = s1;  // Copy constructor
     String s3 = std::move(s1);  // Move constructor

    // String s4;
    // s4 = s2;  // Copy assignment
    // s4 = String("World");  // Move assignment

    // s2.print();
    // s3.print();
    // s4.print();

    return 0;
}
