#ifndef BLUETOOTH_H
#define BLUETOOTH_H
#include <Arduino.h>
#include "Structure.h"

extern int sendingInterval;
extern int baudrate;

extern int ROLL;
extern int PITCH;
extern int YAW;

extern double parameterP;
extern double parameterI;
extern double parameterD;
extern Attitude CommandRpy;
extern int commandThrottle;
extern bool isStop;

extern Attitude Rpy;
extern Output Speeds;

bool parseDouble(double &rt);
bool Arduino_recieve(Info &info);
void bluetoothUpdate();
bool Arduino_send();
void bluetoothSend();
void bluetoothSetup();
#endif
