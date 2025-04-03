#pragma once


#include <MPU9250_WE.h>
#include <Wire.h>
#include <Vector.h>

#define MPU9250_ADDR 0x68

extern MPU9250_WE mpu;         //= MPU9250_WE(MPU9250_ADDR);

class Imu{
    private:
        Vector3D <float> accRaw;
        Vector3D <float> gyroRaw;
        Vector3D <float> gyroOffset;
        
        Vector3D <float> angle;
        Vector3D <float> angle2;
        Vector3D <float> accOrientation;

        // Other variables used to store temporal data
        float dt;
        long prev_time;
        float last_angleX, last_angleY;
        
        // Auxiliary functions
        Vector3D<float> getGyroOffset();
        void printValues(const char* label, float x, float y, float z);
        void computeAngle_ComplementaryFilter(float alpha);
        void computeAccelOrientation();
        int sign(int value);
    public:
        void initialize();
        void calibrate();
        void update();
        void print();
        void printSensorData();

};