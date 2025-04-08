
#ifndef MOTORBLDC_H
#define MOTORBLDC_H

#include <hardware/Encoder.hpp>

class MotorBLDC
{
    private:
        const int Pin_Pwm;
        const int Pin_Dir;
        const int Pin_Stop;
        float position;
        float velocity;
        
    public:
        MotorBLDC(int pwmPin, int dirPin, int stopPin);
        void move(int controlAction);
        void initialize();
};



#endif 

