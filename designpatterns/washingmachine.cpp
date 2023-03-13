#include <iostream>
#include <chrono>
#include <thread>

class WashingMachine;

class State {
public:
    virtual void start(WashingMachine* machine) = 0;
    virtual void pause(WashingMachine* machine) = 0;
    virtual void stop(WashingMachine* machine) = 0;
};

class IdleState : public State {
public:
    void start(WashingMachine* machine) override;
    void pause(WashingMachine* machine) override;
    void stop(WashingMachine* machine) override;
};

class FillState : public State {
public:
    void start(WashingMachine* machine) override;
    void pause(WashingMachine* machine) override;
    void stop(WashingMachine* machine) override;
};

class WashState : public State {
public:
    void start(WashingMachine* machine) override;
    void pause(WashingMachine* machine) override;
    void stop(WashingMachine* machine) override;
};

class DrainState : public State {
public:
    void start(WashingMachine* machine) override;
    void pause(WashingMachine* machine) override;
    void stop(WashingMachine* machine) override;
};

class SpinState : public State {
public:
    void start(WashingMachine* machine) override;
    void pause(WashingMachine* machine) override;
    void stop(WashingMachine* machine) override;
};

class WashingMachine {
private:
    State* currentState;
public:
    WashingMachine() {
        currentState = new IdleState();
    }

    void setState(State* state) {
        currentState = state;
    }

    void start() {
        currentState->start(this);
    }

    void pause() {
        currentState->pause(this);
    }

    void stop() {
        currentState->stop(this);
    }
};

void IdleState::start(WashingMachine* machine) {
    std::cout << "Filling the washing machine with water\n";
    machine->setState(new FillState());
}

void IdleState::pause(WashingMachine* machine) {
    std::cout << "The washing machine is already paused\n";
}

void IdleState::stop(WashingMachine* machine) {
    std::cout << "The washing machine is already stopped\n";
}

void FillState::start(WashingMachine* machine) {
    std::cout << "The washing machine is already filling with water\n";
}

void FillState::pause(WashingMachine* machine) {
    std::cout << "Pausing the washing machine while filling\n";
    machine->setState(new IdleState());
}

void FillState::stop(WashingMachine* machine) {
    std::cout << "Stopping the washing machine while filling\n";
    machine->setState(new IdleState());
}

void WashState::start(WashingMachine* machine) {
    std::cout << "The washing machine is already washing\n";
}

void WashState::pause(WashingMachine* machine) {
    std::cout << "Pausing the washing machine while washing\n";
    machine->setState(new IdleState());
}

void WashState::stop(WashingMachine* machine) {
    std::cout << "Stopping the washing machine while washing\n";
    machine->setState(new IdleState());
}

void DrainState::start(WashingMachine* machine) {
    std::cout << "The washing machine is already draining\n";
}

void DrainState::pause(WashingMachine* machine) {
    std::cout << "Pausing the washing machine while draining\n";
    machine->setState(new IdleState());
}

void DrainState::stop(WashingMachine* machine) {
    std::cout << "Stopping the washing machine while draining\n";
    machine->setState(new IdleState());
}

void Spin
