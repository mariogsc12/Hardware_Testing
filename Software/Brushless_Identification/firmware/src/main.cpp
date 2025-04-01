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
float kp=0.15, ki=0.7, kd=0.001;
float target = 20, controlAction_MaxValue = 60;

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
    
    if (sampleTime.check()) {
        encoder_left.update();
        
        // Filtro de paso bajo para suavizar la velocidad medida
        //float alpha = 0.1;
        //feedback = alpha * encoder_left.getSpeed() + (1 - alpha) * feedback;
        
        feedback=encoder_left.getSpeed();
        
        // Calcular control PID manualmente
        pid = PID();
        
        // Limitar la salida del PID
        pid = constrain(pid, -controlAction_MaxValue, controlAction_MaxValue);
        
        // Mover el motor
        motor_left.move(pid);
        
        // Imprimir valores
        Serial.print("Control_action: "); Serial.print(pid);
        Serial.print(" - Setpoint: "); Serial.print(target);
        Serial.print(" - Speed: "); Serial.println(feedback);
        
        // sampleTime.reset();  // creo que no es necesario
    }
}


float PID() {
    error = target - feedback;
    
    dt = sample_time;  // valor aproximado (si se encuentran problemas calcular en el loop)

    P = kp * error;
    I = ki * (errSum = errSum + (error * dt));
    errSum = constrain(errSum, -maxSum, maxSum);  // Limitar la integral (solución sencilla a wind-up)
    D = kd * (error - prevErr) / dt;
    prevErr = error;

    return P + I + D;
}
