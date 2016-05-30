#include "Motor_module.h"
#include <Arduino.h>

Servo motor0;
Servo motor1;
Servo motor2;
Servo motor3;

void motor_setup() {
  motor0.attach(3);
  motor1.attach(11);
  motor2.attach(6);
  motor3.attach(10);
  motor0.writeMicroseconds(1000);
  motor1.writeMicroseconds(1000);
  motor2.writeMicroseconds(1000);
  motor3.writeMicroseconds(1000);
  delay(2000);
}

void motor_write() {
  motor0.writeMicroseconds(Speeds.speedArray[0]);
  motor1.writeMicroseconds(Speeds.speedArray[1]);
  motor2.writeMicroseconds(Speeds.speedArray[2]);
  motor3.writeMicroseconds(Speeds.speedArray[3]);
}

void motor_stop() {
  motor0.writeMicroseconds(stopThrottle);
  motor1.writeMicroseconds(stopThrottle);
  motor2.writeMicroseconds(stopThrottle);
  motor3.writeMicroseconds(stopThrottle);
}

