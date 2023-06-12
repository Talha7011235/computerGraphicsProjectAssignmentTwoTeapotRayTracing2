// Computer Graphics Project Assignment 1 Ray Tracing
// Matrix2.cpp
#include "Matrix2.h"

Matrix::Matrix()
{
	// The Identity matrix is the following Matrix:
	// [
	//   1 0 0 0
	//   0 1 0 0
	//   0 0 1 0
	//   0 0 0 1
	// ]
	std::fill(data.begin(), data.end(), 0);
	data[0] = 1;
	data[5] = 1;
	data[10] = 1;
	data[15] = 1;
}

void Matrix::LookAt(const Vector3& from, const Vector3& at, const Vector3& up)
{
	// Do a LookAt Matrix Determination that is a Matrix that transforms something to look at a point in space as described according to the
	// website https://www.medium.com/@carmencincotti/lets-look-at-magic-lookat-matrices-c77e53ebdf78.
	Vector3 forward = Vector3::normalize(from - at);
	Vector3 right = Vector3::normalize(Vector3::cross(up, forward));
	Vector3 newUp = Vector3::cross(forward, right);

	data[0] = right.getX();
	data[1] = right.getY();
	data[2] = right.getZ();
	data[3] = 0;
	data[4] = newUp.getX();
	data[5] = newUp.getY();
	data[6] = newUp.getZ();
	data[7] = 0;
	data[8] = forward.getX();
	data[9] = forward.getY();
	data[10] = forward.getZ();
	data[11] = 0;
	data[12] = from.getX();
	data[13] = from.getY();
	data[14] = from.getZ();
	data[15] = 1;
}

Vector3 Matrix::TransformPoint(const Vector3& source) const
{
	// Transform a point with rotation and translation.
	float x = source.getX() * data[0] + source.getY() * data[4] + source.getZ() * data[8] + data[12];
	float y = source.getX() * data[1] + source.getY() * data[5] + source.getZ() * data[9] + data[13];
	float z = source.getX() * data[2] + source.getY() * data[6] + source.getZ() * data[10] + data[14];
	float w = source.getX() * data[3] + source.getY() * data[7] + source.getZ() * data[11] + data[15];

	return { x / w, y / w, z / w };
}

Vector3 Matrix::TransformDirection(const Vector3& source) const
{
	// Transform a direction with rotation. Transform a direction with no translation.
	float x = source.getX() * data[0] + source.getY() * data[4] + source.getZ() * data[8];
	float y = source.getX() * data[1] + source.getY() * data[5] + source.getZ() * data[9];
	float z = source.getX() * data[2] + source.getY() * data[6] + source.getZ() * data[10];

	return { x, y, z };
}

