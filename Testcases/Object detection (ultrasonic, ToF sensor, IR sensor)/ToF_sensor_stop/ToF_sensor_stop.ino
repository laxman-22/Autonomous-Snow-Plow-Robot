#include "ToF.h"
#include "Motors.h"

#define MIN_DISTANCE 5  //5 cm

//flags
bool end = false;

//initialize sensors and motor classes
ToF tof = ToF(0x2A);
Motors motors = Motors();

void setup() {
  Serial.begin(9600);

  //shut off all TOF sensor
  pinMode(TOF_RIGHT_XSHUT_PIN, OUTPUT);
  digitalWrite(TOF_LEFT_XSHUT_PIN, LOW);

  pinMode(TOF_RIGHT_XSHUT_PIN, OUTPUT);
  digitalWrite(TOF_LEFT_XSHUT_PIN, LOW);

  //enable one TOF sensor
  pinMode(TOF_RIGHT_XSHUT_PIN, INPUT);
  delay(10); //wait for it to start up

  //initialise interrupt handlers for object detector
  if (!tof.init()) {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  Serial.println("Setup complete. delay momentarily");
  delay(5000);  //delay 5 seconds to give user time to set up
  Serial.println("Run");
}

void loop() {
  if (!end) {
    Serial.print("loop");

    if (tof.get_distance() <= MIN_DISTANCE) {
      end = true;
      motors.stop();
      Serial.println("Object detected.  stopping");
    } else {
      motors.forward();
    }
  }
}
