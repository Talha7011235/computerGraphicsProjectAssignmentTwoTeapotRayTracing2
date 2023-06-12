// Computer Graphics Project Assignment 2 Ray Tracing 2
// ViewPort2.h
#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "Vector3.h"
#include "Project2IntegersForVector2.h"

struct ViewPort
{
public:
    ViewPort();

    Vector3 getFrom() const;
    Vector3 getAt() const;
    Vector3 getUp() const;
    float getAspectRatio() const;
    float getAngle() const;
    float getAngleScaled() const;
    float getHither() const;
    float getDepthField() const;
    float inverseWidth() const;
    float inverseHeight() const;
    int getResolutionSize() const;
    IntegersForVector2 getResolution() const;

    friend std::istream& operator>> (std::istream&, ViewPort&);

private:
    Vector3 from;
    Vector3 at;
    Vector3 up;
    float aspectRatio;
    float angle;
    float angleScale;
    float hither;
    float depthField;
    float invWidth;
    float invHeight;
    int resolutionSize;
    IntegersForVector2 resolution;
};

#endif

