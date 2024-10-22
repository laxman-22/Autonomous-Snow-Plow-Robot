#include "LineFollower.h"

LineFollower* LineFollower::lineFollower_instance = NULL;

LineFollower::LineFollower() {
  this->digital_pin = LINE_FOLLOWER_DIGITAL_PIN;
  this->analog_pin = LINE_FOLLOWER_ANALOG_PIN;
  this->consecutive_detections = 0;

  //necessary for interrupts
  lineFollower_instance = this;
  pinMode(this->digital_pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->digital_pin), LineFollower_ISR, CHANGE);
}

void LineFollower::detect() {
  if (analogRead(this->analog_pin) >= BLACK_ANALOG_READ_THRESHOLD) {
    this->consecutive_detections++;
  } else {
    this->consecutive_detections = 0;
  }
}

bool LineFollower::detected() {
  if (this->consecutive_detections >= NUM_CONSECUTIVE_DETECTIONS_LINE_SENSOR) {
    return true;
  } else {
    return false;
  }
}