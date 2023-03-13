/*
The Singleton pattern is a creational design pattern that ensures that only one instance of a class can exist, and provides a global point of access to that instance.

Some of the key features of the Singleton pattern are:

It ensures that only one instance of a class is created and provides a global point of access to that instance.
The constructor of the Singleton class is made private, so that no other instances of the class can be created from outside the class.
The Singleton instance is typically created lazily, i.e., only when it is first needed.
Once the Singleton instance is created, it is reused throughout the lifetime of the application.
The Singleton pattern is commonly used in situations where a single instance of a class needs to coordinate actions across an entire system, such as in a logging or configuration system.
Some thumb rules for implementing the Singleton pattern are:

Make the constructor of the Singleton class private to prevent other instances from being created.
Provide a static method that returns the Singleton instance, which creates the Singleton instance if it doesn't already exist.
Use lazy initialization to create the Singleton instance only when it is first requested.
Make the Singleton instance static and final to ensure that it can't be modified or overwritten.
Consider making the Singleton class thread-safe to prevent race conditions when multiple threads access the Singleton instance.
Avoid using the Singleton pattern in situations where there may be multiple instances of the same class in different contexts, as this can lead to coupling and other problems.
*/

#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

class Singleton{
	private: 
		Singleton(){}
		static std::mutex mutex_;
		static Singleton* instance;
	public:
		static Singleton* getInstance();
};
Singleton* Singleton::instance = NULL;
std::mutex Singleton::mutex_;
Singleton* Singleton::getInstance()
{
	if(instance == NULL){
		std::lock_guard<std::mutex> lg(mutex_);
		instance = new Singleton();
		return instance;
	}else{
		return instance;
	}
}

int main(){
	Singleton* singleton = Singleton::getInstance();
	cout << "Address of singleton: " << singleton << endl;
	cout << "Address of singleton::" << Singleton::getInstance() << endl;
	return 0;
}