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
    delay(1000);
}

void Imu::update()
{
    accRaw = mpu.getAccRawValues();
    gyroRaw = mpu.getGyrRawValues();
    angle.x = mpu.getRoll();
    angle.y = mpu.getPitch();
    angle.z = mpu.getYaw();
    computeAccelOrientation();
    computeAngle_ComplementaryFilter(0.995);
}

float Imu::getYaw()
{
    float yaw;
    dt_yaw = (millis() - prev_time_yaw) / 1000.0;
    prev_time_yaw = millis();
    yaw = last_angleZ + gyroRaw.z*dt_yaw;
    last_angleZ = yaw;
    return yaw;
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
    angle_cf.x = alpha*(last_angleX_cf + (gyroRaw.x/131)*dt) + (1-alpha)*accOrientation.x;
    angle_cf.y = alpha*(last_angleY_cf + (gyroRaw.y/131)*dt) + (1-alpha)*accOrientation.y;
    angle_cf.z = last_angleZ_cf + gyroRaw.z * gyroScale * dt;
    last_angleX_cf = angle_cf.x;
    last_angleY_cf = angle_cf.y;
    last_angleZ_cf = angle_cf.z;
}

int Imu::sign(int value){
    return (value > 0) - (value < 0);
}

void Imu::printValues(const char* label, float x, float y, float z) {
    Serial.print(label);
    Serial.print(x);
    Serial.print("   ");
    Serial.print(y);
    Serial.print("   ");
    Serial.println(z);
}

void Imu::printSensorData() {
    //printValues("Acceleration raw values: ", accRaw.x, accRaw.y, accRaw.z);
    //printValues("Gyroscope raw values: ", gyroRaw.x, gyroRaw.y, gyroRaw.z);
    printValues("Angle raw values: ", angle.x, angle.y, angle.z);
    printValues("Complemta filter: ", angle_cf.x, angle_cf.y, angle_cf.z);
}