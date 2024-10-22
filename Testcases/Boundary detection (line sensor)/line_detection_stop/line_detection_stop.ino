#include "Motors.h"
#include "LineFollower.h"
#include "Pins.h"

//flags
bool end = false;

//initialize sensors and motor classes
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

  if (!end) {
    if (line_follower.detected()) {
      Serial.println("Boundary detected.  Stopping");
      end = true;
      motors.stop();
    } else {
      motors.forward();
    }
  }
}
