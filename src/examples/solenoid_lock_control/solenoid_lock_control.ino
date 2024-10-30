#include "AITINKR_SHIELDS.h"

// Instantiate the DigitalControl class for the solenoid lock
DigitalControl solenoidLock;

void setup() {
    // Initialize serial communication for debugging
    Serial.begin(115200);
    
    // Initialize the solenoid lock on the LEFT channel
    solenoidLock.init(LEFT);
}

void loop() {
    // Unlock the solenoid lock
    Serial.println("Unlocking the solenoid lock...");
    solenoidLock.on();  // Unlock the solenoid lock
    Serial.println("Solenoid Lock ON (Unlocked)");
    delay(2000);  // Keep the lock open for 2 seconds

    // Lock the solenoid lock
    Serial.println("Locking the solenoid lock...");
    solenoidLock.off();  // Lock the solenoid lock
    Serial.println("Solenoid Lock OFF (Locked)");
    delay(2000);  // Keep the lock closed for 2 seconds
}
