#include<iostream>
#include<thread>
#include<mutex>
using namespace std;
std::mutex m;
void fun(){
	cout << "thread" << endl;
}
int main(){
	cout << "Hi ..." << endl;
	thread t(fun);
	t.join();
	cout << "Bye ..." << endl;

}

