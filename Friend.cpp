/*
A friend function is able to access private data members without the need of inheriting the class.
The friend function acts as a bridge between two classes by accessing their private data.
It can be declared either in the public or private or protected part of the class.
Friendship is not mutual. If class A is a friend of B, then B doesn’t become a friend of A automatically.
Friendship is not inherited.
refrence: https://www.geeksforgeeks.org/friend-class-function-cpp/
*/
#include<iostream>
using namespace std;

class Base{
	friend class F; // We can define friend functions any where in the class 
	friend void friendFun(Base &obj); // No need to worry about access specifiers 
	
	private:
	int priVal;
	protected:
	int proVal;
	public:
	Base(){
		cout << "Ctor" << endl;
		priVal = 1; proVal = 2;
	}
	~Base(){
		cout << "Dtor" << endl;
	}
};
class F{
	public:
	void getValues(Base &obj){
		cout <<"priVal:" << obj.priVal <<" proVal:" << obj.proVal << endl;
	}
};
class DF: public F{
	
};
class XYZ;
class ABC{
	int a = 1;
	public: 
	friend int maxVal(ABC &abc, XYZ &xyz);
};

class XYZ{
	int x = 3;
	public: 
	friend int maxVal(ABC &abc, XYZ &xyz);
};
int maxVal(ABC &abc, XYZ &xyz){
	if(abc.a > xyz.x){
		return abc.a;
	}else{
		return xyz.x;
	}
}
void friendFun(Base &obj){
		cout << "In Friend function" << endl;
		cout <<"priVal:" << obj.priVal <<" proVal:" << obj.proVal << endl;
}

int main (){
	
	std:cout << "Hello Friend class and Friend function" << endl;
	Base b;
	F f;
	//DF df; df.getValues();// Friendship is not inherited.
	f.getValues(b);
	friendFun(b);
	ABC aobj;
	XYZ xobj;
	cout << "MAX:" << maxVal(aobj,xobj) << endl;
	
}