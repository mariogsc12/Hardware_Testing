#include <HardwareSerial.h>
#include "wit_c_sdk.h"
#include <WT901C.hpp>

/*
Visit: https://wit-motion.gitbook.io/witmotion-sdk/wit-standard-protocol/sdk/arduino_sdk-quick-start

Test on ESP32. use WT901CTTL sensor

WT901CTTL     ESP32 Dev Module
    VCC <--->  5V/3.3V
    TX  <--->  RX2 (GPIO16)
    RX  <--->  TX2 (GPIO17)
    GND <--->  GND
*/


#define RXD2 16
#define TXD2 17

#define ACC_UPDATE    0x01
#define GYRO_UPDATE   0x02
#define ANGLE_UPDATE  0x04
#define MAG_UPDATE    0x08
#define READ_UPDATE   0x80


volatile char WT901C::s_cDataUpdate = 0;

WT901C imu(RXD2,TXD2,RRATE_200HZ);

int sign(int value) {
  return (value > 0) - (value < 0);
}


// ---------------------------------- //
// ---------------------------------- //
// ---------------------------------- //

void setup() {
  Serial.begin(115200);
  Serial.print("\r\n********************** wit-motion normal example  ************************\r\n");

  imu.initialize();

  imu.calibrate();
  
  imu.autoScanSensor();
}



void loop() {

  imu.readData();

  imu.saveData();

}

