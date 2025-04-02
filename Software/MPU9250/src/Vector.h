#pragma once

#include <xyzFloat.h>

template <typename T> class Vector3D{
public:
    T x, y, z;

    Vector3D();
    Vector3D(T in_x, T in_y, T in_z);
    Vector3D(xyzFloat const & xyz);
    void set(T in_x, T in_y, T in_z);
    Vector3D<T> operator+ (const Vector3D& rhs);
    Vector3D<T> operator- (const Vector3D& rhs);
    void print(HardwareSerial* serial);
    void println(HardwareSerial* serial);
};

template <typename T>
Vector3D<T>::Vector3D(xyzFloat const & xyz) {
    this->x = static_cast<T>(xyz.x);
    this->y = static_cast<T>(xyz.y);
    this->z = static_cast<T>(xyz.z);
}

template <typename T>
Vector3D<T>::Vector3D(){
    set(0,0,0);
}

template <typename T>
Vector3D<T>::Vector3D(T in_x, T in_y, T in_z){
    set(in_x, in_y, in_z);
}

template <typename T>
void Vector3D<T>::set(T in_x, T in_y, T in_z){
    this->x = in_x;
    this->y = in_y;
    this->z = in_z;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator+(const Vector3D& rhs){
    return Vector3D<T>(x + rhs.x, y + rhs.y, z + rhs.z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator-(const Vector3D& rhs){
    return Vector3D<T>(x - rhs.x, y - rhs.y, z - rhs.z);
}

template <typename T>
void Vector3D<T>::print(HardwareSerial* serial){
    printf("[");
    printf(this->x); printf(',');
    printf(this->y); printf(',');
    printf(this->z); printf(']');
}

template <typename T>
void Vector3D<T>::println(HardwareSerial* serial){
    //print(serial);
    serial->println();
}

template <typename T>
T distSq(const Vector3D<T> v1, const Vector3D<T> v2){
    Vector3D<T> aux;
    aux = v1 - v2;
    T dist = (aux.x) * (aux.x) + (aux.y) * (aux.y) + (aux.z) * (aux.z);
    return (dist);
}
