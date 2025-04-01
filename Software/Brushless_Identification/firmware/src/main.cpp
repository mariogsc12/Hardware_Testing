#include <Arduino.h>
//#include <MainProgram.h>


#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>

const int sample_time = 50;
Metro sampleTime(sample_time);

MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM,PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_BRAKE, PIN_MOTOR_LEFT_STOP);
Encoder encoder_left(PIN_ENCODER_LEFT_A,PIN_ENCODER_LEFT_B,2500*3.9*4,sample_time);
/*
void writeToMatlab(String data) {
  Serial.write(data.c_str(), data.length()); // Enviar todos los caracteres
  Serial.write(13); // Enviar '\r'
  Serial.write(10); // Enviar '\n' (indica fin de línea)
}
*/

int8_t control_action = 0;
int elapsed_time = 0;
float speed = 0;
int start_time = 0;

/*int setControlAction(int time){
  int time_sec = time / 1000;

  if(time_sec <= 5)return -40;
  else if(time_sec >5 && time_sec <= 10)return -39;
  else if(time_sec > 10 && time_sec <= 15)return -38;
  else if(time_sec > 15 && time_sec <= 20)return -36;
  else if(time_sec > 20 && time_sec <= 25)return -34;
  else if(time_sec > 25 && time_sec <= 30)return -32;
  else if(time_sec > 30 && time_sec <= 35)return -29;
  else if(time_sec > 35 && time_sec <= 40)return -25;
  else if(time_sec > 40 && time_sec <= 45)return -21;
  else if(time_sec > 45 && time_sec <= 50)return -15;
  else if(time_sec > 50 && time_sec <= 55)return -8;
  else if(time_sec > 55 && time_sec <= 60)return -1;
  else return 0;

}*/
int setControlAction(int time){
  int time_sec = time / 1000;

  if(time_sec <= 5)return 0;
  else if(time_sec >5 && time_sec <= 10)return 10;
  else if(time_sec > 10 && time_sec <= 15)return -10;
  else if(time_sec > 15 && time_sec <= 20)return -10;
  else if(time_sec > 20 && time_sec <= 25)return 20;
  else if(time_sec > 25 && time_sec <= 30)return 20;
  else if(time_sec > 30 && time_sec <= 35)return -20;
  else if(time_sec > 35 && time_sec <= 40)return -20;
  //else if(time_sec > 40 && time_sec <= 45)return -5;
  //else if(time_sec > 45 && time_sec <= 50)return -5;
  //else if(time_sec > 50 && time_sec <= 55)return -5;
  //else if(time_sec > 55 && time_sec <= 60)return -5;
  else return 0;

}
/*
int setControlAction(int time){
  int time_sec = time / 1000;

  if(time_sec <= 10)return 0;
  else if(time_sec > 10 && time_sec <= 20)return -20;
  else if(time_sec > 20 && time_sec <= 30)return -15;
  else if(time_sec > 30 && time_sec <= 40)return -10;
  else if(time_sec > 40 && time_sec <= 50)return -7;
  else if(time_sec > 50 && time_sec <= 60)return -5;
  else if(time_sec > 60 && time_sec <= 70)return -3;
  else if(time_sec > 70 && time_sec <= 80)return 3;
  else if(time_sec > 80 && time_sec <= 90)return 5;
  else if(time_sec > 90 && time_sec <= 100)return 7;
  else if(time_sec > 100 && time_sec <= 110)return 10;
  else if(time_sec > 110 && time_sec <= 120)return 20;
  else if(time_sec > 120 && time_sec <= 130)return 30;
  else return 0;

}
*/

void encoderCount_1() {
  encoder_left.count1();
}
void encoderCount_2() {
  encoder_left.count2();
}

void setup() 
{
    //mainSetup();
    Serial.begin(115200);
    motor_left.initialize();
    encoder_left.initialize();
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), encoderCount_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_B), encoderCount_2, CHANGE);
    start_time = millis();
}

String data;
String message;
void loop() 
{
  if(sampleTime.check()==1)
  { 
    elapsed_time = millis() - start_time;
    //Serial.print("time: ");Serial.print(elapsed_time);
    //Serial.print(" - pulses: ");Serial.print(encoder_left.getPulses());
    //control_action = 0;
    control_action=setControlAction(elapsed_time);
    motor_left.move(control_action);
    encoder_left.update();
    speed = encoder_left.getSpeed();
    //data = String(control_action) + "," + String(speed);
    //writeToMatlab(data);
    //Serial.print(" - control action: ");Serial.print(control_action);
    //Serial.print(" - speed: ");Serial.println(speed);
    message = String(millis()) +"," + String(control_action) + "," + String(speed);
    Serial.println(message);
  }
}
   