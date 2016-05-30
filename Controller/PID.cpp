#include "PID.h"

double error[3];  // error between command's attitude and the actual attitude, for ROLL, PITCH, YAW.
double errorSum[3] = {0, 0, 0};  // integeral of the error, for ROLL, PITCH, YAW.
double previousError[3] = {0, 0, 0};  // variables for calaulating errorSum.
double errorDerivative[3];  // differential of the error, for ROLL, PITCH, YAW.
double motor_error[2]; // combination of error, integeral of the error, differential of the error.
uint16_t currentTime, previousTime;  // variables for calculating cycleTime.
double cycleTime;  // the time of period.

/************************
  * calculates how long a period.
************************/
void cycletime_T() {
        previousTime = currentTime;
	currentTime = micros();
	cycleTime = (currentTime - previousTime) / 1000;
	if(cycleTime < 1) cycleTime = 1;
}

/************************
  * the PID algorithm.
************************/
void PID() {
  cycletime_T();
  /************************
  * ROLL error calculate.
  ************************/
  // P_error
  error[ROLL] = CommandRpy.attitudeArray[ROLL] - Rpy.attitudeArray[ROLL];
  // I_error
  if (abs(error[ROLL]) < 1.5) {
    errorSum[ROLL] += error[ROLL];
  }
  // D_error
  errorDerivative[ROLL] = error[ROLL] - previousError[ROLL];
  previousError[ROLL] = error[ROLL];
  motor_error[ROLL] = error[ROLL] * parameterP + errorSum[ROLL] * parameterI * cycleTime + errorDerivative[ROLL] * parameterD / cycleTime;
  
  /************************
  * PITCH error calculate.
  ************************/
  // P_error
  error[PITCH] = CommandRpy.attitudeArray[PITCH] - Rpy.attitudeArray[PITCH];
  // I_error
  if (abs(error[PITCH]) < 1.5) {
    errorSum[PITCH] += error[PITCH];
  }
  // D_error
  errorDerivative[PITCH] = error[PITCH] - previousError[PITCH];
  previousError[PITCH] = error[PITCH];
  motor_error[PITCH] = error[PITCH] * parameterP + errorSum[PITCH] * parameterI * cycleTime + errorDerivative[PITCH] * parameterD / cycleTime;
  
  // speeds asignment
  Speeds.speedArray[0] = commandThrottle -  motor_error[ROLL];
  Speeds.speedArray[2] = commandThrottle - motor_error[PITCH];
  Speeds.speedArray[1] = commandThrottle + motor_error[ROLL];
  Speeds.speedArray[3] = commandThrottle + motor_error[PITCH];
  
  // speeds constrain
  Speeds.speedArray[0] = constrain(Speeds.speedArray[0], minThrottle, maxThrottle);
  Speeds.speedArray[1] = constrain(Speeds.speedArray[1], minThrottle, maxThrottle);
  Speeds.speedArray[2] = constrain(Speeds.speedArray[2], minThrottle, maxThrottle);
  Speeds.speedArray[3] = constrain(Speeds.speedArray[3], minThrottle, maxThrottle);
}
