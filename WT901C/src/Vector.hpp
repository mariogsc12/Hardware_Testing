
#ifndef _VECTOR_HPP
#define _VECTOR_HPP

template <typename T> class Vector3D
{
    private:
        T x,y,z;
    public:
    Vector3D();
    Vector3D(T x_, T y_, T z_);
    void set(T x_, T y_, T z_);
    T getX();
    T getY();
    T getZ();
    Vector3D<T> operator+(const Vector3D& in);
    Vector3D<T> operator-(const Vector3D& in);

};

template <typename T> 
Vector3D<T>::Vector3D():
            x(0),
            y(0),
            z(0)
{
}

template <typename T> 
Vector3D<T>::Vector3D(T x_, T y_, T z_):
            x(x_),
            y(y_),
            z(z_)
{
}

template <typename T> 
void Vector3D<T>::set(T x_, T y_, T z_)
{
    this->x=x_;
    this->y=y_;
    this->z=z_;
}

template <typename T> 
T Vector3D<T>::getX()
{
    return x;
}

template <typename T> 
T Vector3D<T>::getY()
{
    return y;
}

template <typename T> 
T Vector3D<T>::getZ()
{
    return z;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator+(const Vector3D& in){
    return Vector3D<T>(x + in.x, y + in.y, z + in.z);
}

template <typename T>
Vector3D<T> Vector3D<T>::operator-(const Vector3D& in){
    return Vector3D<T>(x - in.x, y - in.y, z - in.z);
}

#endif