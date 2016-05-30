#include "Bluetooth.h"

enum SignalType {P, I, D, R, PIT, Y, T};
uint16_t previousTimer = 0, currentTimer;

bool parseDouble(double &rt) {
  char rc = '0';
  int pos = 0;
  bool rev = false;
  while (true) {
      rc = Serial.read();
      //Serial.print(rc);
      //if (rc == -1) return false;
      if (rc == ';') break;
      if (rc == '/') {
        rt = 0.0;
        return false;
      }
      if (rc == '.') {
        rev = true;
        pos = 0;
      }
      else if (rc <= '9' && rc >= '0'){
        rt *= 10;
        rt += (rc-'0');
        if (rev) pos++;
      }
  }
  rt/=pow(10, pos);
  return true;
}

void bluetoothUpdate() {
  Info info;
  info.data[P] = parameterP;
  info.data[I] = parameterI;
  info.data[D] = parameterD;
  info.data[R] = CommandRpy.attitudeArray[ROLL];
  info.data[PIT] = CommandRpy.attitudeArray[PITCH];
  info.data[Y] = CommandRpy.attitudeArray[YAW];
  info.data[T] = commandThrottle;
  info.isStop =isStop;

  if (Arduino_recieve(info)) {
    parameterP = info.data[P];
    parameterI = info.data[I];
    parameterD = info.data[D];
    CommandRpy.attitudeArray[ROLL] = info.data[R];
    CommandRpy.attitudeArray[PITCH] = info.data[PIT];
    CommandRpy.attitudeArray[YAW] = info.data[Y];
    commandThrottle = info.data[T];
    isStop = info.isStop;
  }
}

bool Arduino_recieve(Info &info) {
  char rc = Serial.read();
  if (rc == -1) return false;
  double rt = 0.0;
  if (!parseDouble(rt)) return false;
  
  switch (rc){
    case 'P': info.data[P] = rt; break;
    case 'I':info.data[I] = rt; break;
    case 'D':info.data[D] = rt; break;
    case 'R':info.data[R] = rt; break;
    case 'Q':info.data[PIT] = rt; break;
    case 'Y':info.data[Y] = rt; break;
    case 'T':info.data[T] = rt; break;
    case 'S':info.isStop = true; break;
    default: return false;
  }
  return true;
}

bool Arduino_send() {
  Serial.print("PID: ");
  Serial.print(parameterP);
  Serial.print(" ");
  Serial.print(parameterI);
  Serial.print(" ");
  Serial.println(parameterD);
  
  Serial.print("commandThrottle: ");
  Serial.println(commandThrottle);
  
  Serial.print("Attitude: ");
  Serial.print(Rpy.attitudeArray[ROLL]);
  Serial.print(" ");
  Serial.print(Rpy.attitudeArray[PITCH]);
  Serial.print(" ");
  Serial.println(Rpy.attitudeArray[YAW]);
  
  Serial.print("Speeds: ");
  Serial.print(Speeds.speedArray[0]);
  Serial.print(" ");
  Serial.print(Speeds.speedArray[1]);
  Serial.print(" ");
  Serial.print(Speeds.speedArray[2]);
  Serial.print(" ");
  Serial.println(Speeds.speedArray[3]);
  
  Serial.print("Command Attitude: ");
  Serial.print(CommandRpy.attitudeArray[ROLL]);
  Serial.print(" ");
  Serial.print(CommandRpy.attitudeArray[PITCH]);
  Serial.print(" ");
  Serial.println(CommandRpy.attitudeArray[YAW]);
  
  Serial.print("StopFlag: ");
  Serial.println(isStop);
  Serial.println(";");
  return true;
}


bool TimerCal() {
  currentTimer = millis();
  if (currentTimer - previousTimer > 200) {
    return true;
  } else {
    return false;
  }
}

void bluetoothSend() {
  if (TimerCal()) {
    Arduino_send();
    previousTimer = millis();
  }
}

void bluetoothSetup() {
  previousTimer = millis();
}

