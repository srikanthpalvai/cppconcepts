#include <iostream>
#include <vector>
#include <memory>
#include <map>

using namespace std;

void printVector(const std::vector<int>& vec) {
    for (int it : vec) {
        std::cout << it << std::endl;
    }
}

auto main() -> int {
    std::unique_ptr<int> ptr(new int(42));
    std::cout << "Value: " << *ptr << std::endl;

    std::map<int, std::string> emp;
    emp[1] = "srikanth";
    emp.insert({2, "palvai"});


    for (const auto& e: emp){
        cout << e.first << " " << e.second << endl;

    }

    for (const auto [first, second]: emp){
        cout << first << " " << second << endl;

    }

    std::map<int, std::string>::iterator it = emp.find(1);
    if(it != emp.end()){
            std::cout << "Found: " << it->second << std::endl;
    }

    if(emp.count(1)){
        std::cout << "key exits!" << std::endl;
    }

    
    std::vector<int> vec = {1, 2, 3};
    printVector(vec);

    return 0;
}
