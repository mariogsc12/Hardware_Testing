#include <Imu.hpp>

// Conversion factors to SI
const float accScale = 4.0 * 9.81 / 32768.0;
const float gyroScale = 250.0 / 32768.0;

void Imu::initialize()
{
    Wire.begin();
    if(!mpu.init()){
        Serial.println("MPU9250 does not respond");
    }
    else{
        Serial.println("MPU9250 is connected");
    }

    Serial.println("Position you MPU9250 flat and don't move it - calibrating...");
    delay(1000);
    mpu.autoOffsets();
    Serial.println("Done!");

    mpu.enableGyrDLPF();
    mpu.setGyrDLPF(MPU9250_DLPF_6);
    mpu.setGyrRange(MPU9250_GYRO_RANGE_250);
    mpu.setAccRange(MPU9250_ACC_RANGE_2G);
    mpu.enableAccDLPF(true);
    mpu.setAccDLPF(MPU9250_DLPF_6);
    delay(1000);

    Serial.print("[INFO] - Initialize calibration");
    gyroOffset = getGyroOffset();
    Serial.print("[INFO] - Calibration finish successfully");
}

void Imu::update()
{
    accRaw = mpu.getAccRawValues();
    gyroRaw = mpu.getGyrRawValues();
    computeAccelOrientation();
    computeAngle_ComplementaryFilter(0.995);

    angle2.x = mpu.getRoll();
    angle2.y = mpu.getPitch();
}

Vector3D <float> Imu::getGyroOffset(){
    int16_t bias_x, bias_y, bias_z;
    Vector3D <float> offset;
    
    for (int i=0; i<1000; i++){
        mpu.getGyrRawValues();
        offset.x += bias_x;
        offset.y += bias_y;
        offset.z += bias_z;
        delay(1);
    }
    offset.x /= 1000;
    offset.y /= 1000;
    offset.z /= 1000;

    return offset;
}

void Imu::printValues(const char* label, float x, float y, float z) {
    Serial.print(label);
    Serial.print(x);
    Serial.print("   ");
    Serial.print(y);
    Serial.print("   ");
    Serial.println(z);
}

void Imu::computeAccelOrientation(){
    // Calculate the orientation angles
    accOrientation.x = atan2(accRaw.y, sign(accRaw.z) * sqrt(pow(accRaw.z,2) + 0.2*pow(accRaw.x,2))) * (180.0 / 3.14);
    accOrientation.y = atan2(-accRaw.x, sqrt(pow(accRaw.y,2) + pow(accRaw.z,2))) * (180.0 / 3.14);
}

void Imu::computeAngle_ComplementaryFilter(float alpha) {
    dt = (millis() - prev_time) / 1000.0;
    prev_time = millis();
    
    // Use complementary filter to calculate the angle using accelerometer and gyroscope
    angle.x = alpha*(last_angleX + ((gyroRaw.x - gyroOffset.x) / 131)*dt) + (1-alpha)*accOrientation.x;
    angle.y = alpha*(last_angleY + ((gyroRaw.y - gyroOffset.y) / 131)*dt) + (1-alpha)*accOrientation.y;
    angle.z = angle.z + (gyroRaw.z - gyroOffset.z) * gyroScale * dt;
    last_angleX = angle.x;
    last_angleY = angle.y;
}

int Imu::sign(int value){
    return (value > 0) - (value < 0);
}

void Imu::printSensorData() {
    //printValues("Acceleration raw values: ", accRaw.x, accRaw.y, accRaw.z);
    //printValues("Gyroscope raw values: ", gyroRaw.x, gyroRaw.y, gyroRaw.z);
    printValues("Angle X: ", accOrientation.x, angle.x, angle2.x);
    //printValues("Angle Y: ", accOrientation.y, angle.y, angle2.y);
}