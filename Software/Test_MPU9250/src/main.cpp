#include <Arduino.h>
#include <Wire.h>
#include <MPU9250_WE.h>

#define MPU9250_ADDR 0x68  // Dirección I2C

MPU9250_WE mpu(&Wire, MPU9250_ADDR); 

void setup() {
  Serial.begin(115200);
  Wire.begin(8, 9);  // SDA = GPIO 8, SCL = GPIO 9

  if (!mpu.init()) {
    Serial.println("No se pudo encontrar el MPU9250");
    while (1);
  }

  // Calibración automática del giroscopio y acelerómetro
  mpu.autoOffsets();
  mpu.enableGyrDLPF(); // Filtro digital
  mpu.setGyrRange(MPU9250_GYRO_RANGE_250);
  mpu.setAccRange(MPU9250_ACC_RANGE_2G);
  mpu.setMagOpMode(AK8963_CONT_MODE_100HZ); // Activar magnetómetro

  Serial.println("MPU9250 listo.");
}

void loop() {
  xyzFloat angles = mpu.getAngles(); 

  Serial.print("Yaw: "); Serial.print(angles.z, 2);
  Serial.print("\tPitch: "); Serial.print(angles.x, 2);
  Serial.print("\tRoll: "); Serial.println(angles.y, 2);

  delay(100);  
}
