#include<iostream>
using namespace std;
class Base{
	public:
	static int count;
	Base(){
		count++;
		cout << "ctor count:" << count << endl;
	}
	~Base()
	{
		cout << "Dtor count:" << count << endl;
		count --;	
		
	}

};
int Base::count = 0;
int main(){
	cout << "Hi.." << endl; 
	Base *p = new Base[10];
	delete [] p;
	return 0;
}
