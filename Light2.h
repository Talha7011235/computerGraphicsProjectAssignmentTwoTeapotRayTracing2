// Computer Graphics Project Assignment 2 Ray Tracing 2
// Light2.h
#ifndef LIGHT_H
#define LIGHT_H

#include "Project2Vector3.h"

class Light {
public:
    Light();
    Light(const Vector3&);

    Vector3 getPosition() const;

    friend std::istream& operator >> (std::istream&, Light&);
    friend std::ostream& operator << (std::ostream&, const Light&);
private:
    Vector3 position;
};

#endif
