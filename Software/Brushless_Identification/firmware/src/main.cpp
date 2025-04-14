/*
#include <Arduino.h>
#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>
#include <hardware/IMU.hpp>
#include <utilities/KalmanFilter.hpp>
#include <utilities/Butterworth_Filter.h>

const int sample_time = 20;
Metro sampleTime(sample_time);
ButterworthFilter speed_filter({b0, b1, b2}, {a1, a2});

float speed;
volatile float feedback = 0.00;
float P = 0.00, I = 0.00, D = 0.00;
float error = 0.00, prevErr = 0.00;
float errSum = 0.00, maxSum = 200;
float pid = 0.00;
//float maxSum;

float PID();

float kp = 2, ki = 0.25, kd = 0.25;
float target=0.0, controlAction_MaxValue = 100;
float maxOutput = controlAction_MaxValue;

MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM, PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_STOP);
Encoder encoder_left(PIN_ENCODER_LEFT_A, PIN_ENCODER_LEFT_B, 2500 * 3.9 * 4, sample_time);

IMU imu;
KalmanFilter kalmanPitch;

int8_t control_action = 0;
int start_time = 0;
int elapsed_time = 0;
String message;

void encoderCount_1() { encoder_left.count1(); }
void encoderCount_2() { encoder_left.count2(); }

void setup() 
{
    Serial.begin(115200);

    // Inicializar motor y encoder
    motor_left.initialize();
    encoder_left.initialize();
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), encoderCount_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_B), encoderCount_2, CHANGE);

    // Inicializar IMU
    if (!imu.begin()) {
        Serial.println("Error inicializando IMU");
        while (true);
    }

    imu.calibrateGyro();
    imu.readRaw();
    imu.computeAccelerometerAngles();
    kalmanPitch.update(imu.getPitchAcc(), 0, 0);

    start_time = millis();
}

void loop() 
{
    if (sampleTime.check() == 1)
    {
        elapsed_time = millis() - start_time;

        imu.readRaw();
        imu.computeAccelerometerAngles();

        float dt = sample_time / 1000.0;
        float pitch = kalmanPitch.update(imu.getPitchAcc(), imu.getGxDPS(), dt);
        encoder_left.update();
        speed = encoder_left.getSpeed();

        feedback = pitch;

        control_action = PID();

        motor_left.move(control_action);

        message = String(millis()) + ", " + String(control_action) + ", " + String(pitch, 2) + ", " + String(speed, 2);
        Serial.println(message);
    }
}

float PID() {
    error = target - feedback;

    //if (abs(error) < 1) error = 0;

    P = kp * error;

    float dt = sample_time / 1000.0; 

    errSum += error * dt;
    errSum = constrain(errSum, -maxSum, maxSum);
    I = ki * errSum;

    D = kd * (error - prevErr) / dt;
    prevErr = error;

    float output = P + I + D;

    output = constrain(output, -maxOutput, maxOutput);

    return output;
}
*/