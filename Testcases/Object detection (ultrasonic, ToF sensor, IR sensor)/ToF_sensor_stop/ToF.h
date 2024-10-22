#ifndef TOF_h
#define TOF_h

#include <Wire.h>
#include <VL53L1X.h>
#include "Arduino.h"
#include "Pins.h"

class ToF { 
  private: 
    VL53L1X sensor;
    uint8_t address;
  public: 
    ToF(uint8_t address);
    bool init();
    void start_continuous();
    void stop_continuous();
    uint16_t get_distance(); // return distance in cm
};

#endif