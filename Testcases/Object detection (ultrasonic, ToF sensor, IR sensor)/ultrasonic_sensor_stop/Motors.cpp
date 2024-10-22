#include "Motors.h"
#include "Pins.h"

Motors::Motors()
  : M1(PWM_DIR, M1_PWM_PIN, M1_DIR_PIN), M2(PWM_DIR, M2_PWM_PIN, M2_DIR_PIN), M3(PWM_DIR, M3_PWM_PIN, M3_DIR_PIN), M4(PWM_DIR, M4_PWM_PIN, M4_DIR_PIN) {
  this->speed = 128;

  reset_flags();
}

void Motors::reset_flags() {
  this->forward_flag = false;
  this->backward_flag = false;
  this->stop_flag = false;
  this->turn_right_flag = false;
  this->turn_left_flag = false;
}

void Motors::forward() {
  //drive forward
  if (!this->forward_flag) {  //only set motor speeds if necessary
    reset_flags();
    this->forward_flag = true;

    this->M1.setSpeed(this->speed);
    this->M2.setSpeed(this->speed);
    this->M3.setSpeed(this->speed);
    this->M4.setSpeed(this->speed);
  }
}

void Motors::backward() {
  //drive backward
  if (!this->backward_flag) {  //only set motor speeds if necessary
    reset_flags();
    this->backward_flag = true;

    this->M1.setSpeed(-this->speed);
    this->M2.setSpeed(-this->speed);
    this->M3.setSpeed(-this->speed);
    this->M4.setSpeed(-this->speed);
  }
}

void Motors::stop() {
  //stop all robot movement
  if (!this->stop_flag) {  //only set motor speeds if necessary
    reset_flags();
    this->stop_flag = true;

    this->M1.setSpeed(0);
    this->M2.setSpeed(0);
    this->M3.setSpeed(0);
    this->M4.setSpeed(0);
  }
}

void Motors::turn_right() {
  //turn the robot right on the spot
  if (!this->turn_right_flag) {  //only set motor speeds if necessary
    reset_flags();
    this->turn_right_flag = true;

    this->M1.setSpeed(this->speed);
    this->M2.setSpeed(this->speed);
    this->M3.setSpeed(-this->speed);
    this->M4.setSpeed(-this->speed);
  }
}

void Motors::turn_left() {
  //turn the robot right on the spot
  if (!this->turn_left_flag) {  //only set motor speeds if necessary
    reset_flags();
    this->turn_left_flag = true;

    this->M1.setSpeed(-speed);
    this->M2.setSpeed(-speed);
    this->M3.setSpeed(speed);
    this->M4.setSpeed(speed);
  }
}

void Motors::set_speed(int speed) {
  //sets speed of motors for next update
  this->speed = speed;
}