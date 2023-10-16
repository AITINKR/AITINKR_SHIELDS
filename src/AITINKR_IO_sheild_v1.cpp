#if ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "AITINKR_IO_sheild_v1.h"

#define motorRF 8 
#define motorRB 7
#define motorLF 12
#define motorLB 13

#define motorRS 5
#define motorLS 6

#define t1 A1
#define c1 A0
#define t2 A3
#define c2 A2
#define t3 A5
#define c3 A4

unsigned int speed;

Ultrasonic::Ultrasonic(uint8_t port) {

  if (port == 1) {
    trig = t1;
    echo = c1;
    pinMode(t1, OUTPUT);
    pinMode(c1, INPUT);
  } else if (port == 2) {
    trig = t2;
    echo = c2;
    pinMode(t2, OUTPUT);
    pinMode(c2, INPUT);
  } else if (port == 3) {
    trig = t3;
    echo = c3;
    pinMode(t3, OUTPUT);
    pinMode(c3, INPUT);
  }
}

unsigned int Ultrasonic::getDis() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);


  previousMicros = micros();
  while (!digitalRead(echo) && (micros() - previousMicros) <= 20000UL)
    ;
  previousMicros = micros();
  while (digitalRead(echo) && (micros() - previousMicros) <= 20000UL)
    ;

  return micros() - previousMicros;
}


unsigned int Ultrasonic::read() {
  return getDis() / 28 / 2;
}

void motor::init() {

  pinMode(motorRF, OUTPUT), pinMode(motorRB, OUTPUT), pinMode(motorRS, OUTPUT);
  pinMode(motorLF, OUTPUT), pinMode(motorLB, OUTPUT), pinMode(motorLS, OUTPUT);
  speed = 255;
}

void motor::setSpeed(uint8_t sp) {
  speed = sp;
}

void motor::forword() {

  digitalWrite(motorLF, HIGH), digitalWrite(motorRF, HIGH), analogWrite(motorRS, speed);
  digitalWrite(motorLB, LOW), digitalWrite(motorRB, LOW), analogWrite(motorLS, speed);
}
void motor::backword() {

  digitalWrite(motorLF, LOW), digitalWrite(motorRF, LOW), analogWrite(motorRS, speed);
  digitalWrite(motorLB, HIGH), digitalWrite(motorRB, HIGH), analogWrite(motorLS, speed);
}

void motor::right() {

  digitalWrite(motorLF, HIGH), digitalWrite(motorRF, LOW), analogWrite(motorRS, speed);
  digitalWrite(motorLB, LOW), digitalWrite(motorRB, HIGH), analogWrite(motorLS, speed);
}

void motor::left() {

  digitalWrite(motorLF, LOW), digitalWrite(motorRF, HIGH), analogWrite(motorRS, speed);
  digitalWrite(motorLB, HIGH), digitalWrite(motorRB, LOW), analogWrite(motorLS, speed);
}

void motor::stop() {

  digitalWrite(motorLF, LOW), digitalWrite(motorRF, LOW), analogWrite(motorRS, 0);
  digitalWrite(motorLB, LOW), digitalWrite(motorRB, LOW), analogWrite(motorLS, 0);
}