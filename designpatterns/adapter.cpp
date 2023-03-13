#include <iostream>
using namespace std;

// The target interface
class ThreePinPlug {
public:
    virtual void plugIntoThreePinOutlet() = 0;
};

// The adaptee interface
class TwoPinPlug {
public:
    virtual void plugIntoTwoPinOutlet() = 0;
};

// The adaptee class
class TwoPinDevice : public TwoPinPlug {
public:
    void plugIntoTwoPinOutlet() override {
        // Implementation of plugging into two-pin outlet
        std::cout << "Device plugged into a two-pin outlet." << std::endl;
    }
};

// The adapter class
class TwoToThreePinAdapter : public ThreePinPlug {
private:
    TwoPinPlug* twoPinDevice;
public:
    TwoToThreePinAdapter(TwoPinPlug* twoPinDevice) {
        this->twoPinDevice = twoPinDevice;
    }
    void plugIntoThreePinOutlet() override {
        // Implementation of plugging into three-pin outlet
        std::cout << "Adapter is adapting the two-pin device to the three-pin outlet." << std::endl;
        twoPinDevice->plugIntoTwoPinOutlet();
        std::cout << "Ground pin connected to the device." << std::endl;
    }
};

// The client code
int main() {
    // Create a two-pin device and adapt it to the three-pin outlet
    TwoPinDevice* device = new TwoPinDevice();
    ThreePinPlug* adapter = new TwoToThreePinAdapter(device);

    // Plug the adapter into the three-pin outlet
    adapter->plugIntoThreePinOutlet();

    // Cleanup
    delete adapter;
    delete device;

    return 0;
}
