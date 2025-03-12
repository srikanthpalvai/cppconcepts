#include <iostream>

[[deprecated("Use newFunction() instead")]]
void oldFunction() {
    // Old implementation
}

void newFunction() {
    // New implementation
}

int main() {
    oldFunction(); // Compiler warning
    //newFunction();
}
