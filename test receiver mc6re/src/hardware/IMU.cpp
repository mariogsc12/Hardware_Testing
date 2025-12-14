#include "Arduino.h"
#include "hardware\Imu.hpp"
#include <math.h>

IMU::IMU(HardwareSerial& serial, int rx, int tx, unsigned long baud)
    : imuSerial(serial), Pin_Rx(rx), Pin_Tx(tx), baudRate(baud) {}

void IMU::begin() {
    imuSerial.begin(baudRate, SERIAL_8N1, Pin_Rx, Pin_Tx);
    delay(300);
    Serial.println("IMU inicializada.");
}

void IMU::update() {
    while (imuSerial.available()) {
        uint8_t byte = imuSerial.read();

        if (!packetStarted) {
            if (byte == 0x55) { //0x55 indica inicio paquete
                buffer[0] = byte;
                bufferIndex = 1;
                packetStarted = true;
            }
        } else {
            buffer[bufferIndex++] = byte;
            if (bufferIndex == 11) { //paquete completo se reinicia estado
                packetStarted = false;
                bufferIndex = 0;
                parsePacket();
            }
        }
    }
}

void IMU::parsePacket() {
    if (buffer[1] == 0x53) { // Paquete de ángulos
        int16_t rollRaw  = (int16_t)(buffer[3] << 8 | buffer[2]);
        int16_t pitchRaw = (int16_t)(buffer[5] << 8 | buffer[4]);
        int16_t yawRaw   = (int16_t)(buffer[7] << 8 | buffer[6]);

        roll  = rollRaw / 32768.0f * 180.0f;
        pitch = pitchRaw / 32768.0f * 180.0f;
        yaw   = yawRaw / 32768.0f * 180.0f;

        if (yaw < 0) yaw += 360.0f;
    }
}

float IMU::getRoll() const  { return roll; }
float IMU::getPitch() const { return pitch; }
float IMU::getYaw() const   { return yaw; }