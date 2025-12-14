#include "IMU.hpp"
#include <Wire.h>
#include <Arduino.h>
#include <math.h>

IMU::IMU() : gx_offset(0), gy_offset(0), gz_offset(0) {}

bool IMU::begin() {
    Wire.begin();
    mpu.initialize();
    return mpu.testConnection();
}

void IMU::calibrateGyro(int samples) {
    long sum_gx = 0, sum_gy = 0, sum_gz = 0;

    for (int i = 0; i < samples; i++) {
        mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
        sum_gx += gx;
        sum_gy += gy;
        sum_gz += gz;
        delay(2);
    }

    gx_offset = sum_gx / (float)samples;
    gy_offset = sum_gy / (float)samples;
    gz_offset = sum_gz / (float)samples;
}

void IMU::readRaw() {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    ax_g = ax / 16384.0;
    ay_g = ay / 16384.0;
    az_g = az / 16384.0;

    gx_dps = (gx - gx_offset) / 131.0;
    gy_dps = (gy - gy_offset) / 131.0;
    gz_dps = (gz - gz_offset) / 131.0;
}

void IMU::computeAccelerometerAngles() {
    pitch_acc = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;
    roll_acc  = atan2(ay_g, sqrt(ax_g * ax_g + az_g * az_g)) * 180.0 / PI;
}

float IMU::getAxG() const { return ax_g; }
float IMU::getAyG() const { return ay_g; }
float IMU::getAzG() const { return az_g; }

float IMU::getGxDPS() const { return gx_dps; }
float IMU::getGyDPS() const { return gy_dps; }
float IMU::getGzDPS() const { return gz_dps; }

float IMU::getPitchAcc() const { return pitch_acc; }
float IMU::getRollAcc() const { return roll_acc; }
