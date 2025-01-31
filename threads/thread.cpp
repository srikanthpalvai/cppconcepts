#include<iostream>
#include<thread>
#include<mutex>
#include<unistd.h>

using namespace std;
std::mutex m;
int count = 0;

void increment(){
	while(count < 10)
	{	m.lock();
		count++;
		cout << "increment count:" << count << endl;
		m.unlock();
	}
}
void decrement() {
	// Add sleep here to make sure that increment thread will be going to execute first.
	// In case if decrement calls, it will check that count is not grater then 5 so it will skip the logic  
	//sleep(1);
	while(count > 0){
		m.lock();
		count--;
		cout << "decrement count:" << count 	<< endl;
		m.unlock();
	}
}
int main(){
	cout << "Hi ..." << endl;
	thread t1(increment);
	thread t2(decrement); 
	t1.join();
	t2.join();

	cout << "Bye ..." << endl;
	return 0;
}
