
#ifndef MOTORBLDC_H
#define MOTORBLDC_H

#include <hardware/Encoder.hpp>

class MotorBLDC
{
    private:
        const int Pin_Pwm;
        const int Pin_Dir;
        const int Pin_Brake;
        float position;
        float velocity;
        
    public:
        MotorBLDC(int pwmPin, int dirPin, int brakePin);
        void move(int controlAction);
        void initialize();
};



#endif 

