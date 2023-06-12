// Computer Graphics Project Assignment 2 Ray Tracing 2
// Polygon2.h
#ifndef POLYGON_H
#define POLYGON_H

#include "Intersectable2.h"
#include "Project2Vector3.h"
#include "Shading2.h"
#include <vector>

// The Structure Data Type "struct Polygon" represents the implementation of a n point Polygon, tesellated into triangles using a custome method.
struct Polygon : public Intersectable
{
public:
    Polygon();
    ~Polygon();

    int getCount() const;
    std::vector<Vector3>getVerticies() const;
    virtual Shading getShading() const;
    virtual Vector3 getCenter() const;
    virtual Vector3 getGetHitNormal(const Vector3&, const Vector3&) const;
    void setShading(Shading);

    friend std::istream& operator>> (std::istream&, Polygon&);

    virtual bool Intersect(const Vector3&, const Vector3&, float&, float, Vector3&) const;

private:
    bool IntersectTriangle(const int, const int, const int, Vector3, Vector3, float&, Vector3&) const;
    int count;
    float squareRadius;
    std::vector<Vector3> verticies;
    std::vector<int> indicies;
    Vector3 center;
    Shading shading;
};

#endif
