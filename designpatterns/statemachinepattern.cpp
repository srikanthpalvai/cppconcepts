/*
In this implementation, the TrafficLight class has three states (Green, Yellow, and Red) and transitions between these states based on a timer event. When the timer expires, the onTimerExpired() method is called, which transitions the traffic light to the next state and starts a new timer for the appropriate duration.
324ersdxz
+For example, when the traffic light is in the Green state, the timer is set for the duration of the green light (greenTime). When the timer expires, the traffic light transitions to the Yellow state and starts a new timer for the duration of the yellow light (yellowTime).
*/
#include <chrono>
#include <thread>
#include <iostream>

class TrafficLight {
public:
    enum State { Green, Yellow, Red };
    
    TrafficLight() {
        startTimer(greenTime_);
    }
    void getState(){ std::cout << "State:" << state_ << std::endl;}
    void onTimerExpired() {
        switch (state_) {
            case Green:
                state_ = Yellow;
                startTimer(yellowTime_);
                break;
            case Yellow:
                state_ = Red;
                startTimer(redTime_);
                break;
            case Red:
                state_ = Green;
                startTimer(greenTime_);
                break;
        }
    }
    
private:
    State state_ = Green;
    int greenTime_ = 60;
    int yellowTime_ = 5;
    int redTime_ = 55;
    
    void startTimer(int seconds) {
        std::this_thread::sleep_for(std::chrono::seconds(seconds));
        onTimerExpired();
    }
};

int main() {
    TrafficLight trafficLight;
    std::cout << "main" << std::endl;
    while (true) {
        // do something else while the traffic light is changing states...
		trafficLight.getState();
    }
    
    return 0;
}
