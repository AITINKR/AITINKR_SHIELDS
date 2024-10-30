#include "AITINKR_SHIELDS.h"

// Instantiate the Ultrasonic sensor on port 1
Ultrasonic ultrasonicSensor(1);

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);
}

void loop() {
    // Read the distance from the ultrasonic sensor
    unsigned int distance = ultrasonicSensor.read();

    // Print the distance to the serial monitor
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(1000);  // Wait for 1 second before taking the next reading
}
