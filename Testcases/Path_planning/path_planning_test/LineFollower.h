#ifndef LINEFOLLOWER_h
#define LINEFOLLOWER_h

#include "Arduino.h"
#include "Pins.h"

class LineFollower { 
  private: 
    volatile bool first_detect;
    volatile bool line;
    int pin;
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