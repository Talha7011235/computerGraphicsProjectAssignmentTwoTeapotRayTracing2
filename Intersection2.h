// Computer Graphics Project Assignment 2 Ray Tracing 2
// Intersection2.h
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Shading2.h"
#include "Project2Vector3.h"

// The Intersection2.h Header File holds variables for ease of passing around.
class Intersection
{
public:
    Intersection();
    Intersection(const Vector3&, const Vector3&, const Vector3&, const Shading&, const float&);
    ~Intersection();

    bool isHit() const;
    float getHitDistance() const;
    Vector3 getUv() const;
    Vector3 getPoint() const;
    Vector3 getBiasPoint() const;
    Vector3 getNormal() const;
    Shading getMaterial() const;

private:
    bool hit;
    float hitDistance;
    Vector3 hitUv;
    Vector3 hitPoint;
    Vector3 hitNormal;
    Shading material;
};


#endif
