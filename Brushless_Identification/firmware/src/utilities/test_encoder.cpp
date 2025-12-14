/*
#include <Arduino.h>
#include "Hardware/Encoder.hpp"

// Configuración
const int pinA = 21;
const int pinB = 45;
const int PPR = 2500;
const float SAMPLE_TIME = 100.0; // ms

Encoder encoder(pinA, pinB, PPR, SAMPLE_TIME);

void IRAM_ATTR isrA() {
  encoder.count1();
}

void IRAM_ATTR isrB() {
  encoder.count2();
}

void setup() {
  Serial.begin(115200);
  encoder.initialize();

  attachInterrupt(digitalPinToInterrupt(pinA), isrA, CHANGE);
  attachInterrupt(digitalPinToInterrupt(pinB), isrB, CHANGE);

  Serial.println("Encoder iniciado...");
}

void loop() {
  static unsigned long lastUpdate = 0;
  if (millis() - lastUpdate >= SAMPLE_TIME) {
    lastUpdate = millis();

    long pulses = encoder.getPulses();  // Leer antes de resetear
    encoder.update();
    float speed = encoder.getSpeed();

    // Ángulo de 0 a 360
    float angle = fmod(((float)pulses / PPR) * 360.0, 360.0);
    if (angle < 0) angle += 360.0;

    Serial.print("Pulsos: ");
    Serial.print(pulses);
    Serial.print(" | Velocidad: ");
    Serial.print(speed, 2);
    Serial.print(" RPM | Ángulo: ");
    Serial.print(angle, 2);
    Serial.println("°");
  }

  delay(10);
}
*/