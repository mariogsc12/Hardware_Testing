
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
    
/*
        if(controlAction>=-4)controlAction-=45;
        else if(controlAction<-4 && controlAction >= -7)controlAction-=43;
        else if(controlAction<-7 && controlAction >= -12)controlAction-=40;
        else if(controlAction<-12 && controlAction >= -16)controlAction-=38;
        else if(controlAction<-16 && controlAction >= -20)controlAction-=35;
        else if(controlAction<-20 && controlAction >= -24)controlAction-=32;
        else if(controlAction<-24 && controlAction >= -27)controlAction-=30;
        else if(controlAction<-27 && controlAction >= -30)controlAction-=28;
        else if(controlAction<-30 && controlAction >= -33)controlAction-=26;
        else if(controlAction<-33 && controlAction >= -36)controlAction-=24;
        else if(controlAction<-36 && controlAction >= -39)controlAction-=22;
        else if(controlAction<-39 && controlAction >= -42)controlAction-=21;
        else if(controlAction<-42 && controlAction >= -45)controlAction-=20;
        else if(controlAction<-45 && controlAction >= -48)controlAction-=18;
        else if(controlAction<-48 && controlAction >= -51)controlAction-=16;
        else if(controlAction<-51 && controlAction >= -54)controlAction-=14;
        else if(controlAction<-54 && controlAction >= -57)controlAction-=12;
        else if(controlAction<-57 && controlAction >= -60)controlAction-=10;
*/

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
