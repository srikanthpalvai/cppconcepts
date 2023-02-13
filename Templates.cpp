/*
C++ templates are a powerful feature that allow you to write generic and reusable code.
They provide a way to define type-independent functions, classes, and objects that can work with a variety of data types.

The idea is simple, source code contains only function/class, but compiled code may contain multiple copies of the same function/class. 
Compiler internally generates int and flot double code methods 

*/
#include<iostream>
using namespace std;

// Function Template
template <typename T> T mymax(T v1, T v2){ // Remember here we have std::max function so go with mymax
	return (v1 > v2) ? v1 : v2;
}

// Class Template
template <typename T> class Array{
	private:
	int size;
	T* ptr;
	public:
	Array(T arr[], int s);
	void print();
};
template <typename T> Array<T> ::Array(T arr[], int s){
	ptr = new T[s];
	size = s;
	for(int i = 0;i < size; i++){
		ptr[i] = arr[i];
	}
}
template <typename T> void Array<T>::print(){
	for(int i=0; i<size; i++){
		cout << " " << *(ptr+i) << endl;
	}
}

// multiple argument to templates
template <typename T, typename U> class Base{
	public:
	T x;
	U y;
	Base(T t, U u):x(t),y(u){
	}
	void getvalues(){
		cout << "x:" << x << " y:" << y << endl;		
	}
	
};
// // arguments with default values
template <typename T, typename U = char> class A{
	public:
	T x;
	U y;
	A(T t, U u):x(t),y(u){
	}
	void getvalues(){
		cout << "x:" << x << " y:" << y << endl;		
	}
	
};

int main(){

	std::cout << "Hello Templates" << std::endl;
	// Template function 
	std::cout << "intmax:" << mymax<int>(5,6) << std::endl;
	/*int mymax(int v1, int v2){
		return (v1 > v2) ? v1 : v2;
	}	
	*/
	std::cout << "floatmax:" << mymax<float>(5.5,5.4) << std::endl;
	/*flot mymax(flot v1, flot v2){
		return (v1 > v2) ? v1 : v2;
	}
	*/
	std::cout << "doublemax:" << mymax<double>(6.333,6.334) << std::endl;
	/*double mymax(double v1, double v2){
		return (v1 > v2) ? v1 : v2;
	}
	*/	
	
	// Class template 
	int arr[5] = {1,2,3,4,5};
	Array<int> array(arr,5);
	array.print();
	
	// Multipule arguments
	Base<int,double> base(5,6.6);
	base.getvalues();

	// Default datatype 
	A<int> a(1, 'a');
	a.getvalues();
}