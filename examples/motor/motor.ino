#include "AITINKR_SHIELDS.h"

// Instantiate the motor class
motor Motor;

void setup() {
    // Initialize the motors
    Motor.init();

    // Set the motor speed to maximum (255)
    Motor.setSpeed(255);
}

void loop() {
    // Move the motors forward
    Serial.println("Moving forward...");
    Motor.forward();
    delay(2000);  // Move forward for 2 seconds

    // Move the motors backward
    Serial.println("Moving backward...");
    Motor.backward();
    delay(2000);  // Move backward for 2 seconds

    // Turn the robot to the right
    Serial.println("Turning right...");
    Motor.right();
    delay(1000);  // Turn right for 1 second

    // Turn the robot to the left
    Serial.println("Turning left...");
    Motor.left();
    delay(1000);  // Turn left for 1 second

    // Stop the motors
    Serial.println("Stopping...");
    Motor.stop();
    delay(2000);  // Stop for 2 seconds
}
