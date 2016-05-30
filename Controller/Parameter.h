#ifndef _PARAMETER_H_
#define _PARAMETER_H_
#include "Structure.h"

// definitions
int stopThrottle = 1000;
int maxThrottle = 2500;
int minThrottle = 1000;
int sendingInterval = 500;
int stopAngle = 25;

// output pins of servos
int pin0 = 3;
int pin1 = 11;
int pin2 = 6;
int pin3 = 10;

// enum of the ROLL, PITCH, YAW
int ROLL = 0;
int PITCH = 1;
int YAW = 2;

// controling variables
double parameterP = 20;
double parameterI = 0.05;
double parameterD = 0;
Attitude CommandRpy;
int commandThrottle = stopThrottle;
bool isStop = false;

// planes' information
Attitude Rpy;
Output Speeds;

#endif
