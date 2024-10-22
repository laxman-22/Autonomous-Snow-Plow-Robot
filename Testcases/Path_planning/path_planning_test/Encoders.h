#ifndef ENCODERS_h
#define ENCODERS_h

#include "Arduino.h"

class Encoders { 
  private:
    bool measuring;
    int encoder_pins[2];
    int encoder_counts[2];

  public: 
    Encoders();
    void start_measure(); //attaches interrupts and resets count
    void end_measure(); //detaches interrupts
    void encoder1_count();
    void encoder2_count();
    void reset_counts();
    int get_encoder1_count();
    int get_encoder2_count();
    int get_average_encoder_count();
    bool is_measuring();

    //for enabling interrupts
    static Encoders* encoders_instance;
    static void encoder1_interrupt() { 
      if (encoders_instance != NULL){ 
        Encoders::encoders_instance->encoder1_count();
      }
    }
    static void encoder2_interrupt() { 
      if (encoders_instance != NULL){ 
        Encoders::encoders_instance->encoder2_count();
      }
    }

};

#endif