#include <DueFlashStorage.h>

//persistent storage for when disconnected from serial
DueFlashStorage flash;
uint32_t log_address;
uint8_t message_num;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  message_num = flash.read(log_address);
  Serial.print(message_num);
  log_address++;
}
