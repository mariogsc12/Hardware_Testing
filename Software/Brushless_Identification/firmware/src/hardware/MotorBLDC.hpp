
#ifndef MOTORBLDC_H
#define MOTORBLDC_H

#include <hardware/Encoder.hpp>

class MotorBLDC
{
    private:
        const int Pin_Pwm;
        const int Pin_Dir;
        const int Pin_Brake;
        const int Pin_Stop;
        float position;
        float velocity;
        
    public:
        MotorBLDC(const int PinPwm, const int PinDir, const int PinBrake, const int PinStop);
        void move(int controlAction);
        void initialize();
};



#endif 

