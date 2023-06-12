// Computer Graphics Project Assignment 2 Ray Tracing 2
// Sphere2.h
#ifndef SPHERE_H
#define SPHERE_H

#include "Intersectable2.h"
#include "Project2Vector3.h"
#include "Shading2.h"

struct Sphere : public Intersectable
{
public:
    Sphere();

    float getRadius() const;
    virtual Shading getShading() const;
    virtual Vector3 getCenter() const;
    virtual Vector3 getGetHitNormal(const Vector3&, const Vector3&) const; 

    void setShading(Shading);

    friend std::istream& operator>> (std::istream&, Sphere&);

    virtual bool Intersect(const Vector3&, const Vector3&, float&, float, Vector3&) const;

private:
    Vector3 center;
    float radius;
    Shading shading;
};

#endif
