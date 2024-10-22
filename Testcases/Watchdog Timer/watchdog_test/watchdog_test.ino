#include <watchdog.h>

// Defines the time for the watchdog in ms
int watchdogTime = 1000;

int counter = 0;

void watchdogSetup(void) {
  // do what you want here
}

void setup() {
  Serial.begin(9600);
  watchdogEnable(watchdogTime);
}

void loop() {
  // put your main code here, to run repeatedly:
  watchdogReset();
  Serial.println(counter);
  delay(500);
  if (counter >= 10) {
    while (true) {
      Serial.println("loop");
      delay(100);
    }
  }
  counter++;
}
