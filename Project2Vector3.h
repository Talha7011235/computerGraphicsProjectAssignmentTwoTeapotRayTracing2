// Talha Hussain
// Computer Graphics Project Assignment 2 Ray Tracing 2
// Project2Vector3.h
#ifndef VECTOR3_H
#define VECTOR3_H

#include<iostream>

struct Vector3
{
public:
    Vector3();
    Vector3(float, float, float);
    virtual ~Vector3();

    // Crete a Vector Component to represent the Global Horizontal X Axis.
    float getX() const;

    // Create a Vector Component to represent the Global Vertical Y Axis.
    float getY() const;

    // Create a Vector Component to represent the Global Depth Z Axis.
    float getZ() const;

    Vector3 operator +(const Vector3&) const;
    Vector3 operator -(const Vector3&) const;
    Vector3 operator *(const float&) const;
    friend Vector3 operator *(const float&, const Vector3&);
    Vector3 operator /(const float&) const;

    Vector3& operator +=(const Vector3&);
    bool operator ==(const Vector3&) const;
    bool operator !=(const Vector3&) const;

    static Vector3 cross(const Vector3&, const Vector3&);
    static float dot(const Vector3&, const Vector3&);

    float squareLength() const;
    float magnitude() const;
    float getAngle(const Vector3&) const;
    Vector3 reflect(const Vector3&) const;
    Vector3 refract(const Vector3&, const float&) const;
    float Fresnel(const Vector3&, const float&) const;

    static Vector3 normalize(const Vector3&);
    static Vector3 invert(const Vector3&);

    friend std::istream& operator >> (std::istream&, Vector3&);
    friend std::ostream& operator << (std::ostream&, const Vector3&);

private:
    float x;
    float y;
    float z;
};

#endif
