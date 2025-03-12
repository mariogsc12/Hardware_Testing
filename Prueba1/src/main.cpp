#include<Arduino.h>
#include <Wire.h>
#include "MPU9250.h"

// Crear instancia del sensor
MPU9250 sensor;

void setup() {
    Serial.begin(115200);
    Wire.begin();
    
    // Inicializar el sensor
    if (!sensor.setup(0x68)) {  // Dirección I2C por defecto 0x68
        Serial.println("Error: No se encontró el MPU9250");
        while (1);
    }
    Serial.println("MPU9250 detectado correctamente");
}

void loop() {
    sensor.update();

    // Leer y mostrar valores de aceleración
    Serial.print("Aceleración (m/s²) - X: "); Serial.print(sensor.getAccX());
    Serial.print(" Y: "); Serial.print(sensor.getAccY());
    Serial.print(" Z: "); Serial.println(sensor.getAccZ());

    // Leer y mostrar valores del giroscopio
    Serial.print("Giroscopio (°/s) - X: "); Serial.print(sensor.getGyroX());
    Serial.print(" Y: "); Serial.print(sensor.getGyroY());
    Serial.print(" Z: "); Serial.println(sensor.getGyroZ());

    // Leer y mostrar valores del magnetómetro
    Serial.print("Magnetómetro (uT) - X: "); Serial.print(sensor.getMagX());
    Serial.print(" Y: "); Serial.print(sensor.getMagY());
    Serial.print(" Z: "); Serial.println(sensor.getMagZ());

    Serial.println("--------------------------------------");
    delay(500);  // Pequeña pausa para evitar saturar el monitor serie
}
