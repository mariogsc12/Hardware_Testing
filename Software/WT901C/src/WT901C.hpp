#include <HardwareSerial.h>
#include "wit_c_sdk.h"
#include <Vector.hpp>

class WT901C
{
    private:
        Vector3D<float> acc, gyro, angle, mag;
        const int8_t Pin_RX;
        const int8_t Pin_TX;
        int32_t outputRate;
        static volatile char s_cDataUpdate;
    public:
        WT901C(const int Rx, const int Tx,int32_t outputRate);
        void initialize();
        void calibrate();
        void saveData();
        void readData();
        void cmdProcess(void);
        void autoScanSensor(void);
        static void sensorUartSend(uint8_t *p_data, uint32_t uiSize);
        static void sensorDataUpdate(uint32_t uiReg, uint32_t uiRegNum);
        static void delayms(uint16_t ucMs);
};