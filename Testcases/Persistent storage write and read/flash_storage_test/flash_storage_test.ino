#include <DueFlashStorage.h>

DueFlashStorage dueFlashStorage;

void setup() {
  Serial.begin(9600);
  byte b1 = 3;
  uint8_t b2 = 1;
  dueFlashStorage.write(0, b1);
  dueFlashStorage.write(1, b2);
}

void loop() {
  // read from flash at address 0 and 1 and print them
  Serial.print("0:");
  Serial.print(dueFlashStorage.read(0));
  Serial.print(" 1:");
  Serial.print(dueFlashStorage.read(1));

  // read from address 2, increment it, print and then write incremented value back to flash storage
  uint8_t i = dueFlashStorage.read(2) + 1;
  Serial.print(" 2:");
  Serial.print(dueFlashStorage.read(2));
  dueFlashStorage.write(2, i);

  Serial.println();
  delay(1000);
}
