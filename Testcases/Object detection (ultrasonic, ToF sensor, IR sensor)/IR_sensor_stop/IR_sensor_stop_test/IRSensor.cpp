#include "IRSensor.h"

IRSensor* IRSensor::ir_instance = NULL;

IRSensor::IRSensor() {
  this->consecutive_detections = 0;
  this->pin = IR_PIN;
}

void IRSensor::init() { 
  pinMode(this->pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->pin), IR_ISR, CHANGE);

  //necessary for interrupts
  ir_instance = this;
}

void IRSensor::detect() {
  if (digitalRead(this->pin) == 0) {
    this->consecutive_detections++;
  } else {
    this->consecutive_detections = 0;
  }
}

bool IRSensor::detected() {
  if (this->consecutive_detections >= NUM_CONSECUTIVE_DETECTIONS_IR_SENSOR) {
    this->consecutive_detections = 0;  //reset count
    return true;
  } else {
    return false;
  }
}