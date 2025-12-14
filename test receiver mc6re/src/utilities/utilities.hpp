
#ifndef UTILITIES_HPP
#define UTILITIES_HPP

int saturate(int value, int min, int max, int returnValue)
{
    if(value<min || value>max)return returnValue;
    else return value;
}
#endif