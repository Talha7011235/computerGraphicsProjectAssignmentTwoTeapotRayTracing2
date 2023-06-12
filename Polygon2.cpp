// Computer Graphics Project Assignment 2 Ray Tracing 2
// Polygon2.cpp
#define _USE_MATH_DEFINES

#include "Polygon2.h"
#include <iostream>
#include <limits>
#include <cmath>

Polygon::Polygon() : count(0), verticies(0), indicies(), shading(), center() {}

Polygon::~Polygon()
{
	indicies.clear();
	verticies.clear();
}

int Polygon::getCount() const
{
	return count;
}

std::vector<Vector3> Polygon::getVerticies() const
{
	return verticies;
}

Shading Polygon::getShading() const
{
	return shading;
}

Vector3 Polygon::getCenter() const
{
	return center;
}

void Polygon::setShading(Shading sIsForShading)
{
	shading = sIsForShading;
}

std::istream& operator>> (std::istream& in, Polygon& value)
{
	in >> value.count;

	value.verticies.reserve(value.count);

	Vector3 vertex;
	for(int iIndex = 0; iIndex < value.count; ++iIndex)
	{
		in >> vertex;
		value.verticies.push_back(vertex);
		value.center += vertex;
	}
	value.center = value.center / value.count;

	value.squareRadius = 0;
	for(int iIndex = 0; iIndex < value.count; ++iIndex)
	{
		Vector3 distanceVector = value.verticies[iIndex] - value.center;
		float distance = distanceVector.squareLength();
		if(distance > value.squareRadius) {
			value.squareRadius = distance;
		}
	}

	// Triangulate the verticies.
	if (value.verticies.size() == 3)
	{
		// If it is the case of working with a Triangle, then there is no need to triangulate.
		value.indicies.push_back(0);
		value.indicies.push_back(1);
		value.indicies.push_back(2);
	}
	else
	{
		// Otherwise, there are more than three verticies.
		std::vector<float> angles;

		// Determine the initial angles.
		int a = value.count - 1;
		for (int iIndex = 0; iIndex < value.count; ++iIndex)
		{
			Vector3 AC = Vector3::normalize(value.verticies[a] - value.verticies[iIndex]);
			Vector3 AB = Vector3::normalize(value.verticies[(iIndex + 1) % value.count] - value.verticies[iIndex]);
			angles.push_back(AC.getAngle(AB));
			a = iIndex;
		}

		// Do Triangulation based off of the angles. In order to triangulate effectively, select the smallest angle.
		for (int iIndex = 0; iIndex < value.count - 2; ++iIndex)
		{
			// Find the smallest angle.
			int smallest = 0;
			float smallestAngle = angles[0];
			for(int jIndex = 0; jIndex < value.count; ++jIndex)
			{
				if (angles[jIndex] < angles[smallest])
				{
					smallest = jIndex;
					smallestAngle = angles[jIndex];
				}
			}

			// Determine the verticies based on the initial triangle.
			int vertexOne = smallest; // 0

			// Create connected verticies to ensure the avoidance of using any vertex that has already been removed from the angle set.
			int vertexTwo = (smallest + 1) % value.count; // 1
			while (angles[vertexTwo] == std::numeric_limits<float>::max())
			{
				vertexTwo = (vertexTwo + 1) % value.count;
			}

			int vertexThree = (smallest + value.count - 1) % value.count; // 5
			while (angles[vertexThree] == std::numeric_limits<float>::max())
			{
				vertexThree = (vertexThree + value.count - 1) % value.count;
			}

			// Add Triangle to indicies.
			value.indicies.push_back(vertexOne);
			value.indicies.push_back(vertexTwo);
			value.indicies.push_back(vertexThree);

			// Update angle at Vertex 2 that is represented by the Integer Variable "int vertexTwo".
			Vector3 vertexTwoa = Vector3::normalize(value.verticies[vertexThree] - value.verticies[vertexTwo]);
			Vector3 vertexTwob = Vector3::normalize(value.verticies[(vertexTwo + 1) % value.count] - value.verticies[vertexTwo]);
			angles[vertexTwo] = vertexTwoa.getAngle(vertexTwob);

			// Update angle at Vertex 3 that is represented by the Interger Variable "int vertexThree".
			Vector3 vertexThreea = Vector3::normalize(value.verticies[(vertexThree + value.count - 1) % value.count] - value.verticies[vertexThree]);
			Vector3 vertexThreeb = Vector3::normalize(value.verticies[vertexTwo] - value.verticies[vertexThree]);
			angles[vertexThree] = vertexThreea.getAngle(vertexThreeb);

			// Set the current angle to max() so that it will not be selected again.
			angles[smallest] = std::numeric_limits<float>::max();
		}
	}

	return in;
}

bool Polygon::Intersect(const Vector3& origin, const Vector3& direction, float& tValueIsTheDepth,float near, Vector3& uv) const
{
	// Check if the center of the polygon is a certain amount further than the closest determined point for an early exit.
	Vector3 line = center - origin;
	if (line.squareLength() - squareRadius > (near * near * 1.1f))
	{
		return false;
	}

	// Loop through triangles and determine if it's been struck.
	for(int iIndex = 0; iIndex < indicies.size(); iIndex += 3)
	{
		float innerDepth = std::numeric_limits<float>::max();
		if (IntersectTriangle(indicies[iIndex], indicies[iIndex + 1], indicies[iIndex + 2], origin, direction, innerDepth, uv))
		{
			// Update the t-value depth that is represented by the Floating Point Reference Variable "float& tValueIsTheDepth" because it has been struck.
			tValueIsTheDepth = innerDepth;
			return true;
		}
	}
	return false;
}

bool Polygon::IntersectTriangle(const int vZero, const int vOne, const int vTwo, Vector3 origin, Vector3 direction, float& tValue, Vector3& uv) const
{
	// Create a planar vector check.
	Vector3 alpha = verticies[vOne] - verticies[vZero];
	Vector3 beta = verticies[vTwo] - verticies[vZero];
	Vector3 planarNormal = Vector3::cross(direction, beta);
	float determinant = Vector3::dot(alpha, planarNormal);

	// If the Determinant is close to 0, then the Ray and Triangle are parallel.
	if (fabs(determinant) < std::numeric_limits<float>::epsilon())
	{
		return false;
	}

	float inverseDeterminant = 1 / determinant;

	// Check if the initial vertex is behind the camera.
	Vector3 originVector = origin - verticies[vZero];
	float originAngle = Vector3::dot(originVector, planarNormal) * inverseDeterminant;
	if (originAngle < 0 || originAngle > 1)
	{
		return false;
	}

	// Check if Planar Contact Point is within the Triangle.
	Vector3 originNormal = Vector3::cross(originVector, alpha);
	float directionAngle = Vector3::dot(direction, originNormal) * inverseDeterminant;
	if (directionAngle < 0 || directionAngle + originAngle > 1)
	{
		return false;
	}

	uv = {originAngle, directionAngle, 0};
	// Update the t-value, that is "tValue", at which the strike happened.
	tValue = Vector3::dot(beta, originNormal) * inverseDeterminant;

	return true;
}

Vector3 Polygon::getGetHitNormal(const Vector3& hitPoint, const Vector3& uv) const {
	Vector3 Ac = verticies[2] - verticies[0];
	Vector3 Bc = verticies[1] - verticies[0];
	return Vector3::normalize(Vector3::cross(Bc, Ac));
}
