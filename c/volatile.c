#include <stdio.h>
#include <unistd.h>

volatile int sensor_value = 0; // Simulated hardware register

// Simulate an external event changing the sensor value
void simulate_hardware_change() {
    sleep(2); // Wait for 2 seconds
    sensor_value = 1; // Change the value
    printf("Sensor value changed to %d\n", sensor_value);
}

int main() {
    // Start a thread or process to simulate the hardware change
    // (For simplicity, we'll just call the function here)
    simulate_hardware_change();

    // Wait for the sensor value to change
    while (sensor_value == 0) {
        // Do nothing
    }

    printf("Sensor detected something!\n");
    return 0;
}