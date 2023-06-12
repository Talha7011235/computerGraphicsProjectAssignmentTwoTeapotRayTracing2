// Computer Graphics Project Assignment 2 Ray Tracing 2
// Ray2.h
#ifndef RAY_H
#define RAY_H

#include "Color2.h"
#include "Intersectable2.h"
#include "Light2.h"
#include "Project2Vector3.h"
#include "NffParser2.h"
#include "Intersection2.h"
#include <vector>

class Ray {
public:
    Ray ();
    Ray (const Ray&);
    Ray (Vector3, Vector3, NffParser*, const int&, const int&, const float&);

    Color Cast() const;

private:
    Color castSingle(const Vector3&, const Vector3&) const;
    Intersection mainCast(const Vector3&, const Vector3&) const;
    Color lightCast(const Intersection&) const;

    int bounces;
    int samples;
    float aperature;
    Vector3 origin;
    Vector3 direction;
    NffParser *scene;
};

#endif
