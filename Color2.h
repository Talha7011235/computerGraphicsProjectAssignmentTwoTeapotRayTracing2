// Computer Graphics Project Assignment 2 Ray Tracing 2
// Color2.h
#ifndef COLOR_H
#define COLOR_H

#include<iostream>
#include <string>

struct Color
{
public:
    Color();
    Color(float, float, float);

    Color operator+(const Color&) const;
    Color& operator+=(const Color&);
    Color operator*(const Color&) const;
    Color operator*(const float&) const;
    Color& operator*=(const Color&);
    Color operator/(const float);

    friend std::istream& operator >> (std::istream&, Color&);
    friend std::ostream& operator << (std::ostream&, const Color&);

    bool operator ==(const Color&) const;

    float getColorRed() const;
    float getColorGreen() const;
    float getColorBlue() const;

    unsigned char getRedColorByte() const;
    unsigned char getBlueColorByte() const;
    unsigned char getGreenColorByte() const;

    Color getShade(const float&) const;
    static Color mix(const Color&, const Color&, const float&);
    std::string toString() const;

private:
    float redColor;
    float greenColor;
    float blueColor;
};

#endif
