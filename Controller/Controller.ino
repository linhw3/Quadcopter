#include <Wire.h>
#include <Servo.h>
#include <Arduino.h>
#include "Parameter.h"
#include "Sensor.h"
#include "Motor_module.h"
#include "Bluetooth.h"
#include "Control.h"

void setup() {
  Serial.begin(115200);
  /************************
  * setup sensor, motor, contorlling modules.
  ************************/
  SensorSteup();
  motor_setup();
  controlSetup();
}

void loop() {
  // update the information fron sensors
  SensorRead();
  // upadte the information on host computer
  bluetoothSend();
  // receive commands from host computer
  bluetoothUpdate();
  // controlling the status of quadcopter
  controlling();
}
