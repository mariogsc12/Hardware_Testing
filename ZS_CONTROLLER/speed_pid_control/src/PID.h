// ----- PID CONTROL -----
    // global variables for error  
    float sumError;
    float prevError;
    float error;

    // global variables for time
    float dt;
    float _time;
    float prevTime;

class PID{
  private:
    // parameters
    float kp;
    float ki;
    float kd;

    // constrain
    float maxValue;

  public:
    PID(float _kp,float _ki,float _kd):kp(_kp),ki(_ki),kd(_kd){}
    float computePID(){
      float P,I,D;
      P = kp*error;
      I = ki * sumError;
      D = kd * (error - prevError) / dt;
      prevError = error;
      return constrainPID(P + I + D);
    }
    float constrainPID(float value){
      if (value>maxValue) return maxValue;
      else if(value<-maxValue) return -maxValue;
      else return value;
    }
    void setMaxValue(float _max){
      maxValue = _max;
    }
};

