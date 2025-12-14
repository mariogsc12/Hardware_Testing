#include <Arduino.h>
#include <TimerOne.h>

const int HALL_PIN = 2;                     // interrupt feedback pin 
const int PWM_PIN_OUT = 3;                  // 490Hz PWM Output
const int POT_PIN_IN = A0;                  // Analog potentiometer for speed

unsigned int g_speed = 0;
volatile int g_encoderValue = 0;
unsigned int g_currentMillis;
unsigned int g_previousMillis;
const int ENCODER_PPR = 24;
const int INTERVAL = 100;                  

const unsigned long MAX_PULSE_TIMEOUT = 500000; // Max allowed time between pulses (500ms)

// -------- AUXILIARY FUNCTIONS --------
void Plotter() {
  Serial.print(">speed:"); Serial.println(g_speed);
}

// Interrupt service routine to capture speed pulse
void updateEncoder() {
  g_encoderValue++;
}

void readSpeed(){
  if(g_encoderValue==ENCODER_PPR){
    g_currentMillis=millis();
    g_speed = 60*1000/(g_currentMillis - g_previousMillis);
    g_previousMillis=g_currentMillis;
    g_encoderValue=0;
  }
}

// -------- MAIN PROGRAM --------
void setup() {
  Serial.begin(115200);                      // Serial monitor
  pinMode(PWM_PIN_OUT, OUTPUT);              // PWM Output
  pinMode(POT_PIN_IN, INPUT);                // Potentiometer input
  attachInterrupt(digitalPinToInterrupt(HALL_PIN), updateEncoder, RISING);
}

void loop() {
  // Read potentiometer and adjust PWM target
  float pot = analogRead(POT_PIN_IN);                     // Throttle value from potentiometer
  float target = map(pot, 0, 1023, 0, 255);               // Map throttle to PWM value
  analogWrite(PWM_PIN_OUT, target);                       // Output PWM target

  // Check if pulses are too infrequent (motor stopped)
  noInterrupts();
    readSpeed();
    if(g_speed>0){
      Plotter();
    }
  interrupts();
}




