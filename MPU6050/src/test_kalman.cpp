#include <Wire.h>
#include "I2Cdev.h"
#include "MPU6050.h"

MPU6050 mpu;

int16_t ax, ay, az, gx, gy, gz;

// Kalman filter parameters
float Q_angle = 0.001;
float Q_bias = 0.003;
float R_measure = 0.03;

// Estados del filtro Kalman
float pitch_bias = 0, roll_bias = 0;
float P_pitch[2][2] = {{0, 0}, {0, 0}};
float P_roll[2][2]  = {{0, 0}, {0, 0}};
float kalman_pitch = 0, kalman_roll = 0;
float yaw = 0;

// Tiempo
unsigned long last_time = 0;

// Offsets del giroscopio
float gx_offset = 0, gy_offset = 0, gz_offset = 0;

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

  Serial.println("Calibración completada:");
  Serial.print("Gx offset: "); Serial.println(gx_offset);
  Serial.print("Gy offset: "); Serial.println(gy_offset);
  Serial.print("Gz offset: "); Serial.println(gz_offset);
}

// Filtro de Kalman
float kalmanFilter(float acc_angle, float gyro_rate, float& kal_angle, float& bias, float P[2][2], float dt) {
  float rate = gyro_rate - bias;
  kal_angle += dt * rate;

  P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
  P[0][1] -= dt * P[1][1];
  P[1][0] -= dt * P[1][1];
  P[1][1] += Q_bias * dt;

  float S = P[0][0] + R_measure;
  float K[2];
  K[0] = P[0][0] / S;
  K[1] = P[1][0] / S;

  float y = acc_angle - kal_angle;
  kal_angle += K[0] * y;
  bias += K[1] * y;

  float P00_temp = P[0][0];
  float P01_temp = P[0][1];

  P[0][0] -= K[0] * P00_temp;
  P[0][1] -= K[0] * P01_temp;
  P[1][0] -= K[1] * P00_temp;
  P[1][1] -= K[1] * P01_temp;

  return kal_angle;
}

void setup() {
  Wire.begin();
  Serial.begin(115200);
  mpu.initialize();

  if (!mpu.testConnection()) {
    Serial.println("Error conectando al MPU6050");
    while (true);
  }

  calibrateGyro();

  // Inicializar ángulos desde el acelerómetro
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  // Versión corregida: pitch desde ax, roll desde ay
  kalman_pitch = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;
  kalman_roll  = atan2(ay_g, sqrt(ax_g * ax_g + az_g * az_g)) * 180.0 / PI;

  Serial.println("Inicialización Kalman:");
  Serial.print("Pitch inicial: "); Serial.println(kalman_pitch);
  Serial.print("Roll inicial : "); Serial.println(kalman_roll);

  last_time = micros();
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Tiempo
  unsigned long now = micros();
  float dt = (now - last_time) / 1000000.0;
  last_time = now;

  // Acelerómetro (g)
  float ax_g = ax / 16384.0;
  float ay_g = ay / 16384.0;
  float az_g = az / 16384.0;

  // Giroscopio (°/s)
  float gx_dps = (gx - gx_offset) / 131.0;
  float gy_dps = (gy - gy_offset) / 131.0;
  float gz_dps = (gz - gz_offset) / 131.0;

  // Ángulos del acelerómetro (ajustados a orientación horizontal)
  float accel_pitch = atan2(ax_g, sqrt(ay_g * ay_g + az_g * az_g)) * 180.0 / PI;
  float accel_roll  = atan2(ay_g, sqrt(ax_g * ax_g + az_g * az_g)) * 180.0 / PI;

  // Kalman filter
  kalman_pitch = kalmanFilter(accel_pitch, gx_dps, kalman_pitch, pitch_bias, P_pitch, dt);
  kalman_roll  = kalmanFilter(accel_roll,  gy_dps, kalman_roll,  roll_bias,  P_roll,  dt);

  // Yaw por integración directa
  yaw += gz_dps * dt;

  // Mostrar resultados
  Serial.print("Pitch (Kalman): ");
  Serial.print(kalman_pitch, 2);
  Serial.print("\tRoll (Kalman): ");
  Serial.print(kalman_roll, 2);
  Serial.print("\tYaw (Gyro): ");
  Serial.println(yaw, 2);

  delay(10);
}
