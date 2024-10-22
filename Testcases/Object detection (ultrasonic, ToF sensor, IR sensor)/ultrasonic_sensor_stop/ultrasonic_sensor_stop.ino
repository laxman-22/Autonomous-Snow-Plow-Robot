#include "Motors.h"
#include "Ultrasonic.h"
#include "Pins.h"

//flags
bool end = false;

//initialize sensors and motor classes
Ultrasonic ultrasonic = Ultrasonic();
Motors motors = Motors();


void setup() {
  Serial.begin(9600);
  //initialise interrupt handlers for object detector
  ultrasonic.init();
  Serial.println("Setup finished");
  delay(500);
}

void loop() {
  //Serial.println("loop");

  //Serial.print("Distance:" );
  //Serial.println(ultrasonic.get_distance());

  if (!end) {
    if (ultrasonic.detected() && ultrasonic.get_distance() <= MIN_DISTANCE_TO_OBJECT) {
      Serial.println("Object Detected. Stopping");
      end = true;
      motors.stop();
    } else {
      motors.forward();
    }
  }
}