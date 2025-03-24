
#include <hardware/MotorBLDC.hpp>
#include <Arduino.h>
#include <utilities/utilities.hpp>
#include <config/datatypes.h>
#include <config/definitions.h>

MotorBLDC::MotorBLDC(const int PinPwm, const int PinDir,const int PinEncA,const int PinEncB):
            Pin_Pwm(PinPwm),
            Pin_Dir(PinDir),
            encoder(PinEncA,PinEncB)
{
}

MotorBLDC::MotorBLDC(const int PinPwm, const int PinDir):
            Pin_Pwm(PinPwm),
            Pin_Dir(PinDir),
            encoder(0,0)
{
}

void MotorBLDC::move(int controlAction)
{
    if(controlAction > 0)
    {
        digitalWrite(Pin_Dir,COUNTERCLOCKWISE);
        analogWrite(Pin_Pwm,saturate(controlAction,0,PWM_MAX,PWM_MAX));
    }
    else if(controlAction < 0)
    {
        digitalWrite(Pin_Dir,CLOCKWISE);
        analogWrite(Pin_Pwm,abs(saturate(controlAction,PWM_MIN,0,PWM_MIN)));
    }
    else 
    {
        digitalWrite(Pin_Dir,0);
        analogWrite(Pin_Pwm,0);
    }
}

void MotorBLDC::initialize()
{
    encoder.initialize();
    pinMode(Pin_Pwm, OUTPUT);   
    pinMode(Pin_Dir, OUTPUT);            
}

void MotorBLDC::update()
{
    MotorBLDC::position = encoder.getPulses()*360 / (PPR*4);
    // UPDATE VELOCITY 
}

float MotorBLDC::getPosition()
{
    return MotorBLDC::position;
}

float MotorBLDC::getVelocity()
{
    MotorBLDC::velocity;
}

