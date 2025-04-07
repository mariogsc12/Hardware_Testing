#ifndef IMU_HPP
#define IMU_HPP

#include "MPU6050.h"

class IMU {
public:
    IMU();

    bool begin();
    void calibrateGyro(int samples = 500);
    void readRaw();
    void computeAccelerometerAngles();

    float getAxG() const;
    float getAyG() const;
    float getAzG() const;

    float getGxDPS() const;
    float getGyDPS() const;
    float getGzDPS() const;

    float getPitchAcc() const;
    float getRollAcc() const;

private:
    MPU6050 mpu;

    int16_t ax, ay, az, gx, gy, gz;
    float gx_offset, gy_offset, gz_offset;

    float ax_g, ay_g, az_g;
    float gx_dps, gy_dps, gz_dps;

    float pitch_acc, roll_acc;
};

#endif
