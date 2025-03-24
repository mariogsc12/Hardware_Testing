
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
        Encoder encoder;
    public:
        MotorBLDC(const int PinPwm, const int PinDir,const int PinEncA,const int PinEncB);
        MotorBLDC(const int PinPwm, const int PinDir);
        void move(int controlAction);
        void initialize();
        void update();
        float getPosition();
        float getVelocity();
};



#endif 

