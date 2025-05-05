#include "Wattmeter.hpp"

Wattmeter::Wattmeter(uint8_t sdaPin, uint8_t sclPin, uint8_t i2cAddr)
  : _wire(1), Pin_Sda(sdaPin), Pin_Scl(sclPin), _i2cAddr(i2cAddr) {
    _sen0291 = new DFRobot_INA219_IIC(&_wire, _i2cAddr);
}

bool Wattmeter::begin() {
    _wire.begin(Pin_Sda, Pin_Scl);
    if (!_sen0291->begin()) {
        return false;
    }
    // Puedes calibrar aquí si lo deseas
    _sen0291->linearCalibrate(1000, 1000);
    return true;
}

float Wattmeter::getVoltage() {
    return _sen0291->getBusVoltage_V();
}

float Wattmeter::getCurrent() {
    return _sen0291->getCurrent_mA();
}

float Wattmeter::getPower() {
    return _sen0291->getPower_mW();
}

float Wattmeter::getShuntVoltage() {
    return _sen0291->getShuntVoltage_mV();
}
