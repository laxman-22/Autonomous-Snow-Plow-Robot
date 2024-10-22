#include "LineFollower.h"

LineFollower* LineFollower::lineFollower_instance = NULL;

LineFollower::LineFollower() {
  this->line = false;
  this->first_detect = false;
  this->pin = LINE_FOLLOWER_PIN;
  pinMode(this->pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(this->pin), LineFollower_ISR, CHANGE);

  //necessary for interrupts
  lineFollower_instance = this;
}

void LineFollower::detect() {
  if (digitalRead(this->pin)) {
    if (!this->first_detect){ 
      this->first_detect = true;
    } else {
      this->line = true;
    }
  } else {
    this->line = false;
    this->first_detect = false;
  }
}

bool LineFollower::detected() {
  return this->line;
}