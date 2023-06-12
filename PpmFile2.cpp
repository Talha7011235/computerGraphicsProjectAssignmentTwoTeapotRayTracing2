// Computer Graphics Project Assignment 2 Ray Tracing 2
// PpmFile2.cpp
#include "PpmFile2.h"
#include <fstream>
#include <vector>

void PpmFile::write(const std::string fileName, IntegersForVector2 resolution, const std::vector<Color> pixels)
{
	std::ofstream output(fileName, std::ofstream::out | std::ofstream::binary);
	if (!output.good())
	{
		throw std::runtime_error("Error: Not able to create/open Image File for saving.");
	}

	// Follow the Portable Pixel Map PPM Version 6 P6 header to indicate that the version is binary instead of the American Standard Code for Information
	// Interchange ASCII version.
	output << "P6" << std::endl;
	output << resolution.getX() << " " << resolution.getY() << std::endl;
	output << "255" << std::endl;

	// Loop through the Pixels and Output.
	for (std::vector<Color>::const_iterator iter = pixels.begin(); iter != pixels.end(); ++iter)
	{
		output << *iter;
	}

	output.close();
}

