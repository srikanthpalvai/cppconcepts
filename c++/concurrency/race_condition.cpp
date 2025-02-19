#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;
std::mutex m;

void run(){
	
	
	for(int i = 0; i < 100000; i++){
		m.lock();
		counter++;
		m.unlock();
	}
}

int main(){

	std::thread t1(run);
	std::thread t2(run);

	t1.join();
	t2.join();

	std::cout << "counter:" << counter << endl;
	return 0;
}
