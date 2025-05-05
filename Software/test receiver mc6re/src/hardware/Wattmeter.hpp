//Inspired by https://wiki.dfrobot.com/Gravity:%20I2C%20Digital%20Wattmeter%20SKU:%20SEN0291

#ifndef WATTMETER_HPP
#define WATTMETER_HPP

#include <Arduino.h>
#include <Wire.h>
#include "DFRobot_INA219.h"

class Wattmeter 
{
private:
    TwoWire _wire;
    uint8_t Pin_Sda, Pin_Scl;
    uint8_t _i2cAddr;
    DFRobot_INA219_IIC* _sen0291;
public:
    Wattmeter(uint8_t sdaPin, uint8_t sclPin, uint8_t i2cAddr = INA219_I2C_ADDRESS4);
    bool begin();
    float getVoltage(); // V
    float getCurrent(); // mA
    float getPower(); // mW
    float getShuntVoltage(); // mV

};
#endif