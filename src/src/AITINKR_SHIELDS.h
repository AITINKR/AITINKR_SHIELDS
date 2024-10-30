#ifndef AITINKR_SHIELDS_H
#define AITINKR_SHIELDS_H

#include <Arduino.h>

// Define motor control pins compatible with Arduino Uno (ATmega328)
#define motorRF 8  // Right Front (Digital Pin)
#define motorRB 7  // Right Back (Digital Pin)
#define motorLF 12 // Left Front (Digital Pin)
#define motorLB 13 // Left Back (Digital Pin)

#define motorRS 5 // Right Speed PWM (PWM Pin)
#define motorLS 6 // Left Speed PWM (PWM Pin)

// Define ultrasonic sensor pins compatible with Arduino Uno (ATmega328)
#define t1 A1 // Trigger pin for ultrasonic sensor 1
#define c1 A0 // Echo pin for ultrasonic sensor 1
#define t2 A3 // Trigger pin for ultrasonic sensor 2
#define c2 A2 // Echo pin for ultrasonic sensor 2
#define t3 A5 // Trigger pin for ultrasonic sensor 3
#define c3 A4 // Echo pin for ultrasonic sensor 3

// Enum to define LEFT and RIGHT channels
enum Channel
{
    LEFT,
    RIGHT
};

/**
 * @brief Ultrasonic class for handling distance measurement using an ultrasonic sensor.
 */
class Ultrasonic
{
public:
    Ultrasonic(uint8_t port); // Constructor for initializing the Ultrasonic sensor with a specific port
    unsigned int read();      // Get the distance measured by the ultrasonic sensor

private:
    uint8_t trig;                    // Trigger pin for the ultrasonic sensor.
    uint8_t echo;                    // Echo pin for the ultrasonic sensor.
    unsigned long previousMicros_us; // Used to store timing for ultrasonic measurement.

    unsigned int getDis(); // Internal method to get the raw distance in microseconds.
};

/**
 * @brief Motor class for controlling two motors with speed and offset functionality.
 */
class motor
{
public:
    void init();               // Initialize the motor pins
    void setSpeed(uint8_t sp); // Set the speed of the motors
    void setOffset(int of);    // Set an offset value to balance the left and right motor speeds
    void forward();            // Move the motors forward
    void forword();            // Move the motors forward (old method)
    void backward();           // Move the motors backward
    void backword();           // Move the motors backward (old method)
    void right();              // Turn the robot to the right
    void left();               // Turn the robot to the left
    void stop();               // Stop the motors

private:
    int speed;  // Speed value for the motors (0-255)
    int Offset; // Offset value to balance motor performance
};

/**
 * @brief DigitalControl class: Provides methods to control a device using simple on/off signals.
 */
class DigitalControl
{
public:
    void init(Channel channel); // Initialize the pins for digital control with enum channel selection (LEFT or RIGHT)
    void on();                  // Turn the selected channel on (HIGH)
    void off();                 // Turn the selected channel off (LOW)

private:
    int motorPinA = -1; // GPIO pin for the motor direction A (forward)
    int motorPinB = -1; // GPIO pin for the motor direction B (backward)
    int motorPinS = -1; // GPIO pin for the motor speed
    int pwmValue = 255; // Default PWM value (max speed)
};

/**
 * @brief SingleChannelControl class: Provides methods to control a motor using PWM for speed and direction control.
 */
class SingleChannelControl
{
public:
    void init(Channel channel); // Initialize the motor control pins with enum channel selection (LEFT or RIGHT)
    void setSpeed(int pwm);     // Set the speed of the motor using PWM
    void forward();             // Set the motor direction to forward
    void backward();            // Set the motor direction to backward
    void stop();                // Stop the motor

private:
    int motorPinA = -1; // GPIO pin for the motor direction A (forward)
    int motorPinB = -1; // GPIO pin for the motor direction B (backward)
    int motorPinS = -1; // GPIO pin for the motor speed
    int pwmValue = 255; // Default PWM value (max speed)
};

#endif // AITINKR_SHIELDS_H
