
#ifndef ENCODERS_h
#define ENCODERS_h

#include "Arduino.h"

class Encoders { 
  private:
    int encoder_pins[2];
    volatile int encoder_counts[2];
    volatile bool counted[2];

  public: 
    Encoders();
    void init();
    void encoder1_count();
    void encoder2_count();
    void reset_counts();
    int get_encoder1_count();
    int get_encoder2_count();
    int get_average_encoder_count();

    //for enabling interrupts
    static Encoders* encoders_instance;
    static void encoder1_interrupt() { 
      if (Encoders::encoders_instance != NULL){ 
        Encoders::encoders_instance->encoder1_count();
      }
    }
    static void encoder2_interrupt() { 
      if (Encoders::encoders_instance != NULL){ 
        Encoders::encoders_instance->encoder2_count();
      }
    }

};

#endif 