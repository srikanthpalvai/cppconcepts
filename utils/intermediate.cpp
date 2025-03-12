#include <iostream>

int get_value() {
    [[indeterminate]] int x; // Compiler recognizes x as indeterminate
//    int x; // Compiler recognizes x as indeterminate

    return x; // Using x might be undefined behavior
}
int main(){
   std::cout <<  get_value() << std::endl;
}