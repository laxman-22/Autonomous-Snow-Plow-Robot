#ifndef MOTORS_h
#define MOTORS_h

#include <CytronMotorDriver.h>
#include "Arduino.h"

class Motors { 
  private: 
    int speed; 
    CytronMD M1;
    CytronMD M2;
    CytronMD M3;
    CytronMD M4;
    bool forward_flag; 
    bool backward_flag;
    bool stop_flag; 
    bool turn_right_flag; 
    bool turn_left_flag; 
    

  public: 
    Motors();
    void stop(); 
    void forward(); 
    void backward();
    void turn_right();
    void turn_left();
    void set_speed(int speed);
    void reset_flags();
};

#endif