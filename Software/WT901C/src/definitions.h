#define ACC_UPDATE    0x01
#define GYRO_UPDATE   0x02
#define ANGLE_UPDATE  0x04
#define MAG_UPDATE    0x08
#define READ_UPDATE   0x80


#define PIN_RX2 16
#define PIN_TX2 17


#define LIVESERIAL_MILLIS(id, value) { unsigned long ms = millis(); Serial.print(id);  Serial.print(':');  Serial.print(value);  Serial.print('@');  Serial.println(ms); }
