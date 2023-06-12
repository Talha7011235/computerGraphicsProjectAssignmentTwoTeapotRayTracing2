// Computer Graphics Project Assignment 2 Ray Tracing 2
// Intersectable2.h
#ifndef INTERSECTABLE_H
#define INTERSECTABLE_H

#include "Project2Vector3.h"
#include "Shading2.h"

// Create an interface class specifically a Structure for Polygons and Spheres to ensure that they are interchangeable for testing purposes.
struct Intersectable
{
public:
    virtual bool Intersect(const Vector3& origin, const Vector3& direction, float& depth, float near, Vector3&) const = 0;
    virtual Shading getShading() const = 0;
    virtual Vector3 getCenter() const = 0;
    virtual Vector3 getGetHitNormal(const Vector3&, const Vector3&) const = 0;  
};

#endif
