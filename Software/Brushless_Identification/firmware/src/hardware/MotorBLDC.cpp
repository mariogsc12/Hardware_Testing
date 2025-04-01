
#include <hardware/MotorBLDC.hpp>
#include <Arduino.h>
#include <utilities/utilities.hpp>
#include <config/datatypes.h>
#include <config/definitions.h>


MotorBLDC::MotorBLDC(const int PinPwm, const int PinDir, const int PinBrake, const int PinStop):
            Pin_Pwm(PinPwm),
            Pin_Dir(PinDir),
            Pin_Brake(PinBrake),
            Pin_Stop(PinStop)
{
}


void MotorBLDC::move(int controlAction)
{
    if(controlAction > 0)
    {
        //digitalWrite(Pin_Stop, HIGH);
        //digitalWrite(Pin_Brake, LOW);
        digitalWrite(Pin_Dir,COUNTERCLOCKWISE);
        analogWrite(Pin_Pwm,abs(saturate(controlAction-10,0,PWM_MAX,PWM_MAX)));
    }
    else if(controlAction < 0)
    {
        //digitalWrite(Pin_Stop, HIGH);
        //digitalWrite(Pin_Brake, LOW);
        digitalWrite(Pin_Dir,CLOCKWISE);
        analogWrite(Pin_Pwm,abs(saturate(controlAction,PWM_MIN,0,PWM_MIN)));
    }
    else 
    {
        digitalWrite(Pin_Stop, LOW);
        digitalWrite(Pin_Brake, HIGH); 
        digitalWrite(Pin_Dir,0);
        analogWrite(Pin_Pwm,0);
    }
}

void MotorBLDC::initialize()
{
    pinMode(Pin_Pwm, OUTPUT);   
    pinMode(Pin_Dir, OUTPUT);  
    pinMode(Pin_Brake, OUTPUT);  
    pinMode(Pin_Stop, OUTPUT);   
    digitalWrite(Pin_Brake, LOW);  
    digitalWrite(Pin_Stop, HIGH);  
    //digitalWrite(Pin_Enable, HIGH);
}
