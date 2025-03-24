#include "Arduino.h"
#include "Encoder.hpp"

Encoder::Encoder(const int pinA, const int pinB,const int PPR_):
    Pin_A(pinA),
    Pin_B(pinB),
    pulses(0),
    PPR(PPR_),
    lastTime(0)
{
}

void Encoder::initialize()
{
  pinMode(Pin_A, INPUT);
  pinMode(Pin_B, INPUT);
}

long Encoder::getPulses()
{
	return Encoder::pulses;
}

void Encoder::setPulses(long pulses_)
{
	Encoder::pulses = pulses_;
}

void Encoder::count1()
{
  Encoder::pulses += ((digitalRead(Pin_A)<<1) - 1) * ((digitalRead(Pin_B)<<1) - 1); 
}

void Encoder::count2()
{
  Encoder::pulses -= ((digitalRead(Pin_A)<<1) - 1) * ((digitalRead(Pin_B)<<1) - 1); 
}

void Encoder::update()
{
  currentTime = millis();
  speed = (pulses / PPR)*(60.0/(currentTime-lastTime));
  lastTime = millis();
  pulses = 0;
}

float Encoder::getSpeed()
{
  return speed;
}
