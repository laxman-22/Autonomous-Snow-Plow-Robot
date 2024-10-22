#include "Encoders.h"
#include "Pins.h"

Encoders* Encoders::encoders_instance = NULL;

Encoders::Encoders() {
  this->encoder_pins[0] = WHEEL_ENCODER_1_PIN;
  this->encoder_counts[0] = 0;
  this->counted[0] = false;

  this->encoder_pins[1] = WHEEL_ENCODER_2_PIN;
  this->encoder_counts[1] = 0;
  this->counted[1] = false;

  pinMode(this->encoder_pins[0], INPUT);
  pinMode(this->encoder_pins[1], INPUT);
  attachInterrupt(digitalPinToInterrupt(this->encoder_pins[0]), encoder1_interrupt, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(this->encoder_pins[1]), encoder2_interrupt, CHANGE);

  //necessary for interrupts
  encoders_instance = this;
}

void Encoders::encoder1_count() {
  if (digitalRead(this->encoder_pins[0]) == 1) {
    if (this->counted[0] == false) {
      this->encoder_counts[0] += 1;
      this->counted[0] = true;
    }
  } else {
    this->counted[0] = false;
  }
}

void Encoders::encoder2_count() {
  if (digitalRead(this->encoder_pins[1]) == 1) {
    if (this->counted[1] == false) {
      this->encoder_counts[1] += 1;
      this->counted[1] = true;
    } else {
      this->counted[1] = false;
    }
  }
}

void Encoders::reset_counts() {
  this->encoder_counts[0] = 0;
  this->encoder_counts[1] = 0;
}

int Encoders::get_encoder1_count() {
  return this->encoder_counts[0];
}

int Encoders::get_encoder2_count() {
  return this->encoder_counts[1];
}

int Encoders::get_average_encoder_count() {
  return (this->encoder_counts[0] + this->encoder_counts[1]) / 2;
}