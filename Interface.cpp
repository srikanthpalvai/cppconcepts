/* Interface
Interfaces are nothing but a way to describe the behavior of a class without committing to the implementation of the class.
In C++ programming there is no built-in concept of interfaces. In order to create an interface,
we need to create an abstract class which is having only pure virtual methods. In C++, Interfaces are also called pure abstract classes.
*/

#include<iostream>
using namespace std;

class IShape{ //Interface class 
	public:
	virtual double area() = 0;
	virtual double perimeter() = 0;
};

class Rectanlge: public IShape{
	
	public:
	double width_,height_;
	Rectanlge(){
		cout << "Default ctor" << endl;
	}
	Rectanlge(double w, double h):width_(w),height_(h){
		cout << "Rectanlge parameterized ctor: " << width_ << " " << height_ << endl;
	}
	double area(){
		return (width_* height_);
	}
	double perimeter(){
		return 2 * (width_ + height_);
	}
};

class Circle: public IShape{
	public:
	double radius_;
	Circle(double r):radius_(r){
		cout << "Circle paramterized ctor:" << radius_ << endl; 
	}
	double area(){
		return 3.14 * radius_* radius_;
	}
	double perimeter(){
		return 2* 3.14 * radius_;
	}
};
int main(){
	
	IShape *shape = new Rectanlge(5,5);
	cout << "Rectanlge area:" << shape->area() << endl;
	cout << "Rectanlge perimeter:" << shape->perimeter() << endl;
	Circle circle(5);
	shape = &circle;
	cout << "Circle area:" << shape->area() << endl;
	cout << "Circle perimeter:" << shape->perimeter() << endl;
	
	return 0;
}