// Computer Graphics Project Assignment 2 Ray Tracing 2
// IntegersForVector2.cpp
#include "Project2IntegersForVector2.h"

IntegersForVector2::IntegersForVector2() :x(0), y(0) {}
IntegersForVector2::IntegersForVector2(int X, int Y) :x(X), y(Y) {}

std::istream& operator>> (std::istream& in, IntegersForVector2& value)
{
	in >> value.x >> value.y;
	return in;
}

int IntegersForVector2::getX() const
{
	return x;
}

int IntegersForVector2::getY() const
{
	return y;
}
