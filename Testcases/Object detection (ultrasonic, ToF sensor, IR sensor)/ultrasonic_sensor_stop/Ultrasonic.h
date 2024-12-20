#ifndef ULTRASONIC_h
#define ULTRASONIC_h

#include "Arduino.h"
#include "Robot_Measurements.h"

class Ultrasonic { 
  private: 
    int trig_pin;
    int echo_pin;
    volatile uint32_t capture_count; 
    volatile float distance;
    int consecutive_detections;
  
  public: 
    Ultrasonic(); 
    void measure(); 
    void init(); //sets up trigger signal
    int get_distance();
    bool detected();

    //for enabling interrupts
    static Ultrasonic* ultrasonic_instance; 
    static void Ultrasonic_ISR() { 
      if (Ultrasonic::ultrasonic_instance != NULL) {
        Ultrasonic::ultrasonic_instance->measure();
      }
    }
};

#endif