# SYSC4805 Group Project
Group Number:  7
Lab (L2 or L3): L3
Students Names:  
1-  Aryan Laxman Sirohi: 101199497
2-  Miller Timlin: 101115779
3-  Basel Syed: 101173816
-------------------------  
## What is the project?

As part of the SYSC 4805 course, we will be building an autonomous snow plowing robot. The bot must be capable of plowing snow in a bounded area, stay within those bounds, and avoid any obstacles it might find along the way.

## Our hardware choices:
For this project we will be using the following hardware:
- Arduino Due Microcontroller
- 4x motors
- 2x Wheel Encoders
- 2x Line follower Sensor
- 1x IR Distance Sensor

With this combination of sensors, we look to achieve a robot can quickly, efficiently, and safely plow snow.

## Repository structure
- \Final Code: This directory contains the final robot code and the final code for reading from the arduino's flash memory
  - \main: The final robot code
    - Encoders.cpp: class representing/controlling the interactions and interrupts from the IRSensor
    - Encoders.h: header file for class
    - IRSensor.cpp: class representing/controlling the interactions and interrupts from the IRSensor
    - IRSensor.h: header file for class
    - LineFollwers.cpp: class representing/controlling the interactions and interrupts from the LineFollwers
    - LineFollwers.h: header file for class
    - Motors.cpp: class representing/controlling the interactions with the motors
    - Motors.h: header file for class
    - Pins.h: File listing all macro definitions for pins used on the robot
    - Robot_Measurements.h: file listing all macro definitions for physical/debouncing properties of the robot relevant to the project implementation
    - main.ino: Arduino code implementing the path planning algorithm using the provided sensors 
  - \read_flash: the final code for reading from the arduino's flash memory
- \Testcases: This directory contains testcases for the various sensors and system requirements
  - \90 turn(encoder): The code for testing a 90 degree turn using the wheel encoders to measure
  - \Boundary detect and turn (line sensor and encoder): The code for testing a 90 degree turn once the line sensor detects a line
  - \Boundary detection (line sensor): The code for testing the ability of the line sensor to detect the boundary line effectively
  - \Object detection (ultrasonic, ToF sensor, IR sensor): The code for testing object dection using the listed sensors.  Note that only the IR sensor ended up being used in the final demo
  - \Path_planning: The initial code for the path planning algorithm
  - \Persistent storage write and read: The code for testing writing and reading to the Due's flash storage
  - \SpeedMod: The code for testing speed modulation of the motores
  - \Watchdog Timer: The code for testing the implementation of the watchdog timer
