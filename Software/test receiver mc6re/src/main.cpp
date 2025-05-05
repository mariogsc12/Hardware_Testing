#include <Arduino.h>
#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <hardware/IMU.hpp>
#include <hardware/Receiver.hpp>
//#include <hardware/Wattmeter.hpp>
#include <config/definitions.h>
#include <config/pinout.h>
#include <utilities/Metro.h>
#include <utilities/Butterworth_Filter.hpp>


const int sample_time = 20;
Metro sampleTime(sample_time);

int start_time = 0;
String message;
float speed_left = 0;
float speed_right=0;

MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM, PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_BRAKE);
Encoder encoder_left(PIN_ENCODER_LEFT_A,PIN_ENCODER_LEFT_B,2500*3.9*4,sample_time);

MotorBLDC motor_right(PIN_MOTOR_RIGHT_PWM, PIN_MOTOR_RIGHT_DIR, PIN_MOTOR_RIGHT_BRAKE);
Encoder encoder_right(PIN_ENCODER_RIGHT_A,PIN_ENCODER_RIGHT_B,2500*3.9*4,sample_time);

//IMU imu(Serial2, PIN_IMU_RX, PIN_IMU_TX);

//Wattmeter wattmeter(PIN_WATT_SDA, PIN_WATT_SCL);

Receiver receiver(PIN_RADIO_CH1, PIN_RADIO_CH3, PIN_RADIO_CH5);

void encoderCount_1() { encoder_left.count1(); }
void encoderCount_2() { encoder_left.count2(); }

void encoderCount_right_1() { encoder_right.count1();}
void encoderCount_right_2() { encoder_right.count2();}

void setup() 
{
    Serial.begin(115200);

    // Inicializar motores y encoders
    motor_left.initialize();
    encoder_left.initialize();

    motor_right.initialize();
    encoder_right.initialize();

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), encoderCount_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_B), encoderCount_2, CHANGE);

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A), encoderCount_right_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_B), encoderCount_right_2, CHANGE);

    //Inicializar IMU
    //imu.begin();

    //Inicialización receiver
    receiver.begin();

    start_time = millis();
}

void loop() {
  if (sampleTime.check() == 1) {

    // Leer señal del receptor
    receiver.update();
    int16_t throttle = receiver.getThrottle();  // -1000 a 1000

    // Escalar a -100 a 100 (PWM)
    int control_signal = map(throttle, -1000, 1000, -100, 100);
    int control_signal = map(throttle, -1000, 1000, -100, 100);
    if (abs(control_signal) < 10) control_signal = 0;

    // Mover ambos motores en la misma dirección
    motor_left.move(control_signal);
    motor_right.move(control_signal);

    // Opcional: imprimir información para depuración
    Serial.print("Throttle: ");
    Serial.print(throttle);
    Serial.print(" -> PWM: ");
    Serial.println(control_signal);
  }
}


