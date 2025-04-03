#pragma once
#include <array>  // Necesario para std::array

class FIR_Filter
{
private:
    float filtered_value;
    float x[3];  
    float y[3]; 
    std::array<float,3> b;
    std::array<float,2> a;
public:
    FIR_Filter(const std::array<float,3>& _b, const std::array<float,2>& _a);
    float update(float value);
    float get_filtered_value();
};

FIR_Filter::FIR_Filter(const std::array<float,3>& _b, const std::array<float,2>& _a) :
    filtered_value(0),
    x{0, 0, 0},
    y{0, 0, 0},
    b(_b), 
    a(_a)   
{
}

// This function receives the value of the measurement and returns the filtered value
float FIR_Filter::update(float value)
{
    x[2] = x[1];
    x[1] = x[0];
    x[0] = value;
  
    y[2] = y[1];
    y[1] = y[0];
  
    y[0] = b[0]*x[0] + b[1]*x[1] + b[2]*x[2] + a[0]*y[1] + a[1]*y[2];
  
    filtered_value = y[0];
}

float FIR_Filter::get_filtered_value(){return filtered_value;}
