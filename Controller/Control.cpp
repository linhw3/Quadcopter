#include "Control.h"

/************************
  * setup the guidance LED, that is the stopping LED.
************************/
void guidanceLEDSetup() {
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
}

/************************
  * setup controlling factors
************************/
void commandUnitSetup() {
  parameterP = 0;
  parameterI = 0;
  parameterD = 0;
  CommandRpy.attitudeArray[ROLL] = 0;
  CommandRpy.attitudeArray[PITCH] = 0;
  CommandRpy.attitudeArray[YAW] = 0;
  commandThrottle = stopThrottle;
  isStop = false;
}

/************************
  * control module setup, including command factors, guidance LED.
************************/
void controlSetup() {
  commandUnitSetup();
  guidanceLEDSetup();
}

/************************
  * checking the status of the quadcopter, if dangerous, set the stop flag isStop.
  * here we cheching the ROLL angle and PITCH angle.
************************/
void safetyChecking() {
  if (abs(Rpy.attitudeArray[ROLL]) > stopAngle || abs(Rpy.attitudeArray[PITCH]) > stopAngle) {
    isStop = true;
  }
}

/************************
  * control the guidance LED, if dangerous, light it.
************************/
void guidanceLEDWork() {
  if (!isStop) {
    digitalWrite(13, LOW);
  } else {
    digitalWrite(13, HIGH);
  }
}

/************************
  * controlling the quadcopter, if the stopping flag set, stop the rotors, else calculating PID algorithm,
  * checking statux, and the driving the rotors
************************/
void controlling() {
  if (!isStop) {
    PID();
    safetyChecking();
    motor_write();
  } else {
    motor_stop();
  }
  guidanceLEDWork();
}
