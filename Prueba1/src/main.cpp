#include <Arduino.h>
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

// Instancia del sensor
MPU6050 sensor;

// Variables globales
int16_t ax, ay, az;
float angulo_inicial; // Variable global para almacenar el ángulo inicial

float calibrarSensorX();
float CalcularAnguloX(float anguloinicial);

// Función para calibrar el sensor en el eje X y devolver el ángulo inicial

void setup() {
  Serial.begin(57600);
  Wire.begin();
  sensor.initialize();

  if (sensor.testConnection()) {
    Serial.println("Sensor iniciado correctamente");
  } else {
    Serial.println("Error al iniciar el sensor");
    while (1); // Detener si no hay conexión con el sensor
  }

  // Calibrar el sensor y guardar el ángulo inicial
  angulo_inicial = calibrarSensorX();
  Serial.print("Ángulo inicial calibrado en X: ");
  Serial.println(angulo_inicial);
}

void loop() {
  // Calcular y mostrar el ángulo relativo en el eje X
  float angulo_relativo = CalcularAnguloX(angulo_inicial);
  Serial.print("Ángulo relativo en X: ");
  Serial.println(angulo_relativo);

  delay(500); // Retardo para facilitar la lectura en el monitor serie
}

float calibrarSensorX() {
  long f_ax = 0;
  int p_ax = 0;
  int ax_o = sensor.getXAccelOffset();

  Serial.println("Calibrando eje X, no mover IMU...");

  // Realizar 100 iteraciones para calibrar
  for (int counter = 0; counter < 100; counter++) {
    // Leer la aceleración en los ejes
    sensor.getAcceleration(&ax, &ay, &az);
    f_ax += ax;
    delay(100);
  }
  
  p_ax = f_ax / 100; // Promedio de la aceleración en X
  float angulo_inicial = atan2(p_ax, az) * 180 / PI; // Cálculo del ángulo inicial
  return angulo_inicial;
}

float CalcularAnguloX(float anguloinicial) {
  sensor.getAcceleration(&ax, &ay, &az);
  float angulo_actual = atan2(ax, az) * 180 / PI;
  return angulo_actual - anguloinicial;
}
