#include "Arduino.h"
#include "Encoder.hpp"

Encoder::Encoder(const int pinA, const int pinB,const int PPR_, const float sampleTime):
    Pin_A(pinA),
    Pin_B(pinB),
    pulses(0),
    PPR(PPR_),
    sample_time(sampleTime),
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
  speed = ((pulses * 60.0)/(PPR*(sample_time/1000))); // RPM
  // speed = speed * (2*pi/60); // rad/s

  x[2] = x[1];
  x[1] = x[0];
  x[0] = speed;

  y[2] = y[1];
  y[1] = y[0];

  y[0] = b[0]*x[0] + b[1]*x[1] + b[2]*x[2] + a[0]*y[1] + a[1]*y[2];

  filtered_speed = y[0];
  lastTime = millis();
  pulses = 0;
}

float Encoder::getSpeed()
{
  return speed;
}

float Encoder::getFilteredSpeed()
{
  return filtered_speed;
}