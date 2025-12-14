#pragma once
#include <array>

class ButterworthFilter {
private:
    float filtered_value;
    std::array<float, 3> x; 
    std::array<float, 3> y; 

    std::array<float, 3> b;
    std::array<float, 2> a;

public:
    ButterworthFilter();
    ButterworthFilter(const std::array<float, 3>& _b, const std::array<float, 2>& _a);
    void configure(const std::array<float, 3>& _b, const std::array<float, 2>& _a);

    float update(float value);
    float get_filtered_value();
};

ButterworthFilter::ButterworthFilter() {}

ButterworthFilter::ButterworthFilter(const std::array<float, 3>& _b, const std::array<float, 2>& _a):
    filtered_value(0),
    x{0, 0, 0},
    y{0, 0, 0},
    b(_b), 
    a(_a)   
    {}

void ButterworthFilter::configure(const std::array<float, 3>& _b, const std::array<float, 2>& _a) {
    b = _b;
    a = _a;
}

float ButterworthFilter::update(float value) {
    // Desplazar muestras de entrada
    x[2] = x[1];
    x[1] = x[0];
    x[0] = value;

    // Desplazar salidas anteriores
    y[2] = y[1];
    y[1] = y[0];

    // Filtro Butterworth
    y[0] = b[0] * x[0] + b[1] * x[1] + b[2] * x[2] + a[0] * y[1] + a[1] * y[2];

    filtered_value = y[0];
    return filtered_value;
}

float ButterworthFilter::get_filtered_value() {
    return filtered_value;
}

