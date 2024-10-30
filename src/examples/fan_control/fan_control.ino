#include "AITINKR_SHIELDS.h"

// Instantiate the SingleChannelControl class for the fan
SingleChannelControl fanControl;

// Variable to control fan speed
int fanSpeed = 0;       // Initial fan speed (PWM value)
bool fanOn = false;     // Fan on/off state

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);
    
    // Initialize fan control on the RIGHT channel
    fanControl.init(RIGHT);

    // Start with fan off
    fanControl.stop();
    Serial.println("Fan OFF (Stopped)");
}

void loop() {
    // If the fan is off, turn it on and gradually increase the speed
    if (!fanOn) {
        Serial.println("Turning fan ON...");
        for (fanSpeed = 0; fanSpeed <= 255; fanSpeed += 25) {
            fanControl.setSpeed(fanSpeed);  // Set the fan speed
            fanControl.forward();           // Make the fan spin
            Serial.print("Fan ON - Speed: ");
            Serial.println(fanSpeed);
            delay(500);  // Delay to gradually increase speed
        }
        fanOn = true;  // Set the fan to "on" state
    } else {
        // If the fan is on, stop it
        Serial.println("Turning fan OFF...");
        fanControl.stop();  // Stop the fan
        Serial.println("Fan OFF (Stopped)");
        fanOn = false;  // Set the fan to "off" state
    }

    delay(2000);  // Delay between each fan on/off cycle
}
