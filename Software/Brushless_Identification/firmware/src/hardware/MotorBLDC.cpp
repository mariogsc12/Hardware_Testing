
#include <hardware/MotorBLDC.hpp>
#include <Arduino.h>
#include <utilities/utilities.hpp>
#include <config/datatypes.h>
#include <config/definitions.h>


MotorBLDC::MotorBLDC(const int PinPwm, const int PinDir, const int PinBrake):
            Pin_Pwm(PinPwm),
            Pin_Dir(PinDir),
            Pin_Brake(PinBrake)
{
}


void MotorBLDC::move(int controlAction)
{
    if(controlAction > 5)
    {
        digitalWrite(Pin_Brake,0);
        digitalWrite(Pin_Dir,COUNTERCLOCKWISE);
        analogWrite(Pin_Pwm,abs(saturate(controlAction,0,PWM_MAX,PWM_MAX)));
    }
    else if(controlAction < -5)
    {
        digitalWrite(Pin_Brake,0);
        digitalWrite(Pin_Dir,CLOCKWISE);
        analogWrite(Pin_Pwm,abs(saturate(controlAction,PWM_MIN,0,PWM_MIN)));
    }
    else 
    {
        digitalWrite(Pin_Dir,0);
        digitalWrite(Pin_Brake,1);
        analogWrite(Pin_Pwm,0);
    }
}

void MotorBLDC::initialize()
{
    pinMode(Pin_Pwm, OUTPUT);   
    pinMode(Pin_Dir, OUTPUT);  
    pinMode(Pin_Brake,OUTPUT);
}
