// Computer Graphics Project Assignment 2 Ray Tracing 2
// Polygon2.h
#ifndef POLYGONPATCH_H
#define POLYGONPATCH_H

#include "Intersectable2.h"
#include "Project2Vector3.h"
#include "Shading2.h"
#include "NffParser2.h"
#include <vector>

struct PolygonPatch : public Intersectable
{
public:
    PolygonPatch(const NffParser*);
    ~PolygonPatch();

    int getCount() const;
    std::vector<Vector3>getVerticies() const;
    std::vector<Vector3>getNormals() const;
    virtual Shading getShading() const;
    virtual Vector3 getCenter() const;
    virtual Vector3 getGetHitNormal(const Vector3&, const Vector3&) const;
    void setShading(Shading);

    friend std::istream& operator>> (std::istream&, PolygonPatch&);

    virtual bool Intersect(const Vector3&, const Vector3&, float&, float, Vector3&) const;

private:
    bool IntersectTriangle(const int, const int, const int, Vector3, Vector3, float&, Vector3&) const;
    int count;
    const NffParser* settings;
    float squareRadius;
    std::vector<Vector3> verticies;
    std::vector<Vector3> normals;
    std::vector<int> indicies;
    Vector3 center;
    Shading shading;
};

#endif
