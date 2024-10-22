#ifndef IRSENSOR_h
#define IRSENSOR_h

#include "Arduino.h"
#include "Pins.h"
#include "Robot_Measurements.h"

class IRSensor {
private:
  volatile int consecutive_detections;
  int pin;
public:
  IRSensor();
  void init();
  void detect();
  bool detected();

  //for enabling interrupts
  static IRSensor* ir_instance;
  static void IR_ISR() {
    if (IRSensor::ir_instance != NULL) {
      IRSensor::ir_instance->detect();
    }
  }
};

#endif