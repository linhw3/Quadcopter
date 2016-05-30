#ifndef CONTROL_H
#define CONTROL_H
#include <Arduino.h>
#include "Structure.h"
#include "PID.h"
#include "Motor_module.h"

/************************
  * if angle of quadcopter exceeds stop angle, stop the  rotors.
************************/
extern int stopAngle;

/************************
  * stopping flag, true for stopping.
************************/
extern bool isStop;

/************************
  * control module setup, including command factors, guidance LED.
************************/
void controlling();

/************************
  * controlling the quadcopter, if the stopping flag set, stop the rotors, else calculating PID algorithm,
  * checking statux, and the driving the rotors
************************/
void controlSetup();
#endif
