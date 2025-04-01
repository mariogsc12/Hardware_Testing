#include <Arduino.h>
#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>

const int sample_time = 20;  // 🔴 Reducido para mejorar respuesta
Metro sampleTime(sample_time);

// Variables PID
volatile float tic, tac, feedback = 0.00;
bool dir = 0;
float now, prvTime, dt;
float P = 0.00, I = 0.00, D = 0.00, error = 0.00, errDiff = 0.00, prevErr = 0.00, maxSum = 50, errSum = 0.00, pid = 0.00;

float PID();

// Ganancias PID y límites
float kp = 2.25, ki = 78, kd = 0;
float target = 20, trgt_min = 10, trgt_max = 30, fb_min = 40, fb_max = 20;

MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM, PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_BRAKE, PIN_MOTOR_LEFT_STOP);
Encoder encoder_left(PIN_ENCODER_LEFT_A, PIN_ENCODER_LEFT_B, 2500 * 3.9 * 4, sample_time);

void encoderCount_1() { encoder_left.count1(); }
void encoderCount_2() { encoder_left.count2(); }

void setup() {
    Serial.begin(115200);

    motor_left.initialize();
    encoder_left.initialize();

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), encoderCount_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_B), encoderCount_2, CHANGE);

    Serial.println("Sistema listo. Iniciando...");
}

void loop() {
    now = millis();
    dt = (now - prvTime) / 1000.00;
    prvTime = now;

    if (sampleTime.check()) {
        encoder_left.update();

        // Filtro de paso bajo para suavizar la velocidad medida
        //float alpha = 0.1;
        //feedback = alpha * encoder_left.getSpeed() + (1 - alpha) * feedback;

        feedback=encoder_left.getSpeed();

        // Calcular control PID manualmente
        pid = PID();

        // Limitar la salida del PID
        pid = constrain(pid, trgt_min, trgt_max);

        // Mover el motor
        motor_left.move(pid);

        // Imprimir valores
        Serial.print("Control_action: "); Serial.print(pid);
        Serial.print(" - Setpoint: "); Serial.print(target);
        Serial.print(" - Speed: "); Serial.println(feedback);
        
        sampleTime.reset();
    }
}

// 🔴 Función PID manual
float PID() {
    noInterrupts();  
    error = target - feedback;
    interrupts();

    // 🔴 Cálculo de términos PID
    P = kp * error;
    I = ki * (errSum = errSum + (error * dt));
    errSum = constrain(errSum, -maxSum, maxSum);  // Limitar la integral
    D = kd * (error - prevErr) / dt;
    prevErr = error;

    return P + I + D;
}
