#include <math.h>
#define BLACK_ANALOG_READ_THRESHOLD 900

#define MIN_DISTANCE_TO_OBJECT 30 //in cm
#define NUM_CONSECUTIVE_DETECTIONS_ULTRASONIC 50
#define NUM_CONSECUTIVE_DETECTIONS_LINE_SENSOR 5
#define NUM_CONSECUTIVE_DETECTIONS_IR_SENSOR 1

#define WHEEL_DIAMETER 6.57 //in cm
#define DISTANCE_BETWEEN_WHEELS 12.1 //in cm
#define WIDTH 22.6 //in cm
#define ENCODER_TEETH 10
#define EXPERIMENTAL_PULSE_OFFSET -1

#define X_CONSTANT 1.48
#define ANGLE_RADS 90*PI/180

#define NUMBER_OF_FULL_REVOLUTIONS_FOR_90 ANGLE_RADS * X_CONSTANT * DISTANCE_BETWEEN_WHEELS / (PI * WHEEL_DIAMETER)
#define NUMBER_OF_ENCODER_PULSES_FOR_90 ENCODER_TEETH * NUMBER_OF_FULL_REVOLUTIONS_FOR_90 + EXPERIMENTAL_PULSE_OFFSET

#define NUMBER_OF_FULL_REVOLUTIONS_FOR_WIDTH WIDTH/(WHEEL_DIAMETER * PI)
#define NUMBER_OF_ENCODER_PULSES_FOR_WIDTH ENCODER_TEETH * NUMBER_OF_FULL_REVOLUTIONS_FOR_WIDTH