#include <Arduino.h>
#include <math.h>

#define UART_RX 17
#define UART_TX 16
#define BAUD_SENSOR 9600

uint8_t buffer[11];
uint8_t bufferIndex = 0;
bool packetStarted = false;

// Variables para datos
float ax = 0, ay = 0, az = 0;
float gx = 0, gy = 0, gz = 0;
float mx = 0, my = 0, mz = 0;
float roll = 0, pitch = 0, yawSensor = 0;
float yawMag = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(BAUD_SENSOR, SERIAL_8N1, UART_RX, UART_TX);
  delay(300);
  Serial.println("WT901C-TTL conected. Showing data...");
}

void loop() {
  while (Serial2.available()) {
    uint8_t byte = Serial2.read();

    if (!packetStarted) {
      if (byte == 0x55) {
        buffer[0] = byte;
        bufferIndex = 1;
        packetStarted = true;
      }
    } else {
      buffer[bufferIndex++] = byte;
      if (bufferIndex == 11) {
        packetStarted = false;
        bufferIndex = 0;

        uint8_t id = buffer[1];

        if (id == 0x51) { // Aceleración
          int16_t axRaw = (int16_t)(buffer[3] << 8 | buffer[2]);
          int16_t ayRaw = (int16_t)(buffer[5] << 8 | buffer[4]);
          int16_t azRaw = (int16_t)(buffer[7] << 8 | buffer[6]);
          ax = axRaw / 32768.0f * 16.0f;
          ay = ayRaw / 32768.0f * 16.0f;
          az = azRaw / 32768.0f * 16.0f;

        } else if (id == 0x52) { // Giroscopio
          int16_t gxRaw = (int16_t)(buffer[3] << 8 | buffer[2]);
          int16_t gyRaw = (int16_t)(buffer[5] << 8 | buffer[4]);
          int16_t gzRaw = (int16_t)(buffer[7] << 8 | buffer[6]);
          gx = gxRaw / 32768.0f * 2000.0f;
          gy = gyRaw / 32768.0f * 2000.0f;
          gz = gzRaw / 32768.0f * 2000.0f;

        } else if (id == 0x54) { // Magnetómetro
          int16_t mxRaw = (int16_t)(buffer[3] << 8 | buffer[2]);
          int16_t myRaw = (int16_t)(buffer[5] << 8 | buffer[4]);
          int16_t mzRaw = (int16_t)(buffer[7] << 8 | buffer[6]);
          mx = mxRaw * 1.0f;
          my = myRaw * 1.0f;
          mz = mzRaw * 1.0f;

          // Calcular Yaw con magnetómetro directamente
          yawMag = atan2(my, mx) * 180.0f / PI;
          if (yawMag < 0) yawMag += 360.0f;

        } else if (id == 0x53) { // Ángulos (sensor)
          int16_t rollRaw  = (int16_t)(buffer[3] << 8 | buffer[2]);
          int16_t pitchRaw = (int16_t)(buffer[5] << 8 | buffer[4]);
          int16_t yawRaw   = (int16_t)(buffer[7] << 8 | buffer[6]);

          roll = rollRaw / 32768.0f * 180.0f;
          pitch = pitchRaw / 32768.0f * 180.0f;
          yawSensor = yawRaw / 32768.0f * 180.0f;
          if (yawSensor < 0) yawSensor += 360.0f;

          // Mostrar todo solo una vez por ciclo (cuando llegan los ángulos)
          Serial.println(" Meassures:");
          Serial.printf(" Angle -> Roll: %.2f°, Pitch: %.2f°, Yaw (sensor): %.2f°\n", roll, pitch, yawSensor);
          Serial.printf(" Aceleration -> ax: %.2fg, ay: %.2fg, az: %.2fg\n", ax, ay, az);
          Serial.printf(" Gyro -> gx: %.2f°/s, gy: %.2f°/s, gz: %.2f°/s\n", gx, gy, gz);
          Serial.printf(" Magnetometer → mx: %.0f, my: %.0f, mz: %.0f\n", mx, my, mz);
          Serial.printf(" Yaw (magnetometer): %.2f°\n", yawMag);
          Serial.println("--------------------------------------------------");
        }
      }
    }
  }
}
