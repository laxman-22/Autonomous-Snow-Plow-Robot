// main loop to run the program
#include "Robot_Measurements.h"
#include "Encoders.h"
#include "Motors.h"
#include "LineFollowers.h"
#include "IRSensor.h"
#include <DueFlashStorage.h>
#include <watchdog.h>

// Defines the time for the watchdog in ms
int watchdogTime = 2000;

//flags
bool store_logs = false;

bool full_stop = false;
bool end = false;
bool forward = true;
bool backward = true;
bool mid_turn = false;
bool turning = false;
bool turn_right = false;

//initialize sensors and motor classes
LineFollowers line_follower_right = LineFollowers(LINE_FOLLOWER_1_DIGITAL_PIN, LINE_FOLLOWER_1_ANALOG_PIN);
LineFollowers line_follower_left = LineFollowers(LINE_FOLLOWER_2_DIGITAL_PIN, LINE_FOLLOWER_2_ANALOG_PIN);
Encoders encoders = Encoders();
IRSensor ir_sensor = IRSensor();
Motors motors = Motors();

//persistent storage for when disconnected from serial
DueFlashStorage flash;

void print(String message, int message_num) {
  if (store_logs) {
    static uint32_t log_address = 0;
    flash.write(log_address, message_num);  //store message num at address
    log_address++;                          //increment address
  } else {
    Serial.println(message);
  }
}

void watchdogSetup(void) {
  // do what you want here
}

void setup() {
  if (!Serial) {  //if serial is not connected
    store_logs = true;
  } else Serial.begin(9600);
  print("\n\n", 0);

  motors.set_speed(200);

  //Initalizing line follower sensors
  print("Initalizing Line Follower right Sensor", 1);
  line_follower_right.init();

  print("Initalizing Line Follower left Sensor", 2);
  line_follower_left.init();

  //Initalizing encoder sensor
  print("Initalizing Encoder Sensor", 3);
  encoders.init();

  //Initialize IR sensor
  print("Initalize IR Sensor", 4);
  ir_sensor.init();

  print("Sensor Setup complete. delay momentarily", 5);
  delay(5000);  //delay 5 seconds to give user time to set up

  //enable watchdog timer
  print("Enable Watchdog Timer", 6);
  watchdogEnable(watchdogTime);

  print("Run", 7);
}

void loop() {
  watchdogReset();

  if (!full_stop) {
    if (forward) {
      if (line_follower_right.detected() || line_follower_left.detected()) {  //check if boundary line has been reached
        motors.stop();
        backward = true;
        forward = false;

        if (end) {  //if this was the last row
          //full_stop = true; //fully stop robot
        }

        encoders.reset_counts();  //must reset encoder counts before turning
        print("Boundary detected.  Stopping forward and starting backward", 8);

      } else if (ir_sensor.detected()) {  //check if obstacle has been detected in front
        motors.stop();
        forward = false;
        backward = true;
        encoders.reset_counts();  //must reset encoder counts before turning
        print("Obstacle Detected", 9);

      } else {  //if no obstacle or boundary detected, keep moving forward
        motors.forward();
      }

    } else if (backward) {
      if (encoders.get_encoder1_count() >= NUMBER_OF_ENCODER_PULSES_FOR_WIDTH / 2) {  //check if width/2 of robot has been driven
        motors.stop();
        turning = true;
        backward = false;

        encoders.reset_counts();  //must reset encoder counts before turning
        print("backwards completed. start turning", 10);

      } else {
        motors.backward();
      }
    } else if (turning) {
      if (encoders.get_encoder1_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {  //check if 90 degree turn has completed
        motors.stop();
        turning = false;

        if (!mid_turn) {
          mid_turn = true;
          print("first 90 degree turn completed. Starting mid turn", 11);
          encoders.reset_counts();  //must reset encoder counts before turning

        } else if (mid_turn) {
          mid_turn = false;
          forward = true;

          //toggle turn_right so that it turns the opposite direction next time
          if (turn_right) turn_right = false;
          else turn_right = true;

          print("second 90 degree turn completed. returning to forward movement", 12);
        }
      } else {  //if turn not complete, keep turning
        if (turn_right) {
          motors.turn_right();
        } else {
          motors.turn_left();
        }
      }
    } else if (mid_turn && !turning) {                                            //flags can be enabled at the same time in the event of the second turn, but we only want to be in this state when mid_turn is enabled
      if (encoders.get_encoder1_count() >= NUMBER_OF_ENCODER_PULSES_FOR_WIDTH) {  //check if width of robot has been driven
        motors.stop();
        turning = true;
        //NOTE: do not set mid_turn false.  it is used to indicate the second turn

        encoders.reset_counts();  //must reset encoder counts before turning
        print("mid turn completed. start turning", 13);

      } else if (ir_sensor.detected()) {  //check if obstacle has been detected in front
        motors.stop();
        backward = true;
        //NOTE: do not set mid_turn false.  it is used to indicate the second turn

        encoders.reset_counts();  //must reset encoder counts before turning
        print("Obstacle Detected", 14);

      } else if (line_follower_right.detected() || line_follower_left.detected()) {  //check if boundary line has been reached
        motors.stop();
        backward = true;
        end = true;  //indicate this is the last row

        encoders.reset_counts();  //must reset encoder counts before turning
        print("Boundary detected.  Stopping mid turn and starting backward", 15);
      } else {
        motors.forward();
      }
    }
  }
}