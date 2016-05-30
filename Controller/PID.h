#ifndef PID_H
#define PID_H
#include <Arduino.h>
#include "Structure.h"
/************************
  * max and min constrain of throttle.
************************/
extern int maxThrottle;
extern int minThrottle;

/************************
  * enumeration, ROLL for 0, PITCH for 1, YAW for 2.
************************/
extern int ROLL;
extern int PITCH;
extern int YAW;

/************************
  * controlling factors, CommandRpy for command's attitude; parameterP for P; parameterI for I; parameterD for D; commandThrottle
  * for command's throttle; isStop for stopping flag.
************************/
extern Attitude CommandRpy;
extern double parameterP;
extern double parameterI;
extern double parameterD;
extern int commandThrottle;
extern bool isStop;

/************************
  * status of the quadcopter, Speeds for outputs of the rotors; Rpy for actual attitude.
************************/
extern Output Speeds;
extern Attitude Rpy;

/************************
  * calculates how long a period.
************************/
void cycletime_T();

/************************
  * the PID algorithm.
************************/
void PID();
#endif
