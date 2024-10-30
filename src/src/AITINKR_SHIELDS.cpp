#include "AITINKR_SHIELDS.h"

#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Ultrasonic class methods

Ultrasonic::Ultrasonic(uint8_t port)
{
    switch (port)
    {
    case 1:
        trig = t1;
        echo = c1;
        break;
    case 2:
        trig = t2;
        echo = c2;
        break;
    case 3:
        trig = t3;
        echo = c3;
        break;
    default:
        trig = t1;
        echo = c1;
        break;
    }
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
}

unsigned int Ultrasonic::getDis()
{
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    previousMicros_us = micros();
    while (!digitalRead(echo) && (micros() - previousMicros_us) <= 20000UL)
        ;
    previousMicros_us = micros();
    while (digitalRead(echo) && (micros() - previousMicros_us) <= 20000UL)
        ;

    return micros() - previousMicros_us;
}

unsigned int Ultrasonic::read()
{
    return getDis() / 58;
}

// Motor class methods

void motor::init()
{
    pinMode(motorRF, OUTPUT);
    pinMode(motorRB, OUTPUT);
    pinMode(motorRS, OUTPUT);
    pinMode(motorLF, OUTPUT);
    pinMode(motorLB, OUTPUT);
    pinMode(motorLS, OUTPUT);

    speed = 255;
    Offset = 0;
}

void motor::setSpeed(uint8_t sp)
{
    speed = sp;
}

void motor::setOffset(int of)
{
    Offset = of;
}

void motor::forward()
{
    analogWrite(motorRS, constrain(speed - Offset, 0, 255));
    analogWrite(motorLS, constrain(speed + Offset, 0, 255));
    digitalWrite(motorRF, HIGH);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLF, HIGH);
    digitalWrite(motorLB, LOW);
}

void motor::forword()
{
    forward();
}

void motor::backward()
{
    analogWrite(motorRS, constrain(speed - Offset, 0, 255));
    analogWrite(motorLS, constrain(speed + Offset, 0, 255));
    digitalWrite(motorRF, LOW);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLF, LOW);
    digitalWrite(motorLB, HIGH);
}

void motor::backword()
{
    backward();
}

void motor::right()
{
    analogWrite(motorRS, constrain(speed - Offset, 0, 255));
    analogWrite(motorLS, constrain(speed + Offset, 0, 255));
    digitalWrite(motorRF, LOW);
    digitalWrite(motorRB, HIGH);
    digitalWrite(motorLF, HIGH);
    digitalWrite(motorLB, LOW);
}

void motor::left()
{
    analogWrite(motorRS, constrain(speed + Offset, 0, 255));
    analogWrite(motorLS, constrain(speed - Offset, 0, 255));
    digitalWrite(motorRF, HIGH);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLF, LOW);
    digitalWrite(motorLB, HIGH);
}

void motor::stop()
{
    analogWrite(motorRS, 0);
    analogWrite(motorLS, 0);
    digitalWrite(motorRF, LOW);
    digitalWrite(motorRB, LOW);
    digitalWrite(motorLF, LOW);
    digitalWrite(motorLB, LOW);
}

// DigitalControl class methods

void DigitalControl::init(Channel channel)
{

    if (channel == LEFT)
    {
        motorPinA = motorLF;
        motorPinB = motorLB;
        motorPinS = motorLS;
    }
    else if (channel == RIGHT)
    {
        motorPinA = motorRF;
        motorPinB = motorRB;
        motorPinS = motorRS;
    }
    else
    {
        Serial.println("ERROR: Invalid channel. Use LEFT or RIGHT.");
        return;
    }
    pinMode(motorPinA, OUTPUT);
    pinMode(motorPinB, OUTPUT);
    off();
}

void DigitalControl::on()
{
    digitalWrite(motorPinS, 1);
    digitalWrite(motorPinA, 1);
    digitalWrite(motorPinB, 0);
}

void DigitalControl::off()
{
    digitalWrite(motorPinS, 0);
    digitalWrite(motorPinA, 0);
    digitalWrite(motorPinB, 0);
}

// SingleChannelControl class methods

void SingleChannelControl::init(Channel channel)
{

    if (channel == LEFT)
    {
        motorPinA = motorLF;
        motorPinB = motorLB;
        motorPinS = motorLS;
    }
    else if (channel == RIGHT)
    {
        motorPinA = motorRF;
        motorPinB = motorRB;
        motorPinS = motorRS;
    }
    else
    {
        Serial.println("ERROR: Invalid channel. Use LEFT or RIGHT.");
        return;
    }
    pinMode(motorPinA, OUTPUT);
    pinMode(motorPinB, OUTPUT);
    stop();
}

void SingleChannelControl::setSpeed(int pwm)
{
    pwmValue = constrain(pwm, 0, 255);
}

void SingleChannelControl::forward()
{
    analogWrite(motorPinS, pwmValue);
    digitalWrite(motorPinA, HIGH);
    digitalWrite(motorPinB, LOW);
}

void SingleChannelControl::backward()
{
    analogWrite(motorPinS, pwmValue);
    digitalWrite(motorPinA, LOW);
    digitalWrite(motorPinB, HIGH);
}

void SingleChannelControl::stop()
{
    digitalWrite(motorPinS, 0);
    digitalWrite(motorPinA, 0);
    digitalWrite(motorPinB, 0);
}
