#ifndef IMU_HPP
#define IMU_HPP

#include "Arduino.h"

class IMU
{
private:
    HardwareSerial& imuSerial; //Hardware serial permite usar los puertos UART secundarios
    const int Pin_Rx;
    const int Pin_Tx;
    unsigned long baudRate; //baudRate Sensor 

    uint8_t buffer[11];
    uint8_t bufferIndex = 0;
    bool packetStarted = false;

    float roll = 0.0f; 
    float pitch = 0.0f;
    float yaw = 0.0f;

    void parsePacket(); //Función que interpreta el paquete de datos recibido de la IMU 
    //para saber si es Acelerometro 0x51, Giroscopio 0x52, Ángulo 0x53 o Magnetómetro 0x54
    //Solo uso el 0x53 porque se supone que ya saca los angulos usando 9GDL
public:
    IMU(HardwareSerial& serial, int rxPin, int txPin, unsigned long baud = 9600);

    void begin();
    void update();

    float getRoll() const;
    float getPitch() const;
    float getYaw() const;
};
#endif