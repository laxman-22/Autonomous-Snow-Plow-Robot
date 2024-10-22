#include "Robot_Measurements.h"
#include "Encoders.h"
#include "LineFollower.h"
#include "Motors.h"
#include "Pins.h"

//flags
bool line_end = false;
bool full_stop = false;
bool turning = false;


//initialize sensors and motor classes
Encoders encoders = Encoders();
LineFollower line_follower = LineFollower();
Motors motors = Motors();

void setup() {
  Serial.begin(9600);
  //initialise interrupt handlers for line detector
  Serial.println("Setup finished");
  delay(5000);
}

void loop() {
  //Serial.println("loop");

  if (!full_stop) {
    if (!turning && line_follower.detected()) {
      Serial.println("Boundary detected.  Stopping and starting turn");
      turning = true;
      motors.stop();
      encoders.reset_counts(); //must reset encoder counts before turning
    } 
    if (!turning) {
      Serial.println("Forward");
      motors.forward();
    } 
    if (turning) {
      if (encoders.get_encoder1_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {
        Serial.println("90 degree turn completed. Stopping");
        full_stop = true;
        motors.stop();
      } else {
        Serial.println("Turning");
        motors.turn_right();
      }
    }
  }
}
