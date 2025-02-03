#include <Arduino.h>
#include <Encoder.hpp>
#include <digitalWriteFast.h>
#include <Metro.h>

Metro sampleTime(50);

Encoder encoder(23,22,2500);


void encoderCount_1() {
  encoder.count1();
}
void encoderCount_2() {
  encoder.count2();
}

void setup() {
  Serial.begin(115200);
  pinMode(23,INPUT);
  pinMode(22,INPUT);

  attachInterrupt(digitalPinToInterrupt(23), encoderCount_1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(22), encoderCount_2, CHANGE);
}

void loop() {
  if(sampleTime.check()==1)
  {
    Serial.print(encoder.getPulses());Serial.print(" - ");Serial.println(encoder.getPulses()*360/(10000));
  }
}

