/*
Advantages:
1. Dynamic array that can resize itself automatically as elements are added or removed
2. Random access: You can access elements in a std::vector using an index
3. Dynamic size: A std::vector can grow or shrink in size as elements are added or removed		  
4. Automatic memory management: A std::vector manages its own memory


Diadvantages:
Overhead:
Performance: Depending on the size of the std::vector and the operations being performed on it,
No bounds checking: By default, a std::vector does not perform bounds checking when you access elements using an index.
This can lead to undefined behavior if you access elements outside the bounds of the vector.
Not thread-safe: A std::vector is not thread-safe by default,
which means that if you access it from multiple threads at the same time, you may run into race conditions and other synchronization issues.
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

class Vec{
	public:
	int v;
	Vec(int x = 0):v(x){ cout << "Ctor" << endl;}
	Vec(const Vec& obj):v(obj.v){ cout << "Copy Ctor" << endl;}
	Vec(const Vec&& obj) :v(obj.v){ cout << "Move Ctor" << endl;}
	~Vec(){cout << "Dtor" << endl;}
};

int main(){

	std::vector<int> v{1,2,3,4,5,6}; // Initilizer list 
	std::vector<int> v1(5, 1); // create 5 elements fill with zero;
	std::vector<int> v2; // Default 
	v2.push_back(5); // creates a new object by copying the value of int, and adds this new object to the end of the vector.
	v2.emplace_back(4); //  Emplace is Used to construct the object in-place and avoid the unnessaray copy of objects.
	{
		std::vector<Vec> vec;
		cout << "*** push back **** " << endl;
		vec.push_back(Vec(1));	
		/*
			Ctor
			Move Ctor
			Dtor
		*/
	}

	{
		std::vector<Vec> vec;
		cout << "*** emplace back **** " << endl;
		vec.emplace_back(2); // it will not call the copy or Move ctor this is the advantage 
		// If you can Vec(2) insted of 2 then same behavior as push_back
		/*
		Ctor
		*/
	}
	cout << "\nElements of the vector v:";
	for(int i = 0; i < v.size(); i++){
		cout << v[i] << " ";
	}

	v1[2] = 10; // Random access
	
	cout << "\nElements of the vector v1:";
	for(int i = 0; i < v1.size(); i++){
		cout << v1[i] << " ";
	}

  // Resize the vector and fill the new elements with 0
	v.resize(10, 0);
	// Iterate through the vector using iterators
	cout << "\nElements of the vector v using iterators:";
	for(auto it = v.begin(); it != v.end(); it++) {
		std::cout << *it << " ";
	}

	// Remove elements that are equal to Zero
	auto checkZero = [](int x) {return x == 0;};
	v.erase(std::remove_if(v.begin(), v.end(), checkZero), v.end());

	cout << "\nElements of the vector v using iterators after removing the zeros:";
	for(auto it = v.begin(); it != v.end(); it++) {
		std::cout << *it << " ";
	}
	
	cout << "\nv.at(2): "<< v.at(2) << endl; // prints 2nd postion value.	
	try{
		//No bounds checking
		cout << "\nv2.at(2): "<< v2.at(2) << endl; // Error:v2.at(2): vector::_M_range_check: __n (which is 2) >= this->size() (which is 2)
	}catch(exception &e){
		cout << e.what() << endl;
	}

	return 0;
}
/*
output:
Elements of the vector v:1 2 3 4 5 6
Elements of the vector v1:111011
v.at(2): 3

v2.at(2): vector::_M_range_check: __n (which is 2) >= this->size() (which is 2)
*/