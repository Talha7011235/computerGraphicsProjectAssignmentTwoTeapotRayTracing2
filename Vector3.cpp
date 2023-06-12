// Computer Graphics Project Assignment 2 Ray Tracing 2
// Vector3.cpp
#include "Vector3.h"
#include <cmath>
#include <algorithm>

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
Vector3::~Vector3() {}

float Vector3::getGlobalHorizontalXAxis() const
{
	return x;
}

float Vector3::getGlobalVerticalYAxis() const
{
	return y;
}

float Vector3::getGlobalDepthZAxis() const
{
	return z;
}

Vector3 Vector3::operator+(const Vector3 &right) const
{
	return {x + right.getGlobalHorizontalXAxis(), y + right.getGlobalVerticalYAxis(), z + right.getGlobalDepthZAxis()};
}

Vector3 Vector3::operator-(const Vector3 &right) const
{
	return {x - right.getGlobalHorizontalXAxis(), y - right.getGlobalVerticalYAxis(), z - right.getGlobalDepthZAxis()};
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
	return left.getGlobalHorizontalXAxis() * right.getGlobalHorizontalXAxis() + left.getGlobalVerticalYAxis() * right.getGlobalVerticalYAxis() + left.getGlobalDepthZAxis() * right.getGlobalDepthZAxis();
}

Vector3 Vector3::cross(const Vector3 &left, const Vector3 &right)
{
	// Determine the Cross Produce using a method described at https://cs.wellesley.edu/~cs307/readings/08-geometry.html.
	float x = left.getGlobalVerticalYAxis() * right.getGlobalDepthZAxis() - left.getGlobalDepthZAxis() * right.getGlobalVerticalYAxis();
	float y = left.getGlobalDepthZAxis() * right.getGlobalHorizontalXAxis() - left.getGlobalHorizontalXAxis() * right.getGlobalDepthZAxis();
	float z = left.getGlobalHorizontalXAxis() * right.getGlobalVerticalYAxis() - left.getGlobalVerticalYAxis() * right.getGlobalHorizontalXAxis();

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
	// Create a unit vector of length 1 by dividing each element by the length of the Vector.
	float magnitude = value.magnitude();
	return value / magnitude;
}

Vector3 Vector3::invert(const Vector3 &value)
{
	return {-value.x, -value.y, -value.z};
}

Vector3 Vector3::reflect(const Vector3 &normal) const
{
	// The First Parameter in the Dot Product Function "dot()" that is "*this" represents the Angle of Incidence. The Second Parameter in the Dot Product
	// Function "dot()" that is "normal" represents the Perpendicular Surface Vector to reflect around.
	return *this - 2.f * Vector3::dot(*this, normal) * normal;
}

Vector3 Vector3::refract(const Vector3 &normal, const float &indexOfRefraction) const
{
	// The First Parameter in the Dot Product Function "dot()" that is "*this" represents the Angle of Incidence. The Second Parameter in the Dot Product
	// Function "dot()" that is "normal" represents the Perpendicular Surface Vector to reflect around.
	float clampI = std::clamp(Vector3::dot(*this, normal), -1.f, 1.f);
	float refractiveValueThatIsClose = 1;
	float refractiveValueThatIsFar = indexOfRefraction;
	Vector3 norm = normal;
	if (clampI < 0)
	{
		clampI = -clampI;
	}
	else
	{
		std::swap(refractiveValueThatIsClose, refractiveValueThatIsFar);
		norm = Vector3::invert(norm);
	}

	float iorRatio = refractiveValueThatIsClose / refractiveValueThatIsFar;
	float angleOfIncidence = 1 - iorRatio * iorRatio * (1 - clampI * clampI);

	// Total Reflection.
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

// Use the Equality Operator that is the Is Equal To Operator "==" to check if x, y, and z are the same between this vector and the 'right' vector.
bool Vector3::operator==(const Vector3 &right) const
{
	return x == right.x && y == right.y && z == right.z;
}

// Use the Inequality Operator that is the Is Not Equal To Operator "!=" to check if the Equality Operator returned False.
bool Vector3::operator!=(const Vector3 &right) const
{
	return !(*this == right);
}
