#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

int main(){

    //A simple lambda that captures nothing and takes no parameters:
    auto printHello = [](){cout << "hello" << endl;};
    printHello();


    int multiplier = 5;
    //Capture by Value
    auto multiplyByFive = [multiplier](int x){ return x * multiplier;};
    cout << multiplyByFive(10) << endl;

    int sum = 0;
    std::vector<int> v = {8,4,5,2,9,7,3,1,6};
    // Call by refrence 
    std::for_each(v.begin(), v.end(), [&sum](int n){ sum += n;});
    cout << "SUM: " << sum << endl;

    std::sort(v.begin(), v.end(), [](auto a, auto b){ return a > b;});
    cout << "Sorted Vector: ";
    for(const auto & n : v){
        cout << n << " ";
    }
    cout << endl;

    auto even_count = std::count_if(v.begin(), v.end(),[](int a){ return a%2 ==0;});
    cout << "Even Count: "<< even_count << endl;

    std::transform(v.begin(), v.end(), v.begin(), [](int x){ return x*x;});

    // Generic lambda
    //Lambdas that use auto in their parameter list:
    auto genericprint = [](const auto& item){ cout << item << endl;};
    genericprint(95);
    genericprint("Hello");

    //Mutable Lambda
    int counter = 0;
    //Allows modification of captured variables:
    auto incCount = [counter]() mutable {return ++counter;};
    cout << incCount() << endl;
    cout << incCount() << endl;
    cout << counter << endl;

    //Recursive Lambda (C++14)
    // Lambdas that call themselves:
    std::function<int(int)> fibonacci = [&fibonacci](int n){
        return n < 2 ? n : fibonacci(n-1) + fibonacci(n-2);
    };

    cout << fibonacci(10) << endl;

    // Immediately Invoked Function experssion (IIFE)
    int s1, s2;
    s1 = 10; s2= 12;

    auto result = [](int x, int y){ return x+y;}(s1,s2);
    auto result1 = [](int x, int y){ return x+y;}(4,6);
    cout << result << endl;
    cout << result1 << endl;

    // Lambda with Trailing Return Type
    // Explicitly specifying the return type
    //Lambda with Exception Handling
    auto safeDivide = [](double a, double b) -> double{ 
            try {
                if (b == 0) throw std::runtime_error("Divison By Zero");
                return a/b;
            } catch (const exception& e) {
                cout << "Error:" << e.what() << endl;
            }
        };

    cout << safeDivide(10, 2) << endl;
    cout << safeDivide(10, 0) << endl;


    // Lambda with Multiple Captures
    // = Read only 
    // & Allow all the varaible in lambda 
    // mutable this will allow for local cahnges
    auto lambda = [=, &s2]() mutable{
        s1 += 10;
        s2 += 10;
        cout << "Inside: " << s1 << " " << s2 << endl; 
    };
    lambda();
    cout << "Outside:" << s1 << " " << s2 << endl;



    // Lambda with variadic templates (C++14)
    auto printAll = [](auto... args){
        (std::cout << ... << args) << std::endl;
    };

    printAll(1, "Lambda", 3.14);
    
    return 0;
}

/*
[ capture clause ] (parameters) -> return-type  
{   
   definition of method   
} 

*/