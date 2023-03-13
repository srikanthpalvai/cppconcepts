/*
State machine Design pattern
Is useful in situations where an object can be in different states and the behavior of the object depends on its current state.
ఒక వస్తువు వివిధ స్థితులలో ఉండి, ఆ వస్తువు యొక్క ప్రవర్తన దాని ప్రస్తుత స్థితిపై ఆధారపడి ఉండే సందర్భాలలో ఉపయోగపడుతుంది.
object can be in one of several states at any given time, and its behavior can change depending on the current state


Vending machine: A vending machine is a common example of a state machine.
When a customer inserts money, the machine enters a state where it waits for the customer to make a selection. Once the customer selects an item,
the machine enters a state where it dispenses the item and returns change.
Elevator: An elevator is another example of a state machine.
The elevator can be in different states, such as moving up, moving down, or stopped. The elevator moves to different floors based on user input and the state of the elevator.
Washing machine: A washing machine is a state machine that goes through different states, such as filling with water, agitating, draining, and spinning. These states are triggered by user input and the current state of the machine.
Traffic light: As mentioned earlier, a traffic light is a state machine that goes through different states, such as red, yellow, and green. The state of the traffic light changes based on a predetermined schedule or based on sensor input.
Game AI: In game development, state machines can be used to create AI that responds to different inputs and events. For example, a character in a game can have different states, such as idle, attacking, or fleeing, and can transition between states based on user input or the state of the game world.
*/

#include <iostream>
#include <chrono>
#include <thread>

class TrafficLight;

class State {
public:
    virtual void changeState(TrafficLight* light) = 0;
};

class RedState : public State {
public:
    void changeState(TrafficLight* light) override;
};

class YellowState : public State {
public:
    void changeState(TrafficLight* light) override;
};

class GreenState : public State {
public:
    void changeState(TrafficLight* light) override;
};

class TrafficLight {
private:
    State* currentState;
public:
    TrafficLight() {
        currentState = new RedState();
    }

    void setState(State* state) {
        currentState = state;
    }

    void change() {
        currentState->changeState(this);
    }
};

void RedState::changeState(TrafficLight* light) {
    std::cout << "Red light on\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    light->setState(new GreenState());
}

void YellowState::changeState(TrafficLight* light) {
    std::cout << "Yellow light on\n";
    std::this_thread::sleep_for(std::chrono::seconds(2));
    light->setState(new RedState());
}

void GreenState::changeState(TrafficLight* light) {
    std::cout << "Green light on\n";
    std::this_thread::sleep_for(std::chrono::seconds(5));
    light->setState(new YellowState());
}

int main() {
    TrafficLight* light = new TrafficLight();

    while (true) {
        light->change();
    }

    return 0;
}
