#include "I2Cdev.h"
#include <Wire.h>
#include "MPU6050_6Axis_MotionApps20.h"
#include "Structure.h"

#ifndef _SENSOR_H_
#define _SENSOR_H_
  extern int ROLL;
  extern int PITCH;
  extern int YAW;
  
  extern Attitude Rpy;
  
  void SensorSteup();
  void SensorRead();
#endif
