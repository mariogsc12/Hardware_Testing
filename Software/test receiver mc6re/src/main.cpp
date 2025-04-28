#include <Arduino.h>

// Pines de los canales
const int ch1Pin = 12;  
const int ch2Pin = 13;  
const int ch3Pin = 14;  

// Últimos valores guardados para comparar
uint32_t lastCh1 = 1500;
uint32_t lastCh2 = 1500;
uint32_t lastCh3 = 1500;

// Umbral para detectar movimiento
const int movementThreshold = 20; // microsegundos

void setup() {
  Serial.begin(115200);

  pinMode(ch1Pin, INPUT);
  pinMode(ch2Pin, INPUT);
  pinMode(ch3Pin, INPUT);

  Serial.println("Sistema iniciado: esperando movimiento de joystick...");
}

void loop() {
  // Leer el pulso actual de cada canal
  uint32_t ch1PulseWidth = pulseIn(ch1Pin, HIGH, 25000); // Timeout 25ms
  uint32_t ch2PulseWidth = pulseIn(ch2Pin, HIGH, 25000);
  uint32_t ch3PulseWidth = pulseIn(ch3Pin, HIGH, 25000);

  // Comprobar movimiento en Canal 1
  if (abs((int32_t)(ch1PulseWidth - lastCh1)) > movementThreshold) {
    Serial.println("¡Movimiento detectado en Canal 1!");
    lastCh1 = ch1PulseWidth;
  }

  // Comprobar movimiento en Canal 2
  if (abs((int32_t)(ch2PulseWidth - lastCh2)) > movementThreshold) {
    Serial.println("¡Movimiento detectado en Canal 2!");
    lastCh2 = ch2PulseWidth;
  }

  // Comprobar movimiento en Canal 3
  if (abs((int32_t)(ch3PulseWidth - lastCh3)) > movementThreshold) {
    Serial.println("¡Movimiento detectado en Canal 3!");
    lastCh3 = ch3PulseWidth;
  }

  delay(50); // Pequeño retardo para estabilizar
}
