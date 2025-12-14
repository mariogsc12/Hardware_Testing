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
