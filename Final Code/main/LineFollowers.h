#ifndef LINEFOLLOWERS_h
#define LINEFOLLOWERS_h

#include "Arduino.h"
#include "Pins.h"
#include "Robot_Measurements.h"

class LineFollowers {
private:
  volatile int consecutive_detections;
  int digital_pin;
  int analog_pin;
  static int instance; 

public:
  LineFollowers(int digital_pin, int analog_pin);
  void init();
  void detect();
  bool detected();

  //for enabling interrupts
  static LineFollowers* lineFollower_instance[2];
  static void LineFollower0_ISR() {
    if (LineFollowers::lineFollower_instance[0] != NULL) {
      LineFollowers::lineFollower_instance[0]->detect();
    }
  }
    static void LineFollower1_ISR() {
    if (LineFollowers::lineFollower_instance[1] != NULL) {
      LineFollowers::lineFollower_instance[1]->detect();
    }
  }
};

#endif