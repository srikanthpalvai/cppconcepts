#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
//points:
// traficlight: red,green,yellow.
// State,currentState, changeState

// wait timings
// red 10 seconds
// green 20 seconds
// yellow 5 seconds 
class traficlight;

class State{
	public:
	virtual void currentState(traficlight* tl) = 0;
};
class ReadState : public State{
	public:
	ReadState(){
		cout << "ReadState Ctor" << endl;
	}
	void currentState(traficlight* tl);
	~ReadState(){
		cout << "ReadState Dtor" << endl;
	}
};
class YellowState : public State{
	public:
	YellowState(){
		cout << "YellowState Ctor" << endl;
	}
	void currentState(traficlight* tl);
	~YellowState(){
		cout << "YellowState Dtor" << endl;
	}
};
class GreenState : public State{
	public:
	GreenState(){
		cout << "GreenState Ctor" << endl;
	}
	void currentState(traficlight* tl);
	~GreenState(){
		cout << "GreenState Dtor" << endl;
	}
};
class traficlight{
	public:
	traficlight(){
		state_ = new ReadState;
	}
	void setState(State* state){
		state_ = state;
	}
	void change(){
		state_->currentState(this);
	}
	private:
	State *state_;
};
void ReadState::currentState(traficlight* tl){
	cout << "ReadState state" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	tl->setState(new GreenState());
	
}
void YellowState::currentState(traficlight* tl){
	cout << "YellowState state" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	tl->setState(new ReadState());
}
void GreenState::currentState(traficlight* tl){
	cout << "GreenState state" << endl;
	std::this_thread::sleep_for(std::chrono::seconds(15));
	tl->setState(new YellowState());
}

int main(){
	traficlight* light = new traficlight();
	while(true){
		light->change();
	}
	return 0;
}