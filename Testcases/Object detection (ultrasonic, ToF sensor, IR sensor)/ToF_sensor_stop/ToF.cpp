#include "ToF.h"

#define TIMING_BUDGET 20  //timing budget of 20ms

ToF::ToF(uint8_t address) {
  this->address = address;
}

bool ToF::init() {
  Wire.begin();
  Wire.setClock(400000);  // use 400 kHz I2C

  //this->sensor = VL53L1X();

  this->sensor.setTimeout(500);
  if (!this->sensor.init()) return false;


  this->sensor.setDistanceMode(VL53L1X::Short);
  this->sensor.setMeasurementTimingBudget(TIMING_BUDGET * 1000);
  this->sensor.setAddress(this->address);
}

void ToF::start_continuous(){ 
  this->sensor.startContinuous(TIMING_BUDGET);
}

void ToF::stop_continuous(){ 
  this->sensor.stopContinuous();
}

uint16_t ToF::get_distance() {
  this->sensor.read();
  return (this->sensor.ranging_data.range_mm/10); //get distance in cm
}