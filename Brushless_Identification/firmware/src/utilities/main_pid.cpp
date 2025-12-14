
#include <Arduino.h>
//#include <MainProgram.h>
#include <hardware/MotorBLDC.hpp>
#include <hardware/Encoder.hpp>
#include <config/definitions.h>
#include <utilities/Metro.h>
#include <config/pinout.h>
#include <utilities/Butterworth_Filter.h>

const int sample_time = 20;
Metro sampleTime(sample_time);
ButterworthFilter speed_filter({b0, b1, b2}, {a1, a2});
/*
// Variables PID

volatile float feedback = 0.00;
float P = 0.00, I = 0.00, D = 0.00;
float error = 0.00, prevErr = 0.00;
float errSum = 0.00, maxSum = 200;
float pid = 0.00;
//float maxSum;
*/

int8_t control_action = 0;
int elapsed_time = 0;
float speed_left = 0;
float speed_right=0;
float filteredSpeed=0;
int start_time = 0;
String message;

//float PID();

/*
float kp = 1.5, ki = 3, kd = 0.02;
float target, controlAction_MaxValue = 100;
float maxOutput = controlAction_MaxValue;
*/


MotorBLDC motor_left(PIN_MOTOR_LEFT_PWM, PIN_MOTOR_LEFT_DIR, PIN_MOTOR_LEFT_BRAKE);
Encoder encoder_left(PIN_ENCODER_LEFT_A,PIN_ENCODER_LEFT_B,2500*3.9*4,sample_time);

MotorBLDC motor_right(PIN_MOTOR_RIGHT_PWM, PIN_MOTOR_RIGHT_DIR, PIN_MOTOR_RIGHT_BRAKE);
Encoder encoder_right(PIN_ENCODER_RIGHT_A,PIN_ENCODER_RIGHT_B,2500*3.9*4,sample_time);

int setControlAction(int time){
  int time_sec = time / 1000;

  if(time_sec <= 5)return 10;
  else if(time_sec >5 && time_sec <= 10)return 20;
  else if(time_sec > 10 && time_sec <= 15)return 30;
  else if(time_sec > 15 && time_sec <= 20)return 40;
  else if(time_sec > 20 && time_sec <= 25)return 50;
  else if(time_sec > 25 && time_sec <= 30)return 10;
  else if(time_sec > 30 && time_sec <= 35)return 10;
  else if(time_sec > 35 && time_sec <= 40)return 10;
  else if(time_sec > 40 && time_sec <= 45)return 10;
  else if(time_sec > 45 && time_sec <= 50)return 10;
  //else if(time_sec > 50 && time_sec <= 55)return 40;
  //else if(time_sec > 55 && time_sec <= 60)return 50;
  //else if(time_sec > 60 && time_sec <= 65)return 60;
  else return 10;
}

/*
float setTarget(int time){
  int time_sec = time / 1000;
  if(time_sec <= 10)return 50;
  else if(time_sec >10 && time_sec <= 20)return 60;
  else return 60;
}
*/

void encoderCount_left_1() { encoder_left.count1();}
void encoderCount_left_2() { encoder_left.count2();}

void encoderCount_right_1() { encoder_right.count1();}
void encoderCount_right_2() { encoder_right.count2();}

void setup() 
{
    //mainSetup();
    Serial.begin(115200);
    motor_left.initialize();
    encoder_left.initialize();

    motor_right.initialize();
    encoder_right.initialize();

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_A), encoderCount_left_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_LEFT_B), encoderCount_left_2, CHANGE);

    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_A), encoderCount_right_1, CHANGE);
    attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_RIGHT_B), encoderCount_right_2, CHANGE);
    
    start_time = millis();
}

void loop() 
{
  if(sampleTime.check()==1)
  { 
    //Para controlar con accion de control
    elapsed_time = millis() - start_time;
    control_action=setControlAction(elapsed_time);
    motor_left.move(control_action);
    motor_right.move(control_action);

    
    //elapsed_time = millis() - start_time;
    //target=setTarget(elapsed_time);
    

    encoder_left.update();
    encoder_right.update();
    speed_left = encoder_left.getSpeed();
    speed_right = encoder_right.getSpeed();

    //filteredSpeed=speed_filter.update(speed);

    //feedback = filteredSpeed;
    /*
    if (millis() - start_time < 1000) {
        feedback = speed;
      } else {
        feedback = filteredSpeed;
      }
*/

    // Calcular control PID
    
    //pid = PID();
    //pid = constrain(pid, -controlAction_MaxValue, controlAction_MaxValue);
    

    //motor_left.move(pid);

    
    //Serial.print("Control_action: "); Serial.print(pid);
    //Serial.print(" - Setpoint: "); Serial.print(target);
    //Serial.print(" - Speed: "); Serial.println(speed);
    //Serial.print(" - Filtered Speed: "); Serial.println(feedback);
    

    //data = String(control_action) + "," + String(speed);
    //writeToMatlab(data);
    //Serial.print("time: ");Serial.print(elapsed_time);
    //Serial.print(" - pulses: ");Serial.print(encoder_left.getPulses());
    //Serial.print(" - control action: ");Serial.print(control_action);
    //Serial.print(" - speed: ");Serial.println(speed);
    //Serial.print(" - filtered_speed: ");Serial.println(filtered_speed);

    //message = String(millis()) +"," + String(control_action) + "," + String(speed) + "," + String(filteredSpeed);
    //Serial.println(message);

    message = String(millis()) +"," + String(control_action) + "," + String(speed_left) + "," + String(speed_right);
    Serial.println(message);
  }
}


/*
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

     // BLOQUE NUEVO: Si el error cambia de signo y es pequeño, no invierte el sentido del control para que no haya bloqueo
     //if ((output > 0 && feedback > target) || (output < 0 && feedback < target)) {
       // output = 0; 
   // }
    output = constrain(output, -maxOutput, maxOutput);

    return output;
}
*/