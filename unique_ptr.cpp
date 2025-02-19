#include <iostream>
#include <memory>
#include <vector>

using namespace std;

int main(){

    {
        uint8_t var1 = 255;   // 8-bit unsigned integer (0 to 255)
        uint16_t var2 = 65535; // 16-bit unsigned integer (0 to 65,535)
        uint32_t var3 = 4294967295; // 32-bit unsigned integer (0 to 4,294,967,295)

        printf("uint8_t: %u\n", var1);
        printf("uint16_t: %u\n", var2);
        printf("uint32_t: %u\n", var3);
    }

    {
        std::unique_ptr<uint8_t> var1 = std::make_unique<uint8_t>(65);   // 8-bit
        std::unique_ptr<uint16_t> var2 = std::make_unique<uint16_t>(65535); // 16-bit
        std::unique_ptr<uint32_t> var3 = std::make_unique<uint32_t>(4294967295); // 32-bit

        std::cout << "uint8_t: " << *var1 << std::endl;
        std::cout << "uint8_t: " << static_cast<uint32_t>(*var1) << std::endl;
        std::cout << "uint16_t: " << *var2 << std::endl;
        std::cout << "uint32_t: " << *var3 << std::endl;
    }
    {
        std::unique_ptr<uint8_t[]> ptr1 = std::make_unique<uint8_t[]>(255);
        std::vector<uint8_t> buffer (ptr1.get(), ptr1.get()+ 255);
        for(auto b: buffer){
            std:cout <<  b << std::endl;
        }
    }
}