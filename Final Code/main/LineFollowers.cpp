#include "LineFollowers.h"

LineFollowers* LineFollowers::lineFollower_instance[2] = { NULL, NULL };
int LineFollowers::instance = 0;

LineFollowers::LineFollowers(int digital_pin, int analog_pin) {
  this->digital_pin = digital_pin;
  this->analog_pin = analog_pin;
  this->consecutive_detections = 0;
}

void LineFollowers::init() {
  //necessary for interrupts
  pinMode(this->digital_pin, INPUT);

  if (instance == 0) {
    attachInterrupt(digitalPinToInterrupt(this->digital_pin), LineFollower0_ISR, CHANGE);
  } else {
    attachInterrupt(digitalPinToInterrupt(this->digital_pin), LineFollower1_ISR, CHANGE);
  }
  lineFollower_instance[instance] = this;
  instance++;
}

void LineFollowers::detect() {
  if (analogRead(this->analog_pin) >= BLACK_ANALOG_READ_THRESHOLD) {
    this->consecutive_detections++;
  } else {
    this->consecutive_detections = 0;
  }
}

bool LineFollowers::detected() {
  if (this->consecutive_detections >= NUM_CONSECUTIVE_DETECTIONS_LINE_SENSOR) {
    this->consecutive_detections = 0;  //reset count
    return true;
  } else {
    return false;
  }
}