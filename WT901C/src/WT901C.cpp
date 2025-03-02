#include <WT901C.hpp>
#include <definitions.h>

WT901C::WT901C(const int Rx, const int Tx):
        Pin_RX(Rx),
        Pin_TX(Tx)
{
  s_cDataUpdate = 0;
}

void WT901C::initialize()
{
    Serial2.begin(115200, SERIAL_8N1, Pin_RX, Pin_TX);
    Serial.print("Serial2 ready\r\n");
  
    WitInit(WIT_PROTOCOL_NORMAL, 0x50);
    WitSerialWriteRegister(sensorUartSend);
    WitRegisterCallBack(sensorDataUpdate);
    WitDelayMsRegister(delayms);
}

void WT901C::autoScanSensor(void)
{
    int i, iRetry; 
    const uint32_t c_uiBaud[8] = {0, 4800, 9600, 19200, 38400, 57600, 115200, 230400};
    
    for (i = 0; i < sizeof(c_uiBaud) / sizeof(c_uiBaud[0]); i++) {
      Serial2.begin(c_uiBaud[i], SERIAL_8N1, Pin_RX, Pin_TX); 
      Serial2.flush(); 
      iRetry = 2; 
      s_cDataUpdate = 0; 
      do {
        WitReadReg(AX, 3); 
        delay(200); 
        while (Serial2.available()) {
          WitSerialDataIn(Serial2.read()); 
        }
        if (s_cDataUpdate != 0) {
          Serial.print(c_uiBaud[i]); 
          Serial.print("Baud sensor detected\r\n\r\n"); 
          return; 
        }
        iRetry--; 
      } while (iRetry); 
    } 
    Serial.print("Cannot find sensor\r\n"); 
    Serial.print("Please check your connections\r\n"); 
}

void WT901C::sensorUartSend(uint8_t *p_data, uint32_t uiSize)
{
    Serial2.write(p_data, uiSize); 
    Serial2.flush(); 
}

void WT901C::sensorDataUpdate(uint32_t uiReg, uint32_t uiRegNum)
{
    int i; 
    for (i = 0; i < uiRegNum; i++) {
      switch (uiReg) {
        case AZ: 
          s_cDataUpdate |= ACC_UPDATE; 
          break; 
        case GZ: 
          s_cDataUpdate |= GYRO_UPDATE; 
          break; 
        case HZ: 
          s_cDataUpdate |= MAG_UPDATE; 
          break; 
        case Yaw: 
          s_cDataUpdate |= ANGLE_UPDATE; 
          break; 
        default: 
          s_cDataUpdate |= READ_UPDATE; 
          break; 
      } 
      uiReg++; 
    } 
}

void WT901C::saveData()
{
  
  if (s_cDataUpdate) {
    acc.set(sReg[AX]/ 32768.0f * 16.0f, sReg[AX+1]/ 32768.0f * 16.0f, sReg[AX+2]/ 32768.0f * 16.0f);
    gyro.set(sReg[GX]/ 32768.0f * 2000.0f, sReg[GX + 1]/ 32768.0f * 2000.0f, sReg[GX + 2]/ 32768.0f * 2000.0f);
    angle.set(sReg[Roll]/ 32768.0f * 180.0f, sReg[Roll + 1]/ 32768.0f * 180.0f, sReg[Roll + 2]/ 32768.0f * 180.0f);
    mag.set(sReg[HX],sReg[HY],sReg[HZ]);

    if (s_cDataUpdate & ACC_UPDATE) {
      LIVESERIAL_MILLIS("accX",acc.getX());
      LIVESERIAL_MILLIS("accY",acc.getY());
      LIVESERIAL_MILLIS("accZ",acc.getZ());
      s_cDataUpdate &= ~ACC_UPDATE;
    }

    if (s_cDataUpdate & GYRO_UPDATE) {
      LIVESERIAL_MILLIS("gyroX",gyro.getX());
      LIVESERIAL_MILLIS("gyroY",gyro.getY());
      LIVESERIAL_MILLIS("gyroZ",gyro.getZ());
      s_cDataUpdate &= ~GYRO_UPDATE;
    }

    if (s_cDataUpdate & ANGLE_UPDATE) {
      LIVESERIAL_MILLIS("angleX",angle.getX());
      LIVESERIAL_MILLIS("angleY",angle.getY());
      LIVESERIAL_MILLIS("angleZ",angle.getZ());
      s_cDataUpdate &= ~ANGLE_UPDATE;
    }

    if (s_cDataUpdate & MAG_UPDATE) {
      LIVESERIAL_MILLIS("magX",mag.getX());
      LIVESERIAL_MILLIS("magY",mag.getY());
      LIVESERIAL_MILLIS("magZ",mag.getZ());
      s_cDataUpdate &= ~MAG_UPDATE;
    }
  }
}

void WT901C::delayms(uint16_t ucMs)
{
    delay(ucMs); 
}

void WT901C::calibrate()
{
  if (WitStartAccCali() == WIT_HAL_OK)Serial.print("Accelerometer calibration completed successfully\r\n");
  else ("ERROR - Accelerometer Calibration\r\n");


  if (WitStartMagCali() == WIT_HAL_OK) 
  {
    Serial.print("Mag calibration started. Move sensor in figure-eight motion.\r\n");
    Serial.print("Please move the sensor in the three axes.\r\n");
    delay(10000); 

    if (WitStopMagCali() == WIT_HAL_OK)Serial.print("Mag calibration completed successfully\r\n");
    else Serial.print("Mag calibration failed\r\n");

  } 
  else Serial.print("Mag calibration Incorrect\r\n");


  if (WitSetOutputRate(RRATE_100HZ) == WIT_HAL_OK)Serial.print("Set Output Rate equal to 100 Hz completed Successfully\r\n");
  else Serial.print("ERROR - Output Rate configuration\r\n");
}

void WT901C::readData()
{
  while (Serial2.available()) {
    WitSerialDataIn(Serial2.read());
  }
}