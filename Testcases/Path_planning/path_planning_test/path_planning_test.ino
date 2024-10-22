#include "Robot_Measurements.h"
#include "Encoders.h"
#include "Motors.h"
#include "Ultrasonic.h"
#include "LineFollower.h"
#include "ToF.h"
#include <DueFlashStorage.h>

//flags
bool store_logs = false;

bool full_stop = false;
bool end = false;
bool forward = true;
bool mid_turn = false;
bool turning = false;
bool turn_right = true;

bool hazard = false;
bool hazard_mid_turn = false;
bool hazard_turning = false;
bool hazard_turn_right;

//initialize sensors and motor classes
LineFollower line_follower = LineFollower();
Encoders encoders = Encoders();
Ultrasonic ultrasonic = Ultrasonic();
ToF tof_right = ToF(0x2A);
ToF tof_left = ToF(0x2A + 1);
Motors motors = Motors();

//persisten storage for when disconnected from serial
DueFlashStorage dueFlashStorage;

void setup() {

  if (!Serial) {  //if serial is not connected
    store_logs = true;
  } else Serial.begin(9600);

  //initialise necessary sensors
  ultrasonic.init();

  if (!tof_right.init()) {
    Serial.println("Failed to detect and initialize tof1 sensor!");
    while (1)
      ;
  }
  if (!tof_right.init()) {
    Serial.println("Failed to detect and initialize tof2 sensor!");
    while (1)
      ;
  }

  delay(5000);  //delay 5 seconds to give user time to set up
}

void loop() {
  if (!full_stop) {
    //check for sensor outputs and perform necessary state changes
    if (!hazard && line_follower.detected() && (forward || mid_turn)) {  //boundary line was detected while moving forward
      motors.stop();
      forward = false;
      mid_turn = false;

      if (end) full_stop = true;
      else {
        turning = true;
        encoders.start_measure();
      }
    }
    if (!hazard && turning && encoders.get_average_encoder_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {  //robot has turned 90 Degrees
      motors.stop();
      turning = false;
      if (!mid_turn) {            //if only first 90 degree turn has completed
        encoders.reset_counts();  //restart measurement from 0
        mid_turn = true;          //set flag to remember to turn extra 90 degrees later
      } else {                    //full 180 degree turn has completed
        encoders.end_measure();   //stop measurement. it is not needed for the time being
        forward = true;           //else, drive forward on new line
        //toggle turn_right flag so we turn in the opposite direction next time
        if (turn_right) turn_right = false;
        else turn_right = true;
      }
    }
    if (!hazard && mid_turn && encoders.get_average_encoder_count() >= NUMBER_OF_ENCODER_PULSES_FOR_WIDTH) {  //robot has driven the width of robot
      motors.stop();
      encoders.end_measure();  //stop measurement. it is not needed for the time being
      mid_turn = false;
      turning = true;  //start next turn
    }
    //object avoidance
    if (!hazard && ultrasonic.get_distance() <= MIN_DISTANCE_TO_OBJECT && (forward || mid_turn)) {  //if moving forward and detect hazard infront
      motors.stop();
      hazard = true;
      hazard_turning = true;
      hazard_mid_turn = false;
      hazard_turn_right = turn_right;

      if (encoders.is_measuring()) encoders.reset_counts(); //if encoders were counting, reset
      else encoders.start_measure(); //if encoders were not counting, start
    }
    if (hazard && hazard_turning && encoders.get_average_encoder_count() >= NUMBER_OF_ENCODER_PULSES_FOR_90) {  //robot has turned 90 Degrees to avoid a hazard
      motors.stop();
      encoders.end_measure(); //stop counting, it is no longer needed
      hazard_turning = false;

      if (forward && !hazard_mid_turn) hazard_mid_turn = true;  //if hazard was detected moving forward and hazard mid-turn not in progress more actions are required to avoid object
      else hazard = false;                  //if hazard was detected mid-turn, or we have have now avoided hazard by turning twice, go back to normal flow
    }
    if (hazard && hazard_mid_turn) {
      if (hazard_turn_right && tof_left.get_distance() > MIN_DISTANCE_TO_OBJECT) {  //if we have turned right to avoid hazard, check hazard is no longer on left side
        motors.stop();
        hazard_turning = true;

        //toggle hazard_turn_right flag so we turn in the opposite direction next
        if (hazard_turn_right) hazard_turn_right = false;
        else hazard_turn_right = true;

        encoders.start_measure();

      } else if (!hazard_turn_right && tof_right.get_distance() > MIN_DISTANCE_TO_OBJECT) {  //if we have turned left to avoid hazard, check hazard is no longer on right side
        motors.stop();
        hazard_turning = true;

        //toggle hazard_turn_right flag so we turn in the opposite direction next
        if (hazard_turn_right) hazard_turn_right = false;
        else hazard_turn_right = true;

        encoders.start_measure();

      } else if (line_follower.detected()) {  //boundary line was detected while moving forward to avoid obstacle and object is still present on either side
        motors.stop();
        full_stop = true; //you are trapped, stop here (could potentially back up and try and find another route, but outside of current scope)
      }

    }


    //state operations
    if (!hazard) {  //if hazard has not been detected
      if (forward || mid_turn) {
        motors.forward();

      } else if (turning) {
        if (turn_right) motors.turn_right();
        else motors.turn_left();
      }
    } else {  //if hazard has been detected
      if (hazard_mid_turn) {
        motors.forward();

      } else if (hazard_turning) {
        if (hazard_turn_right) motors.turn_right();
        else motors.turn_left();
      }
    }
  }
  if (encoders.is_measuring()) encoders.end_measure();  //once done, stop measuring encoder if it is currently measuring
}
