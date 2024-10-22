#include "Motors.h"
#include "IRSensor.h"

//flags
bool end = false;

//initialize sensors and motor classes
IRSensor ir_sensor = IRSensor();
Motors motors = Motors();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  //Initialize IR sensor 
  Serial.println("Initalize IR Sensor");
  ir_sensor.init(); 

  Serial.println("Setup finished");
  delay(500);
}

void loop() {
  if (!end) {
    Serial.println("loop");
    
    if (ir_sensor.detected()) {
      Serial.println("Object Detected. Stopping");
      end = true;
      motors.stop();
    } else {
      motors.forward();
    }
  }
}
