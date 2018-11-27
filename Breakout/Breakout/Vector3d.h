//
//  Vector3d.h
//  Breakout
//
//  Created by Iram Diaz Reyes on 11/25/18.
//  Copyright © 2018 Iram Diaz Reyes. All rights reserved.
//

#ifndef Vector3d_h
#define Vector3d_h


#include <iostream>
#include <cmath>
#include <cassert>


using namespace std;
template <class T> class Vector3D;

typedef Vector3D<double> Vector3Dd;
typedef Vector3D<float> Vector3Df;
typedef Vector3D<int> Vector3Di;

template <class T>
class Vector3D{
    
public:
    
    Vector3D():Vector3D(0,0,0){}
    Vector3D(T x,T y,T z):x(x),y(y),z(z){}
    Vector3D<T> *clone() { return new Vector3D<T>(*this); }
    Vector3D(const Vector3D<T> &v);
    inline T getX();
    inline T getY();
    inline T getZ();
    inline void setX(T x);
    inline void setY(T y);
    inline void setZ(T z);
    
    inline Vector3D<T> sum(Vector3D<T> v2);
    inline Vector3D<T> operator/(T v);
    inline Vector3D<T> operator*(T v);
    inline Vector3D<T> operator+(Vector3D<T> v2);
    inline Vector3D<T> operator-(Vector3D<T> b);
    inline bool operator==(Vector3D<T> b);
    friend ostream& operator<<(ostream &os, const Vector3D<T>& v);
    
    inline T operator*(const Vector3D<T> &v2);
    inline Vector3D<T> crossProduct(const Vector3D<T> &v2);
    inline T lengthSquared(){ return x*x + y*y + z*z;}
    inline T length(){ return sqrt(lengthSquared());}
    inline bool equalsZero(T a){return fabs(a)<0.00001;}
    inline void normalize();
    
private:
    T x;
    T y;
    T z;
};

template <class T>
Vector3D<T>::Vector3D(const Vector3D<T> &v){
    this->x = v.x;
    this->y= v.y;
    this->x = v.z;
}

template <class T>
T Vector3D<T>:: getX(){
    return x;
}

template <class T>
T Vector3D<T>::getY(){
    return y;
}
template <class T>
T Vector3D<T>::getZ(){
    return z;
}

template <class T>
void Vector3D<T>::setX(T x){
    this->x = x;
}

template <class T>
void Vector3D<T>::setY(T y){
    this->y = y;
}

template <class T>
void Vector3D<T>::setZ(T z){
    this->z = z;
}

template <class T>
Vector3D<T> Vector3D<T>::sum(Vector3D<T> v2){
    Vector3D<T> vr;
    vr.x = x +v2.x;
    vr.y = y +v2.y;
    vr.z = z +v2.z;
    
    return vr;
}
/*
 se llama como
 Vector3D v, v1,v2;
 v = v1.sum(v2);
 
 
 */

template <class T>
Vector3D<T> Vector3D<T>::operator/(T v){
    Vector3D<T> vr;
    vr.x = x /v;
    vr.y = y /v;
    vr.z = z /v;
    
    return vr;
}

template <class T>
Vector3D<T> Vector3D<T>::operator*( T d){
    Vector3D<T> ret;
    ret.x=x*d;
    ret.y=y*d;
    ret.z=z*d;
    return ret;
}

template <class T>
T Vector3D<T>::operator*(const Vector3D<T> &v2){
    Vector3D<T> &v1=*this;
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <class T>
Vector3D<T> Vector3D<T>::operator+( Vector3D<T> v2){
    Vector3D<T> vr;
    vr.setX(this->getX() +v2.getX());
    vr.setY(this->getY() +v2.getY());
    vr.setZ(this->getZ() +v2.getZ());
    
    return vr;
}

template <class T>
Vector3D<T> Vector3D<T>::operator-(Vector3D<T> b){
    Vector3D<T> ret;
    ret.x=x-b.x;
    ret.y=y-b.y;
    ret.z=z-b.z;
    return ret;
}



template <class T>
Vector3D<T> Vector3D<T>::crossProduct(const Vector3D<T> &v2){
    Vector3D<T> &v1=*this;
    return Vector3D<T>(v1.y*v2.z - v1.z*v2.y,
                       v1.z*v2.x - v1.x*v2.z,
                       v1.x*v2.y - v1.y*v2.x);
}

template <class T>
void Vector3D<T> :: normalize(){
    T magnitude = length();
    assert(!equalsZero(magnitude));
    
    magnitude = 1.0f / magnitude;
    
    x *= magnitude;
    y *= magnitude;
    z *= magnitude;
}

template <class T>
bool Vector3D<T> :: operator==(Vector3D<T> b){
    return x==b.x && y==b.y && z==b.z;
}

ostream& operator<<(ostream &os, const Vector3D<double> &v){
    
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}




#endif /* Vector3d_h */
