#include <iostream>
#include <thread>
#include <chrono>
#include <unistd.h>
#include <vector>

using namespace std;

void launch_thread() {
    cout << "In the launch_thread" << endl;
    cout << "launch_thread ID:" << std::this_thread::get_id() << endl;
}

void launch_detach_thread() {
    cout << "In the launch_detach_thread" << endl;
    cout << "launch_thread ID:" << std::this_thread::get_id() << endl;
}

void launch_thread_with_arg(int value) {
    cout << "In the launch_thread_with_arg with value " << value << endl;
    cout << "launch_thread ID:" << std::this_thread::get_id() << endl;
}
auto launch_thread_with_lambda = [](){ 
    cout << "In the lambda fucntion" << endl;
    cout << "launch_thread ID:" << std::this_thread::get_id() << endl;
};

class A{
    public:
    void func() {
        cout << "A function " << endl;
    }
    void func_with_arg(int val) {
        cout << "A function with arg " << val << endl;
    }
};

class B{
    public:
    static void func(){
        cout << "B static func" << endl;
    }
};

class fun_obj_class {
    public:
    // Remember we need two (). 
    void operator()() {
        cout << "fun_obj_class " << endl;
        cout << "launch_thread ID:" << std::this_thread::get_id() << endl;
    }
};

int main() {

    A a;
    std::thread t1(launch_thread);
    std::thread t2(launch_thread_with_arg, 1);
    std::thread t3(launch_thread_with_lambda);
    std::thread t4(&A::func, &a); // launch with class method
    std::thread t5(&A::func_with_arg, &a, 1); // launch with class method with argument 
    std::thread t6(&B::func); // lanuch static method 
    std::thread t7{fun_obj_class()};

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();

    // Create threads using the array 
    std::thread t_array[] = {
        std::thread (launch_thread),
        std::thread (launch_thread_with_arg, 1),
        std::thread (launch_thread_with_lambda),
        std::thread (&A::func, &a), // launch with class method
        std::thread (&A::func_with_arg, &a, 1), // launch with class method with argument 
        std::thread (&B::func), // lanuch static method 
        std::thread {fun_obj_class()}
    };

    for(auto &t : t_array) t.join();

    // create threads using vector 
    std::vector<std::thread> t_vec;
        t_vec.emplace_back(std::thread (launch_thread));
        t_vec.emplace_back(std::thread (launch_thread_with_arg, 1));
        t_vec.emplace_back(std::thread (launch_thread_with_lambda));
        t_vec.emplace_back(std::thread (&A::func, &a)); // launch with class method
        t_vec.emplace_back(std::thread (&A::func_with_arg, &a, 1)); // launch with class method with argument 
        t_vec.emplace_back(std::thread (&B::func)); // lanuch static method 
        t_vec.emplace_back(std::thread {fun_obj_class()});

    for(auto &t : t_vec) t.join();

    std::thread dt(launch_detach_thread);
    dt.detach();


    std::thread _thread;
    if(_thread.joinable()){
        cout << " ******* Yes thread is joinable" << endl;
        cout << "******** Let's jon it " << endl;
    }

    sleep(10);  
}