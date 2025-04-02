#include <Arduino.h>
#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>

const int sample_time = 2;
Metro sampleTime(sample_time);

// Variables PID
volatile float feedback = 0.00;
float P = 0.00, I = 0.00, D = 0.00;
float error = 0.00, prevErr = 0.00;
float errSum = 0.00, maxSum = 100;
float pid = 0.00;

#define NUM_SAMPLES 10
float speedSamples[NUM_SAMPLES];
int sampleIndex = 0;
float speedSum = 0;
int printCounter = 0;
//float maxSum;

float PID();

float kp = 3, ki = 0.8, kd = 0.12;
float target = 20, controlAction_MaxValue = 60;
float maxOutput = controlAction_MaxValue;

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

    for (int i = 0; i < NUM_SAMPLES; i++) {
        speedSamples[i] = 0;
    }
}

void loop() {
    if (sampleTime.check()) {

       // maxSum = abs(target) * 2;

        encoder_left.update();

        float currentSpeed = encoder_left.getSpeed();
        feedback = currentSpeed;

        // Calcular control PID
        pid = PID();
        pid = constrain(pid, -controlAction_MaxValue, controlAction_MaxValue);

        // Mover el motor
        motor_left.move(pid);

        // Guardar para media
        speedSum -= speedSamples[sampleIndex];
        speedSamples[sampleIndex] = currentSpeed;
        speedSum += currentSpeed;
        sampleIndex = (sampleIndex + 1) % NUM_SAMPLES;

        printCounter++;
        if (printCounter >= 10) {
            float averageSpeed = speedSum / NUM_SAMPLES;

            Serial.print("Control_action: "); Serial.print(pid);
            Serial.print(" - Setpoint: "); Serial.print(target);
            Serial.print(" - Speed: "); Serial.print(feedback);
            Serial.print(" - Velocidad promedio: "); Serial.println(averageSpeed);

            printCounter = 0;
        }
    }
}

float PID() {
    error = target - feedback;

    if (abs(error) < 0.5) error = 0;

    P = kp * error;

    errSum += error * sample_time;
    errSum = constrain(errSum, -maxSum, maxSum);
    I = ki * errSum;

    static float lastFeedback = 0;
    D = -kd * (feedback - lastFeedback) / sample_time;
    lastFeedback = feedback;

    float output = P + I + D;
    output = constrain(output, -maxOutput, maxOutput);

    return output;
}