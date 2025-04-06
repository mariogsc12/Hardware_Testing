#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// Configuración general
MPU6050 accelgyro; // Dirección I2C por defecto 0x68

// Variables para almacenar lecturas y cálculos
int16_t ax, ay, az, gx, gy, gz;
float ax_offset = 0, ay_offset = 0, az_offset = 0;
float gx_offset = 0, gy_offset = 0, gz_offset = 0;
float initial_pitch = 0, initial_roll = 0;
float pitch = 0, roll = 0; // Ángulos dinámicos

// Constantes del filtro complementario
const float alpha = 0.98; // Peso del giroscopio en el filtro
const float dt = 0.01; // Intervalo de tiempo en segundos (10 ms)

// Número de mediciones para calibrar
const int NUM_MEASUREMENTS = 10;
const int MEASUREMENT_INTERVAL = 1000; // 1 segundo

void calibrateSensor();

void setup() {
  Wire.begin();
  Serial.begin(115200);

  // Inicializar el sensor MPU6050
  accelgyro.initialize();

  // Verificar la conexión del sensor
  if (accelgyro.testConnection()) {
    Serial.println("MPU6050 conectado correctamente");
  } else {
    Serial.println("Error al conectar con el MPU6050");
    while (1);
  }

  // Configurar offsets iniciales
  accelgyro.setXAccelOffset(0);
  accelgyro.setYAccelOffset(0);
  accelgyro.setZAccelOffset(0);
  accelgyro.setXGyroOffset(0);
  accelgyro.setYGyroOffset(0);
  accelgyro.setZGyroOffset(0);

  // Calibrar el sensor
  calibrateSensor();
}

///////////////////////////////////   LOOP   ////////////////////////////////////
void loop() {
  // Leer las mediciones del sensor
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calcular ángulos a partir del acelerómetro
  float accel_pitch = atan2(ax, sqrt(ay * ay + az * az)) * 180 / PI;
  float accel_roll = atan2(ay, sqrt(ax * ax + az * az)) * 180 / PI;

  // Convertir valores del giroscopio a grados/segundo
  float gyro_pitch_rate = gx / 131.0;
  float gyro_roll_rate = gy / 131.0;

  // Calcular los ángulos dinámicos usando el filtro complementario
  pitch = alpha * (pitch + gyro_pitch_rate * dt) + (1 - alpha) * accel_pitch;
  roll = alpha * (roll + gyro_roll_rate * dt) + (1 - alpha) * accel_roll;

  // Mostrar las diferencias de ángulo respecto al inicial
  Serial.print("Pitch: ");
  Serial.print(pitch - initial_pitch);
  Serial.print("\tRoll: ");
  Serial.println(roll - initial_roll);

  delay(10); // Actualización cada 10 ms
}

///////////////////////////////////   FUNCIONES   ////////////////////////////////////
void calibrateSensor() {
  Serial.println("Iniciando calibración...");

  long sum_ax = 0, sum_ay = 0, sum_az = 0;
  long sum_gx = 0, sum_gy = 0, sum_gz = 0;

  for (int i = 0; i < NUM_MEASUREMENTS; i++) {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    sum_ax += ax;
    sum_ay += ay;
    sum_az += az;
    sum_gx += gx;
    sum_gy += gy;
    sum_gz += gz;

    Serial.print("Medición ");
    Serial.print(i + 1);
    Serial.println(" tomada");
    delay(MEASUREMENT_INTERVAL);
  }

  // Calcular la media
  ax_offset = sum_ax / NUM_MEASUREMENTS;
  ay_offset = sum_ay / NUM_MEASUREMENTS;
  az_offset = sum_az / NUM_MEASUREMENTS;
  gx_offset = sum_gx / NUM_MEASUREMENTS;
  gy_offset = sum_gy / NUM_MEASUREMENTS;
  gz_offset = sum_gz / NUM_MEASUREMENTS;

  // Ajustar los offsets del sensor
  accelgyro.setXAccelOffset(ax_offset);
  accelgyro.setYAccelOffset(ay_offset);
  accelgyro.setZAccelOffset(az_offset);
  accelgyro.setXGyroOffset(gx_offset);
  accelgyro.setYGyroOffset(gy_offset);
  accelgyro.setZGyroOffset(gz_offset);

  // Calcular los ángulos iniciales
  initial_pitch = atan2(ax_offset, sqrt(ay_offset * ay_offset + az_offset * az_offset)) * 180 / PI;
  initial_roll = atan2(ay_offset, sqrt(ax_offset * ax_offset + az_offset * az_offset)) * 180 / PI;

  pitch = initial_pitch;
  roll = initial_roll;

  Serial.println("Calibración completada.");
  Serial.print("Pitch inicial: ");
  Serial.println(initial_pitch);
  Serial.print("Roll inicial: ");
  Serial.println(initial_roll);
}