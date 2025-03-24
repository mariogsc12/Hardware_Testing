#include <Arduino.h>
#include <MainProgram.h>


#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>

Metro sampleTime(10);

MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM,PIN_MOTOR_LEFT_DIR);
Encoder encoder_left(PIN_ENCODER_LEFT_A,PIN_ENCODER_LEFT_B);

void writeToMatlab(float control, float speed) {
  byte *b_control = (byte*)&control;
  byte *b_speed = (byte*)&speed;
  
  Serial.write(b_control, 4); // Enviar 4 bytes (float control)
  Serial.write(b_speed, 4);   // Enviar 4 bytes (float speed)
  Serial.write(13); // '\r'
  Serial.write(10); // '\n'
}

uint8_t control_action = 0;
int elapsed_time = 0;
float speed = 0;

void setControlAction(int time){
  int time_sec = time / 1000;

  if(time_sec <= 10)return 0;
  else if(time_sec > 10 && time_sec <= 20)return -100;
  else if(time_sec > 20 && time_sec <= 30)return -75;
  else if(time_sec > 30 && time_sec <= 40)return -50;
  else if(time_sec > 40 && time_sec <= 50)return -25;
  else if(time_sec > 50 && time_sec <= 60)return -10;
  else if(time_sec > 60 && time_sec <= 70)return -5;
  else if(time_sec > 70 && time_sec <= 80)return 10;
  else if(time_sec > 80 && time_sec <= 90)return 20;
  else if(time_sec > 90 && time_sec <= 100)return 40;
  else if(time_sec > 100 && time_sec <= 110)return 60;
  else if(time_sec > 110 && time_sec <= 120)return 80;
  else if(time_sec > 120 && time_sec <= 130)return 100;
  else return 0;

}

void encoderCount_1() {
  encoder.count1();
}
void encoderCount_2() {
  encoder.count2();
}

void setup() 
{
    //mainSetup();
    Serial.begin(115200);
    pinMode(PIN_RADIO_CH1,INPUT);
    pinMode(PWM_PIN_OUT,OUTPUT);
    pinMode(DIR_PIN_OUT,OUTPUT);
    motor_left.initialize();
    encoder_left.initialize();
    attachInterrupt(digitalPinToInterrupt(23), encoderCount_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(22), encoderCount_2, CHANGE);
}

void loop() 
{
  
  if(sampleTime.check()==1)
  { 
    elapsed_time = millis();
    control_action = setControlAction(elapsed_time);
    motor_left.move(control_action);
    encoder_left.update();
    speed = encoder_left.getSpeed();
    writeToMatlab(control_action,speed);
  }
   
}
