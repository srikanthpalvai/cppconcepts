#include <iostream>
#include <memory>
#include <vector>
#include <array>

using namespace std;

class myClass{


};

int main() {
    // raw pointers 
    {
//    int *ptr = malloc(sizeof(int));
//    int i = 95;
//    ptr = &i;

    }

    {
        int *ptr = new int;
        int i = 95;
        ptr = &i;
    }

    {
        int *ptr = new int[10];
        int i[] = {1,2,3,4,5,6,7,8,9,0};
        ptr = &(*i);

        for(int i = 0; i< 10; i++){
            cout << ptr[i] << endl;
        }
    }    

    std::unique_ptr<int> up = std::make_unique<int>(95);
    std::unique_ptr<int[]> arr = std::make_unique<int[]>(10);

    // we can't use the unified intializer with make_unique.
    std::unique_ptr<int[]> arr1 (new int[10]{1,2,3,4,5,6,7,8,9,0});

    cout << "up: " << *up << endl; 
    cout << "up: " << *up.get() << endl; 
    arr.get()[2] = 10;
    arr[1] = 30;
    cout << "arr[2]: " << arr.get()[2] << endl; 
    cout << "arr[1]: " << arr[1] << endl;

    {
        std::shared_ptr<std::vector<int>> arr = std::make_shared<std::vector<int>>(10,1);
        // Initialize arr...

        for (const auto& element : *arr) {
            std::cout << element << " ";
        }
            
    }
    return 0;
}