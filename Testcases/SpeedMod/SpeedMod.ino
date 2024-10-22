 #include "CytronMotorDriver.h"

int currentSpeed;
// Configure the motor driver.
CytronMD motor(PWM_DIR, 3, 4);  // PWM = Pin 3, DIR = Pin 4.
CytronMD motor1(PWM_DIR, 6, 5); // pin 5 on duino is enable 6 is direction 
CytronMD motor2(PWM_DIR, 7, 8); 
CytronMD motor3(PWM_DIR, 9, 10); 

void initialize() {
  currentSpeed = 255;
  motor.setSpeed(currentSpeed);
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(currentSpeed);
  motor3.setSpeed(currentSpeed);
}

void changeSpeed(int speed) {
  motor.setSpeed(speed);
  motor1.setSpeed(speed);
  motor2.setSpeed(speed);
  motor3.setSpeed(speed);
  currentSpeed = speed;
}

void changeDirection() {
  currentSpeed *= -1;
  motor.setSpeed(currentSpeed);
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(currentSpeed);
  motor3.setSpeed(currentSpeed);
  
}

void stop() {
  currentSpeed = 0;
  motor.setSpeed(currentSpeed);
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(currentSpeed);
  motor3.setSpeed(currentSpeed);
}

void turnLeft() {
  motor.setSpeed(-currentSpeed);
  motor1.setSpeed(-currentSpeed);
  motor2.setSpeed(currentSpeed);
  motor3.setSpeed(currentSpeed);
}

void turnRight() {
  motor.setSpeed(currentSpeed);
  motor1.setSpeed(currentSpeed);
  motor2.setSpeed(-currentSpeed);
  motor3.setSpeed(-currentSpeed);
}

// The setup routine runs once when you press reset.
void setup() {
  
}


// The loop routine runs over and over again forever.
void loop() {
  initialize();
  delay(1000);

}
