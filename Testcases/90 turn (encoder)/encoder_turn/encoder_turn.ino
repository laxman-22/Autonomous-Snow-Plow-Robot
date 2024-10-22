#include "Robot_Measurements.h"
#include "Encoders.h"
#include "Motors.h"
#include "Pins.h"

//flags
bool end = false;

//initialize sensors and motor classes
Encoders encoders = Encoders();
Motors motors = Motors();

void setup() {
  Serial.begin(9600);

  Serial.print("Goal pulses: ");
  Serial.println(NUMBER_OF_ENCODER_PULSES_FOR_90);

  Serial.println("Setup finished");
  delay(5000);
}

void loop() {
  Serial.print("loop ");
  //Serial.println(encoders.get_average_encoder_count());
  Serial.println(encoders.get_encoder1_count());

  if (!end) {
    //if (encoders.get_average_encoder_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {
    if (encoders.get_encoder1_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {
      end = true;
      motors.stop();
    } else {
      motors.turn_right();
    }
  }
}
