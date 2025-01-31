#include <iostream>
#include <cstring>
using namespace std;

class String{
public:
    char* data;

    // Constructor
    String(const char* str = "") {
        data = new char[strlen(str) + 1];
        strcpy(data, str);
        std::cout << "Constructor Called!" << std::endl;
    }

    // Copy Constructor (Deep copy)
    String(const String& obj) {
        data = new char[strlen(obj.data) + 1];
        strcpy(data, obj.data);
        std::cout << "Copy Constructor Called!" << std::endl;
    }

    // Move Constructor
    String(String&& obj) noexcept {
        data = obj.data;
        obj.data = nullptr; // Nullify the source to prevent double delete
        std::cout << "Move Constructor Called!" << std::endl;
    }

    // Copy Assignment Operator
    String& operator=(const String& obj) {
        // Self assignment check
        if (this != &obj) {
            delete[] data;
            data = new char[strlen(obj.data) + 1];
            strcpy(data, obj.data);
            std::cout << "Copy Assignment Operator Called!" << std::endl;
        }
        return *this;
    }

    // Move Assignment Operator
    String& operator=(String&& obj) noexcept {
        if (this != &obj) {
            delete[] data;
            data = obj.data;
            obj.data = nullptr;
            std::cout << "Move Assignment Operator Called!" << std::endl;
        }
        return *this;
    }

    // Destructor
    ~String() {
        delete[] data;
    }

    // Print the string
    void printstr() const {
        if (data != nullptr) {
            cout << data << endl;
        } else {
            cout << "Data is null!" << endl;
        }
    }
};

int main() {
    String str1("hello world!");
    str1.printstr();

    // Move Constructor (str1 is now in a moved-from state)
    String str2 = std::move(str1);  // str1 is now empty/null
    str2.printstr();
    // str1.printstr();  // Don't print str1 after it's been moved from; it is in an invalid state

    // Copy Constructor
    String str3(str2);  
    str3.printstr();

    String str4("Temp String");
    str4.printstr();
    str4 = str3;  // Copy Assignment
    str4.printstr();

    String str5("Hello Again!");
    str5.printstr();

    // Move Assignment
    str4 = std::move(str5);  // str5 is now empty/null
    str4.printstr();
    // str5.printstr();  // Don't print str5 after it's been moved from; it is in an invalid state

    return 0;
}
