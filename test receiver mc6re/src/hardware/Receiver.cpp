#include "Receiver.hpp"

Receiver::Receiver(uint8_t ch1Pin, uint8_t ch3Pin, uint8_t ch5Pin)
    : Pin_Ch1(ch1Pin), Pin_Ch3(ch3Pin), Pin_Ch5(ch5Pin),
      ch1Value(0), ch3Value(0), mode(0) {}

void Receiver::begin() {
    pinMode(Pin_Ch1, INPUT);
    pinMode(Pin_Ch3, INPUT);
    pinMode(Pin_Ch5, INPUT);
}

void Receiver::update() {
    uint16_t pulse1 = pulseIn(Pin_Ch1, HIGH, 25000);
    uint16_t pulse3 = pulseIn(Pin_Ch3, HIGH, 25000);
    uint16_t pulse5 = pulseIn(Pin_Ch5, HIGH, 25000);

    ch1Value = normalizePWM(pulse1);
    ch3Value = normalizePWM(pulse3);
    mode = detectMode(pulse5);
}

int16_t Receiver::getThrottle() {
    return ch1Value;
}

int16_t Receiver::getSteering() {
    return ch3Value;
}

uint8_t Receiver::getMode() {
    return mode;
}

int16_t Receiver::normalizePWM(uint16_t pulseWidth) {
    if (pulseWidth < 1000 || pulseWidth > 2000) return 0;
    return map(pulseWidth, 1000, 2000, -1000, 1000);
}

uint8_t Receiver::detectMode(uint16_t pulseWidth) {
    if (pulseWidth < 1200) return 0;
    if (pulseWidth < 1700) return 1;
    return 2;
}
