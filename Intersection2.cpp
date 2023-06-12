// Computer Graphics Project Assignment 2 Ray Tracing 2
// Intersection2.cpp
#include "Intersection2.h"

Intersection::Intersection() :
    hit(false), hitPoint(), hitNormal(), hitUv(), material(), hitDistance(0) {}

Intersection::Intersection(const Vector3& p, const Vector3& n, const Vector3& u, const Shading& m, const float& distance) :
    hit(true), hitPoint(p), hitNormal(n), hitUv(u), material(m), hitDistance(distance) {}

Intersection::~Intersection()
{
}

bool Intersection::isHit() const {
    return hit;
}

float Intersection::getHitDistance() const {
    return hitDistance;
}

Vector3 Intersection::getUv() const {
    return hitUv;
}

Vector3 Intersection::getPoint() const {
    return hitPoint;
}

Vector3 Intersection::getBiasPoint() const {
    return hitPoint + hitNormal * 0.05;
}

Vector3 Intersection::getNormal() const {
    return hitNormal;
}

Shading Intersection::getMaterial() const {
    return material;
}
