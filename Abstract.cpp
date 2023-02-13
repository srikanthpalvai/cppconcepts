/*
Abstraction: Abstraction is the process of hiding implementation details and showing only the necessary information to the user
Abstract class: An abstract class is a class that contains at least one pure virtual function (i.e., a function that has no definition), and these classes cannot be instantiated.

1. Characteristics of Abstract Class in C++
	. Abstract Classes must have at least one pure virtual function.
	. Abstract Classes cannot be instantiated, but pointers and references of Abstract Class types can be created
	. Abstract Classes are mainly used for Upcasting, which means its derived classes can use its interface.
	. Classes that inherit the Abstract Class must implement all pure virtual functions. If they do not, those classes will also be treated as abstract classes.

2. Why Can't We Make an Abstract Class Object?
	. When we construct a pure virtual function in Abstract, we reserve a slot in the VTABLE(discussed in the previous topic) for a function,
	  but we don't put any address in that slot. As a result, the VTABLE will be unfinished. Since the VTABLE for the Abstract class is missing,
	  the compiler will refuse to let you create an object for it and will show an error message if you try.
	  
*/ 

#include<iostream>
using namespace std;

class Shape{
	protected:
	int width;
	int hight;
	public:
	// pure virtual function with no defination.
	virtual int area() = 0;
	void setwidth(int w){
		width = w;
	}
	void sethight(int h){
		hight = h;
	}
};
int Shape::area(){ // We can define outside the class
	cout << "Shape Area method" << endl;
	return 0;
}
class Rectangle: public Shape{
	public:
	int area(){
		return width * hight;
	}
};
class Triangle: public Shape{
	public:
	int area(){
		return (width*hight)/2;
	}
};

int main(){
		//Shape shape; //error: cannot declare variable ‘shape’ to be of abstract type ‘Shape’
					// note:   because the following virtual functions are pure within ‘Shape’:
		Rectangle rec;
		rec.setwidth(5);
		rec.sethight(5);
		cout << "Area of Rectangle:"<< rec.area() << endl; 

		Triangle tri;
		tri.setwidth(5);
		tri.sethight(5);
		cout << "Area of Triangle:"<< tri.area() << endl;

		Shape *s = new Rectangle();
		s->setwidth(2);
		s->sethight(3);
		cout << "Area of Rectangle with Shape pointer:"<< s->area() << endl;

		
}
 