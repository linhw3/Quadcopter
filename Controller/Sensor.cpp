#include"Sensor.h"
#include"Structure.h"

bool dmpReady = false;
uint8_t mpuIntStatus;
uint8_t devStatus;
uint16_t packetSize;
uint16_t fifoCount;
uint8_t fifoBuffer[64];

MPU6050 accelgyro;
Quaternion q;
VectorFloat gravity;
float ypr[3];
const float rad_to_deg = 57.29577951307855;


volatile bool mpuInterrupt = false;
void dmpDataReady() {
  mpuInterrupt = true;
}
void SensorSteup() {
#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
  Wire.begin();
  TWBR = 24;
#elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
  Fastwire::setup(400, true);
#endif
  accelgyro.initialize();
  accelgyro.dmpInitialize();

  if (devStatus == 0) {
    accelgyro.setDMPEnabled(true);
    attachInterrupt(0, dmpDataReady, RISING);
    mpuIntStatus = accelgyro.getIntStatus();
    dmpReady = true;
    packetSize = accelgyro.dmpGetFIFOPacketSize();
  } else {
    Serial.print(F("DMP Initialization failed (code "));
    Serial.print(devStatus);
    Serial.println(F(")"));
  }
}
void SensorRead() {
  if (!dmpReady) return;
  mpuInterrupt = false;
  mpuIntStatus = accelgyro.getIntStatus();
  fifoCount = accelgyro.getFIFOCount();
  if ((mpuIntStatus & 0x10) || fifoCount == 1024) {
    accelgyro.resetFIFO();
  } else if (mpuIntStatus & 0x02) {
    while (fifoCount < packetSize) fifoCount = accelgyro.getFIFOCount();
    accelgyro.getFIFOBytes(fifoBuffer, packetSize);
    fifoCount -= packetSize;
    accelgyro.dmpGetQuaternion(&q, fifoBuffer);
    accelgyro.dmpGetGravity(&gravity, &q);
    accelgyro.dmpGetYawPitchRoll(ypr, &q, &gravity);
    accelgyro.setFullScaleGyroRange(MPU6050_GYRO_FS_2000);
  }
  Rpy.attitudeArray[ROLL] = ypr[2] * rad_to_deg;
  Rpy.attitudeArray[PITCH] = ypr[1] * rad_to_deg;
  Rpy.attitudeArray[YAW] = ypr[0] * rad_to_deg;
}
