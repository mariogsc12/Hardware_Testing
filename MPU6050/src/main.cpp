
//Prueba con filtro complementario
/*
#include <Arduino.h>
#include "Wire.h"
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

int16_t ax, ay, az, gx, gy, gz;

// Ángulos
float pitch = 0, roll = 0, yaw = 0;

// Tiempo
unsigned long last_time = 0;

// Offset del giroscopio
float gx_offset = 0, gy_offset = 0, gz_offset = 0;

// Filtro complementario
const float alpha = 0.95;

void calibrateGyro() {
  long sum_gx = 0, sum_gy = 0, sum_gz = 0;
  const int N = 500;

  Serial.println("Calibrando giroscopio...");

  for (int i = 0; i < N; i++) {
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    sum_gx += gx;
    sum_gy += gy;
    sum_gz += gz;
    delay(2);
  }

  gx_offset = sum_gx / (float)N;
  gy_offset = sum_gy / (float)N;
  gz_offset = sum_gz / (float)N;

  Serial.println("Calibración terminada:");
  Serial.print("Gx offset: "); Serial.println(gx_offset);
  Serial.print("Gy offset: "); Serial.println(gy_offset);
  Serial.print("Gz offset: "); Serial.println(gz_offset);
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error conectando al MPU6050");
    while (1);
  }

  calibrateGyro();
  last_time = micros();
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calcular dt
  unsigned long now = micros();
  float dt = (now - last_time) / 1000000.0;
  last_time = now;

  // Convertir gyro a grados/s y restar offset
  float gyro_pitch_rate = (gx - gx_offset) / 131.0;
  float gyro_roll_rate  = (gy - gy_offset) / 131.0;
  float gyro_yaw_rate   = (gz - gz_offset) / 131.0;

  // Calcular ángulos con acelerómetro (para corrección)
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  float accel_pitch = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;
  float accel_roll  = atan2(ay_g, sqrt(ax_g * ax_g + az_g * az_g)) * 180.0 / PI;

  // Filtro complementario
  pitch = alpha * (pitch + gyro_pitch_rate * dt) + (1 - alpha) * accel_pitch;
  roll  = alpha * (roll + gyro_roll_rate  * dt) + (1 - alpha) * accel_roll;

  // Yaw sigue solo con integración
  yaw += gyro_yaw_rate * dt;

  // Mostrar resultados
  Serial.print("Pitch: ");
  Serial.print(pitch, 2);
  Serial.print("\tRoll: ");
  Serial.print(roll, 2);
  Serial.print("\tYaw: ");
  Serial.println(yaw, 2);

  delay(10);
}
*/