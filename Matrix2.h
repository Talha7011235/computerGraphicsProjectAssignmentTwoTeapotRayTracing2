// Computer Graphics Project Assignment 2 Ray Tracing 2
// Matrix2.h
#ifndef MATRIX_H
#define MATRIX_H

#include "Project2Vector3.h"
#include <array>

struct Matrix
{
public:
    Matrix();

    void LookAt(const Vector3&, const Vector3&, const Vector3&);
    Vector3 TransformPoint(const Vector3&) const;
    Vector3 TransformDirection(const Vector3&) const;

private:
    std::array<float, 16> data;
};

#endif
