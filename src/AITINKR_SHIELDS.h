#ifndef AITINKR_SHIELDS_h
#define AITINKR_SHIELDS_h


class Ultrasonic {

public:

  Ultrasonic(uint8_t port);
  unsigned int read();

private:
  uint8_t trig;
  uint8_t echo;
  unsigned long previousMicros;
  unsigned long timeout;
  unsigned int getDis();
};

// class motor {

// public:
//   void motor::init();
//   void motor::setSpeed(uint8_t sp);
//   void motor::forword();
//   void motor::backword();
//   void motor::right();
//   void motor::left();
//   void motor::stop();


private:
};



#endif  // AITINKR_SHIELDS_h
