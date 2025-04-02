#include <MPU9250_WE.h>
#include <Wire.h>
#include <Imu.hpp>


#define MPU9250_ADDR 0x68

MPU9250_WE mpu = MPU9250_WE(MPU9250_ADDR);

Imu imu;

void setup() {
  Serial.begin(115200);
  
  imu.initialize();

  delay(1000);
}

void loop() {
  imu.update();

  imu.printSensorData();

  delay(20);
}