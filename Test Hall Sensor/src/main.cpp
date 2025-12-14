#include <Arduino.h>

// Definición de pines
int DIR_PIN_OUT = 15;   // Dirección del motor
int PWM_PIN_OUT = 17;   // Salida PWM para el motor
int HALL_PIN = 11;      // Pin del sensor Hall

volatile float tic, tac, feedback = 0.00;
float now, prvTime, dt;
float P = 0.00, I = 0.00, D = 0.00, error = 0.00, prevErr = 0.00, errSum = 0.00, pid = 0.00;
float kp = 0.15, ki = 0.7, kd = 0.001;
float target = 15; // Velocidad deseada inicial
float maxSum = 50;
float trgt_min = 12, trgt_max = 25, fb_min = 104, fb_max = 46;

void intrupt();
float PID();
void Plotter();
void Trace();

void setup() {
  Serial.begin(115200);
  pinMode(DIR_PIN_OUT, OUTPUT);
  pinMode(PWM_PIN_OUT, OUTPUT);
  pinMode(HALL_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), intrupt, RISING);
  digitalWrite(DIR_PIN_OUT, LOW); // Dirección fija
  Serial.println("Ingrese la velocidad deseada:");
}

void loop() {
  now = millis();
  dt = (now - prvTime) / 1000.00;
  prvTime = now;
  
  if (Serial.available()) {
    target = Serial.parseFloat(); // Leer velocidad deseada desde el monitor serie
    Serial.print("Nueva velocidad objetivo: ");
    Serial.println(target);
  }
  
  pid = PID();
  analogWrite(PWM_PIN_OUT, round(pid = constrain(pid, trgt_min, trgt_max)));
  Plotter();
}

void intrupt() {
  tic = millis();
  feedback = tic - tac;
  tac = tic;
  feedback = map(feedback, fb_min, fb_max, trgt_min, trgt_max);
}

float PID() {
  noInterrupts();
  error = target - feedback;
  interrupts();
  P = kp * error;
  I += ki * error * dt;
  I = constrain(I, -maxSum, maxSum);
  D = kd * (error - prevErr) / dt;
  prevErr = error;
  return P + I + D;
}

void Plotter() {
  Serial.println(digitalRead(HALL_PIN));
  Serial.print("Feedback: ");
  Serial.print(feedback, 3);
  Serial.print("  PID: ");
  Serial.print(pid, 3);
  Serial.print("  Target: ");
  Serial.println(target);
}
