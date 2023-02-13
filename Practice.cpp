/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <memory>
using namespace std;

class Base{
    int val;
    public:
    static int count;
    Base(){
        val = 1;
        count++;
        cout << "Base Ctor" << count <<endl;

    }
    virtual void getval()
    {
        cout << "Base getval" << val << endl;
    }
    void getcount(){
        cout << "get count" << count << endl;
    }    
    ~Base(){
        cout << "Base Dtor" << endl;
    }
};
int Base::count = 0;
class Derived:public Base{
    int dval;
    public:
    Derived(){
        dval = 2;
        cout << "Derived Ctor" << endl;
    }
    void getval() final{ // Derived1 can not contain getval method, Because we are making here final 
        cout << "Derived getval" << dval << endl;
    }

    ~Derived(){
        cout << "Derived Dtor " << endl;
    }
    
};
class Derived1:public Derived{
    int dval;
    public:
    Derived1(){
        dval = 2;
        cout << "D ctor" << endl;
    }
    ~Derived1(){
        cout << "D Dtor " << endl;
    }
};
int main()
{
    Base *bp = new Derived();
    bp->getval();
    delete bp; // Make sure when ever deleting the base pointer, Check base class distructor whether it's Virtual or not
	
	cout << "\n \n";
	{	// If you go with shared pointer we no need to worry about the virtual distructor of Derived calss 
		std::shared_ptr<Base> sbp = std::make_shared<Derived>();
	}
	cout << "\n \n";
    Base *abp = new Derived[5];
    for(int i = 0;i<=5;i++){
        //abp[i]->getcount(); you can't access with abp[i]->
        abp[i].getcount(); 
        (abp+i)->getcount();
    }
	
	std::unique_ptr<int> up = std::make_unique<int>(100);
	//std::unique_ptr<Vec3> v1 = std::make_unique<Vec3>();
	cout << "up.get():" << up.get() << endl;
	auto up1 = move(up);
	cout << "up1.get():" << up1.get() << endl;
	std::shared_ptr<int> sp = std::make_shared<int>(100);
	cout << "sp.get():" << sp.get() << endl;
	cout << "sp.count():" << sp.use_count() << endl;
	auto sp1 = sp;
	cout << "sp1.get():" << sp1.get() << endl;
	cout << "sp1.count():" << sp1.use_count() << endl;
    
    return 0;
}
