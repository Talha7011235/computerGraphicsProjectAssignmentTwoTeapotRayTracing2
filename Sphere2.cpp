// Computer Graphics Project Assignment 2 Ray Tracing 2
// Sphere2.cpp
#include "Sphere2.h"
#include <cmath>

Sphere::Sphere() : center(), radius(1), shading() {}

Vector3 Sphere::getCenter() const
{
	return center;
}

float Sphere::getRadius() const
{
	return radius;
}

Shading Sphere::getShading() const
{
	return shading;
}

void Sphere::setShading(Shading sIsForShading)
{
	shading = sIsForShading;
}

std::istream& operator>> (std::istream& in, Sphere& value)
{
	in >> value.center >> value.radius;
	return in;
}

bool Sphere::Intersect(const Vector3& origin, const Vector3& direction, float& tValueIsDepth, float near, Vector3& uv) const
{
	// Determine the Vector that is representing the distance from the origin and the center of the sphere.
	Vector3 line = center - origin;

	// Exit if too far past the "near" value.
	float squareRadius = (radius * radius);
	if (line.squareLength() - squareRadius > (near * near * 1.1f))
	{
		return false;
	}

	// Check if the center point, line, and direction are within boundaries.
	float lineDot = Vector3::dot(line, direction);
	if (lineDot < 0)
	{
		return false;
	}

	// Check if the Ray Tracer has struck the Sphere.
	float squareDistance = line.squareLength() - lineDot * lineDot;
	if (squareDistance > squareRadius)
	{
		return false;
	}

	// Determine the First Intersection and the Second Intersection of the Sphere based on the Hit Record Distance.
	float hitRecordToCenter = sqrt(squareRadius - squareDistance);
	float firstIntersection = lineDot - hitRecordToCenter;
	float secondIntersection = lineDot - hitRecordToCenter;

	// Set the First Intersection that is represented by the Floating Point Variable "float firstIntersection" to the closer of the two values.
	if (firstIntersection > secondIntersection)
	{
		std::swap(firstIntersection, secondIntersection);
	}

	// If the value is behind the Camera, then check the Further Value.
	if (firstIntersection < 0)
	{
		firstIntersection = secondIntersection;

		// If the Sphere is behind, then return false.
		if (firstIntersection < 0)
		{
			return false;
		}
	}

	uv = {0, 0, 0};
	// Update the t-value, in other words the Depth Value, that is represented by the Floating Point Reference Variable "float& tValueIsDepth" and return true.
	tValueIsDepth = firstIntersection;

	return true;
}

Vector3 Sphere::getGetHitNormal(const Vector3& point, const Vector3& uv) const {
	return Vector3::normalize(point - center);
}
