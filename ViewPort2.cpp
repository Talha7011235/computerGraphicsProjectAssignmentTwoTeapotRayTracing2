// Computer Graphics Project Assignment 2 Ray Tracing 2
// ViewPort2.cpp

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include "ViewPort2.h"
#include <cmath>

ViewPort::ViewPort() : from(0, 0, 0), at(0, 0, 1), up(0, 1, 0), angle(45), hither(0.1f), resolution(512, 512) {
	depthField = (at - from).magnitude();
}

Vector3 ViewPort::getFrom() const
{
	return from;
}

Vector3 ViewPort::getAt() const
{
	return at;
}

Vector3 ViewPort::getUp() const
{
	return up;
}

float ViewPort::getAspectRatio() const
{
	return aspectRatio;
}

float ViewPort::getAngle() const
{
	return angle;
}

float ViewPort::getAngleScaled() const {
	return angleScale;
}

float ViewPort::getHither() const
{
	return hither;
}

float ViewPort::getDepthField() const {
	return depthField;
}

float ViewPort::inverseWidth() const {
	return invWidth;
}

float ViewPort::inverseHeight() const {
	return invHeight;
}

int ViewPort::getResolutionSize() const {
	return resolutionSize;
}

IntegersForVector2 ViewPort::getResolution() const
{
	return resolution;
}

std::istream& operator>> (std::istream& in, ViewPort& value)
{
	std::string ignore;
	in >> ignore >> value.from;
	in >> ignore >> value.at;
	in >> ignore >> value.up;
	in >> ignore >> value.angle;
	in >> ignore >> value.hither;
	in >> ignore >> value.resolution;
	value.depthField = (value.at - value.from).magnitude();

	float radians = (value.angle * 0.5) * M_PI / 180;
	value.angleScale = tan(radians);

	value.invWidth = 1.f / value.resolution.getX();
	value.invHeight = 1.f / value.resolution.getY();
	value.resolutionSize = value.resolution.getX() * value.resolution.getY();
	value.aspectRatio = value.resolution.getX() / value.resolution.getY();
	return in;
}
