#ifndef MOTOR_MODULE_H
#define MOTOR_MODULE_H
#include <Servo.h>
#include "Structure.h"
extern Output Speeds;
extern int stopThrottle;
void motor_setup();
void motor_write();
void motor_stop();
#endif
