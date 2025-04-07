
#ifndef MOTORBLDC_H
#define MOTORBLDC_H

#include <hardware/Encoder.hpp>

class MotorBLDC
{
    private:
        const int Pin_Pwm;
        const int Pin_Dir;
        float position;
        float velocity;
        
    public:
        MotorBLDC(int pwmPin, int dirPin);
        void move(int controlAction);
        void initialize();
};



#endif 

