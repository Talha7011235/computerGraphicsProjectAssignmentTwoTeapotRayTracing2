// Computer Graphics Project Assignment 2 Ray Tracing 2
// NffParser2.cpp
#include "NffParser2.h"
#include "Polygon2.h"
#include "PolygonPatch2.h"
#include "Sphere2.h"
#include <fstream>

NffParser::NffParser()
	: backgroundColor(), isPhong(false),aperature(0), objects(), lights()
{}

// In order to prevent a memory leak, ensure that the created elements inside the objects vector get deleted.
NffParser::~NffParser()
{
	for(std::vector<Intersectable*>::iterator iter = objects.begin(); iter != objects.end(); ++iter)
	{
		delete(*iter);
	}
	objects.clear();

	for(std::vector<Light*>::iterator iter = lights.begin(); iter != lights.end(); ++iter)
	{
		delete(*iter);
	}
	lights.clear();
}

bool NffParser::isPhongRendering() const {
	return isPhong;
}
float NffParser::getAperatureSize() const {
	return aperature;
}
int NffParser::getSampleSize() const {
	return samples;
}
void NffParser::setPhongShading(const bool& value) {
	isPhong = value;
}
void NffParser::setAperatureSize(const float& value) {
	aperature = value;
}
void NffParser::setSampleSize(const int& value) {
	samples = value;
}

Color& NffParser::getBackgroundColor()
{
	return backgroundColor;
}

ViewPort& NffParser::getViewPort()
{
	return viewPort;
}

std::vector<Intersectable*>& NffParser::getObjects()
{
	return objects;
}
std::vector<Light*>& NffParser::getLights()
{
	return lights;
}

void NffParser::parse(const std::string& fileName)
{
	std::ifstream file(fileName);
	if(!file.good())
	{
		throw std:: runtime_error("Error: Unable to open Neutral File Format NFF file, that is .nff File, for reading.");
	}

	Shading current = { {0,0,0}, 0,0,0,0,0};

	// Do a while() Loop to loop through the lines until reaching the end.
	while(!file.eof())
	{
		// Reset the Character Data Type Variable "char element" to 0 so that an input is not repeated.
		char element = 0;
		file >> element;
		switch (element)
		{
		// Fill the background color with the specified values.
		case 'b':
		    file >> backgroundColor;
		    break;

		// Viewpoint.
		case 'v':
		    file >> viewPort;
		    break;

		// Fill Shading.
		case 'f':
		    file >> current;
		    break;

		// Polygon.
		case 'p':
		{
			if(file.peek() == 'p') {
				// Polygon Patch.
				file >> element;

				PolygonPatch *patch = new PolygonPatch(this);
				file >> *patch;
				patch->setShading(current);
				objects.push_back(patch);
				break;
			}

		    Polygon *p = new Polygon();
		    file >> *p;
		    p->setShading(current);
		    objects.push_back(p);
		    break;
		}

		// Sphere.
		case 's':
		{
		    Sphere *s = new Sphere();
		    file >> *s;
		    s->setShading(current);
		    objects.push_back(s);
			break;
		}

		// Light.
		case 'l':
		{
			Light* light = new Light();
			file >> *light;
			lights.push_back(light);
			break;
		}
		// Skip the current line when the current line cannot recognize an element to parse.
		default:
		    file.ignore(255, '\n');
		    break;
		}
	}

	file.close();
}


