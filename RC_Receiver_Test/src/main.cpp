#include <Arduino.h>
#include <Metro.h>

#define CH1 23
#define CH2 22
#define CH3 21
#define CH4 19
#define CH5 18
#define CH6 17

#include "config.h"
#include <Metro.h>

Metro ledMetro = Metro(200);
Metro printMetro = Metro(20);

// PWM decoder variables
int pwm1 = 0;
int pwm2 = 0;
int pwm3 = 0;
int pwm4 = 0;
int pwm5 = 0;
int pwm6 = 0;



void printTask();
void decodePwm_1();
void decodePwm_2();
void decodePwm_3();
void decodePwm_4();
void decodePwm_5();
void decodePwm_6();



void setup() {
  Serial.begin(115200); // Serial to PC

  // pwm decoder interrupts
  attachInterrupt(digitalPinToInterrupt(CH1), decodePwm_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH2), decodePwm_2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH3), decodePwm_3, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH4), decodePwm_4, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH5), decodePwm_5, CHANGE);
  attachInterrupt(digitalPinToInterrupt(CH6), decodePwm_6, CHANGE);
}

void loop() {
  printTask(); // print PWM values, formatted for the Serial Plotter
}

void printTask() {
  if (printMetro.check()) {
    Serial.print(pwm1);
    Serial.print(',');
    Serial.print(pwm2);
    Serial.print(',');
    Serial.print(pwm3);
    Serial.print(',');
    Serial.print(pwm4);
    Serial.print(',');
    Serial.print(pwm5);
    Serial.print(',');
    Serial.println(pwm6);
  }
}


// Interrupt callbacks to measure the pwm duty cycle
void decodePWM(const int CH, int *g_PWM)
{
  static unsigned long riseTime = micros(); // initialize riseTime
  if (digitalRead(CH) == 1) { // the signal has risen
    riseTime = micros(); // save the rise time
  }
  else { // the signal has fallen
    *g_PWM = micros() - riseTime; // compute the duration of the high pulse
  }

}

void decodePwm_1() {
  decodePWM(CH1,&pwm1);
}

void decodePwm_2() {
  decodePWM(CH2,&pwm2);
}

void decodePwm_3() {
  decodePWM(CH3,&pwm3);
}

void decodePwm_4() {
  decodePWM(CH4,&pwm4);
}

void decodePwm_5() {
  decodePWM(CH5,&pwm5);
}

void decodePwm_6() {
  decodePWM(CH6,&pwm6);
}