#include <Arduino.h>

// Pines para el puente H
#define IN1 48
#define IN2 45
#define PWM 47

// Acción de control inicial (ajusta este valor según lo necesites)
int control_action = 255;

// Declaración de la función para inicializar PWM
void iniciarPWM();

void setup() {
  // Configurar los pines como salida
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Inicializar el PWM
  iniciarPWM();

  // Iniciar comunicación serie para depuración
  Serial.begin(115200);
  Serial.println("Motor control iniciado");
}

void loop() {
  // Leer la acción de control (puedes modificarlo para recibir valores dinámicamente)
  control_action = constrain(control_action, -255, 255); // Limita el rango a [-255, 255]

  if (control_action > 0) {
    // Movimiento hacia adelante
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    ledcWrite(0, control_action); // Asigna el canal PWM 0 a este motor
  } else if (control_action < 0) {
    // Movimiento hacia atrás
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    ledcWrite(0, -control_action); // Invertir la acción de control para velocidad
  } else {
    // Detener el motor
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    ledcWrite(0, 0);
  }

  // Imprimir el estado actual
  Serial.print("Control action: ");
  Serial.println(control_action);

  delay(100); // Pequeña pausa para evitar saturar el puerto serie
}

void iniciarPWM() {
  // Configurar el canal PWM para la ESP32
  const int freq = 5000;    // Frecuencia de PWM
  const int pwmChannel = 0; // Canal PWM
  const int resolution = 8; // Resolución de 8 bits (0-255)

  // Configuración del canal PWM
  ledcSetup(pwmChannel, freq, resolution);
  // Asociar el pin PWM al canal configurado
  ledcAttachPin(PWM, pwmChannel);
}
