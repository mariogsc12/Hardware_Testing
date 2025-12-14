/* ----------------------------------------------------------------- */
/* ---------------------- PINOUT DEFINITIONS ----------------------- */

#ifndef PINOUT_H
#define PINOUT_H

// MOTOR LEFT
#define PIN_MOTOR_LEFT_PWM 41
#define PIN_MOTOR_LEFT_BRAKE 42
#define PIN_MOTOR_LEFT_DIR 2

// ENCODER LEFT
#define PIN_ENCODER_LEFT_A 4
#define PIN_ENCODER_LEFT_B 5

// MOTOR RIGHT
#define PIN_MOTOR_RIGHT_PWM 38
#define PIN_MOTOR_RIGHT_BRAKE 39
#define PIN_MOTOR_RIGHT_DIR 40

// ENCODER RIGHT
#define PIN_ENCODER_RIGHT_A 21
#define PIN_ENCODER_RIGHT_B 45

//WATTMETER
#define PIN_WATT_SDA 8
#define PIN_WATT_SCL 9

//IMU
#define PIN_IMU_TX 16
#define PIN_IMU_RX 15

// RADIO
#define PIN_RADIO_CH1 13 // Joystick izquierda delante/detras
#define PIN_RADIO_CH2 // Joystick derecha delante/detras
#define PIN_RADIO_CH3 12 // Joystick derecha lados
#define PIN_RADIO_CH4  // Joystick izquierda lados
#define PIN_RADIO_CH5 14
#define PIN_RADIO_CH6 
#endif