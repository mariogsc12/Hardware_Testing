#ifndef RECEIVER_HPP
#define RECEIVER_HPP

#include <Arduino.h>

class Receiver {
private:
    uint8_t Pin_Ch1, Pin_Ch3, Pin_Ch5;
    int16_t ch1Value, ch3Value;
    uint8_t mode;

    int16_t normalizePWM(uint16_t pulseWidth);
    uint8_t detectMode(uint16_t pulseWidth);
public:
    Receiver(uint8_t ch1Pin, uint8_t ch3Pin, uint8_t ch5Pin);
    void begin();
    void update();

    int16_t getThrottle();   // CH1: avance/retroceso
    int16_t getSteering();   // CH3: izquierda/derecha
    uint8_t getMode();       // CH5: modo de operación
};

#endif


