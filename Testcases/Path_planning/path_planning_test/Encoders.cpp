#include "Encoders.h"
#include "Pins.h"


Encoders* Encoders::encoders_instance = NULL;

Encoders::Encoders() { 
  this->encoder_pins[0] = WHEEL_ENCODER_1_PIN;
  this->encoder_counts[0] = 0;

  this->encoder_pins[1] = WHEEL_ENCODER_2_PIN;
  this->encoder_counts[1] = 0;

  this->measuring = false;

  //necessary for interrupts
  encoders_instance = this;
}

void Encoders::start_measure() { 
  this->measuring = true;
  reset_counts();
  attachInterrupt(digitalPinToInterrupt(this->encoder_pins[0]), encoder1_interrupt, HIGH);
  attachInterrupt(digitalPinToInterrupt(this->encoder_pins[1]), encoder2_interrupt, HIGH);
}

void Encoders::end_measure() { 
  this->measuring = false;
  detachInterrupt(digitalPinToInterrupt(this->encoder_pins[0]));
  detachInterrupt(digitalPinToInterrupt(this->encoder_pins[1]));
}

void Encoders::encoder1_count() { 
  this->encoder_counts[0]++;
}

void Encoders::encoder2_count() { 
  this->encoder_counts[1]++;
}

void Encoders::reset_counts(){ 
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
  return (this->encoder_counts[0]+this->encoder_counts[1])/2;
}

bool Encoders::is_measuring() { 
  return this->measuring;
}