#ifndef LINEFOLLOWER_h
#define LINEFOLLOWER_h

#include "Arduino.h"
#include "Pins.h"
#include "Robot_Measurements.h"

class LineFollower { 
  private: 
    volatile int consecutive_detections;
    int digital_pin;
    int analog_pin;
  public: 
    LineFollower();
    void detect();
    bool detected();

    //for enabling interrupts
    static LineFollower* lineFollower_instance; 
    static void LineFollower_ISR() { 
      if (LineFollower::lineFollower_instance != NULL) {
        LineFollower::lineFollower_instance->detect();
      }
    }
};

#endif