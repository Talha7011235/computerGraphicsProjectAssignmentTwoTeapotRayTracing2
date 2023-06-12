// Computer Graphics Project Assignment 2 Ray Tracing 2
// Shading2.h
#ifndef SHADING_H
#define SHADING_H

#include "Color2.h"

struct Shading
{
public:
    Shading();
    Shading(Color, float, float, float, float, float);

    Color getColor();
    float getDiffuse();
    float getSpecular();
    float getShine();
    float getTransmittance();
    float getIndexOfRefraction();

    friend std::istream& operator>> (std::istream&, Shading&);

private:
    Color color;
    float diffuse;
    float specular;
    float shine;
    float transmittance;
    float indexOfRefraction;
};

#endif

