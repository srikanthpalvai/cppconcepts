#include <iostream>
#include <vector>
#include <ranges>
#include <algorithm>

using namespace std;

struct employee{
    string name;
    int age;
};
std::string targetName = "Ram";
int targetAge = 35;

int main(){

    std::vector<employee> emp = {
        {"Ram",35},{"Robert", 45}, {"Rahim", 55}
    };
    emp.push_back({"sitha", 28});

    // basic 
    std::vector<employee>::iterator it;
    for(it = emp.begin(); it != emp.end(); ++it){
        if(it->age == targetAge && it->name == targetName){
            cout << "Found" << endl;
            break;
        } 
    }

    if(it == emp.end()){
        cout << "Not Found" << endl;
    }


    // c++ 11 range based for loop 
    for (const auto& e : emp) {
        if(e.age == targetAge && e.name == targetName){
            cout << "Found, rangesbased for loop" << endl;
        }
    }

    // c++20 ranges 
    auto result = std::ranges::find_if(emp, [](const auto& e){
            return (e.age == targetAge && e.name == targetName);
        }
    );

    if(result != emp.end()){
        cout << "Found, ranges" << endl;
    } else {
        cout << "Not found" << endl;
    }


    // c++ 20 filtered view 
    auto filtered_view = emp | std::views::filter([](const auto & e){ 
            return e.age == targetAge && e.name == targetName;
    }); 

    auto it = std::ranges::begin(filtered_view);
    if(it != std::ranges::end(filtered_view)) {
        cout << "Found, filtered view" << endl;
    } else {
        cout << "Not found" << endl;
    }

    return 0;
}