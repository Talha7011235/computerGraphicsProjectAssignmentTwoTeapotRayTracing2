// Computer Graphics Project Assignment 2 Ray Tracing 2
// Shading2.cpp
#include "Shading2.h"

Shading::Shading() : color(), diffuse(0), specular(0), shine(0), transmittance(0), indexOfRefraction(0) {}
Shading::Shading(Color cForColor, float dForDiffuse, float sForSpecular, float shForShine, float tForTransmittance, float iForIndexOfRefraction) : color(cForColor), diffuse(dForDiffuse), specular(sForSpecular), shine(shForShine), transmittance(tForTransmittance), indexOfRefraction(iForIndexOfRefraction) {}

Color Shading::getColor()
{
	return color;
}

float Shading::getDiffuse()
{
	return diffuse;
}

float Shading::getSpecular()
{
	return specular;
}

float Shading::getShine()
{
	return shine;
}

float Shading::getTransmittance()
{
	return transmittance;
}

float Shading::getIndexOfRefraction()
{
	return indexOfRefraction;
}

std::istream& operator>> (std::istream& in, Shading& value)
{
	in >> value.color >> value.diffuse >> value.specular >> value.shine >> value.transmittance >> value.indexOfRefraction;
	return in;
}
