// Talha Hussain
// Computer Graphics Project Assignment 2 Ray Tracing 2
// Project2Vector3.cpp
#include "Project2Vector3.h"
#include <algorithm>
#include <cmath>

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
Vector3::~Vector3() {}

float Vector3::getX() const
{
	return x;
}

float Vector3::getY() const
{
	return y;
}

float Vector3::getZ() const
{
	return z;
}

Vector3 Vector3::operator+(const Vector3 &right) const
{
	return {x + right.getX(), y + right.getY(), z + right.getZ()};
}

Vector3 Vector3::operator-(const Vector3 &right) const
{
	return {x - right.getX(), y - right.getY(), z - right.getZ()};
}

Vector3 Vector3::operator*(const float &right) const
{
	return {x * right, y * right, z * right};
}

Vector3 operator*(const float &left, const Vector3 &right)
{
	return right * left;
}

Vector3 Vector3::operator/(const float &right) const
{
	return {x / right, y / right, z / right};
}

Vector3 &Vector3::operator+=(const Vector3 &right)
{
	x += right.x;
	y += right.y;
	z += right.z;
	return *this;
}
float Vector3::dot(const Vector3 &left, const Vector3 &right)
{
	return left.getX() * right.getX() + left.getY() * right.getY() + left.getZ() * right.getZ();
}

Vector3 Vector3::cross(const Vector3 &left, const Vector3 &right)
{
	// Determine the Cross Product using a method described at https://cs.wellesley.edu/~cs307/readings/08-geometry.html.
	float x = left.getY() * right.getZ() - left.getZ() * right.getY();
	float y = left.getZ() * right.getX() - left.getX() * right.getZ();
	float z = left.getX() * right.getY() - left.getY() * right.getX();

	return {x, y, z};
}

std::istream &operator>>(std::istream &in, Vector3 &value)
{
	in >> value.x >> value.y >> value.z;
	return in;
}

std::ostream &operator<<(std::ostream &out, const Vector3 &value)
{
	out << value.x << ", " << value.y << ", " << value.z;
	return out;
}

Vector3 Vector3::normalize(const Vector3 &value)
{
	// Create a Unit Length 1 Vector by dividing each element by the length of the Vector.
	float magnitude = value.magnitude();
	return value / magnitude;
}

Vector3 Vector3::invert(const Vector3 &value)
{
	// Create a Unit Length 1 Vector by dividing each element by the length of the Vector.
	return {-value.x, -value.y, -value.z};
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
	// *this: represents our incident angle
	// normal: represents the perpandicular surface vector to reflect around
	return *this - 2.f * Vector3::dot(*this, normal) * normal;
}

Vector3 Vector3::refract(const Vector3 &normal, const float &indexOfRefraction) const
{
	// *this: represents our incident angle
	// normal: represents the perpandicular surface vector to reflect around
	// based on: https://www.brown.edu/research/labs/mittleman/sites/brown.edu.research.labs.mittleman/files/uploads/lecture13_0.pdf
	float clampI = std::clamp(Vector3::dot(*this, normal), -1.f, 1.f);
	float closeRefractiveValue = 1, farRefractiveValue = indexOfRefraction;
	Vector3 norm = normal;
	if (clampI < 0)
	{
		clampI = -clampI;
	}
	else
	{
		std::swap(closeRefractiveValue, farRefractiveValue);
		norm = Vector3::invert(norm);
	}

	float iorRatio = closeRefractiveValue / farRefractiveValue;
	float angleOfIncidence = 1 - iorRatio * iorRatio * (1 - clampI * clampI);
	// We have total reflection
	if (angleOfIncidence < 0)
	{
		return reflect(normal);
	}
	return iorRatio * (*this) + (iorRatio * clampI - sqrt(angleOfIncidence)) * norm;
}

// Get the angle between two vectors in radians.
float Vector3::getAngle(const Vector3 &b) const
{
	float determinantOfMatrix = Vector3::dot(*this, b);
	return acos(determinantOfMatrix);
}

float Vector3::squareLength() const
{
	return x * x + y * y + z * z;
}

float Vector3::magnitude() const
{
	return sqrt(squareLength());
}

// Equality operator, check if x, y and z are the same between this vector and the 'right' vector
bool Vector3::operator==(const Vector3 &right) const
{
	return x == right.x && y == right.y && z == right.z;
}

// Inequality operator, check if the equality operator returned false
bool Vector3::operator!=(const Vector3 &right) const
{
	return !(*this == right);
}
