// Computer Graphics Project Assignment 2 Ray Tracing 2
// Light2.h
#include "Light2.h"

Light::Light() : position() {}
Light:: Light(const Vector3& p) : position(p) {}

Vector3 Light::getPosition() const {
    return position;
}

std::istream& operator>> (std::istream& in, Light& value)
{
	in >> value.position;
	return in;
}

std::ostream& operator << (std::ostream& out, const Light& value) {
	out << "Light at: " << value.position;
	return out;
}
