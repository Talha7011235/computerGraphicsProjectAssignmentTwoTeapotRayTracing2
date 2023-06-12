// Computer Graphics Project Assignment 2 Ray Tracing 2
// main2.cpp
#define _USE_MATH_DEFINES

#include "NffParser2.h"
#include "PpmFile2.h"
#include "Project2IntegersForVector2.h"
#include "Matrix2.h"
#include "Ray2.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <thread>
#include <mutex>

// Convert a Degree to a Radian.
inline float convertDegreeToRadian(const float& dDegree)
{
	return dDegree * M_PI / 180;
}

NffParser settings;
std::vector<Color> pixels;
int counter = 0;
std::mutex countMutex;

void PerformRayCast(int y) {
    float yDirection = (1 - 2 * (y + 0.5) * settings.getViewPort().inverseHeight()) * settings.getViewPort().getAngleScaled();
	Matrix world;
	world.LookAt(settings.getViewPort().getFrom(), settings.getViewPort().getAt(), settings.getViewPort().getUp());

    for (int x = 0; x < settings.getViewPort().getResolution().getX(); ++x)
    {
        {
            std::lock_guard<std::mutex> guard(countMutex);
            std::cout << "Tracing: " << (++counter * 100.f / settings.getViewPort().getResolutionSize()) << "%           " << std::endl << "\x1b[A";
        }
        // Create a Ray to send.
        float xDirection = (2 * (x + 0.5) * settings.getViewPort().inverseWidth() - 1) * settings.getViewPort().getAngleScaled() * settings.getViewPort().getAspectRatio();
        Vector3 direction = Vector3::normalize(world.TransformDirection({ xDirection, yDirection, -1 }));

        Ray ray(settings.getViewPort().getFrom(), direction, &settings, 5, settings.getSampleSize(), settings.getAperatureSize());
        pixels[y * settings.getViewPort().getResolution().getX() + x] = ray.Cast();
    }
}

// Pass the C++ Command Line Arguments argc and argv to the main() Function.
int main (int argc, char** argv)
{
	if (argc < 2)
	{
		std::cout << "Ray Tracer" << std::endl;
		std::cout << "Usage: " << argv[0] << " [-p] [-a <float>] [-b <float>] [-j <int>] filename [output]" << std::endl;
		return 1;
	}
    // Reset the random.
    srand(time(nullptr));

	// Command Line Argument Parser.
	bool phong = false;
	int samples = 1;
	float aperature = 0;
	float counter = 0;

	int state = 0;
	std::string filename("");
	std::string output("output.ppm");

	for(int i = 1; i < argc; ++i) {

		// Check if Phong Shading is requested.
		if(strcmp(argv[i], "-p") == 0) {
			phong = true;
			continue;
		}

		// Check if jitter is desired.
		if(strcmp(argv[i], "-s") == 0) {
			samples = atoi(argv[++i]);
			continue;
		}

		// Check for Depth of Field Aperature.
		if(strcmp(argv[i], "-a") == 0) {
			aperature = atof(argv[++i]);
			continue;
		}

		if(state == 0) {
			filename = argv[i];
			++state;
			continue;
		}
		if(state == 1) {
			output = argv[i];
			++state;
			continue;
		}
	}

	std::cout << "Settings" << std::endl;
	if(phong) {
		std::cout << "Phong";
	} else {
		std::cout << "Flat";
	}
	std::cout << " shading selected" << std::endl;
	if(samples > 1) {
		std::cout << "Stratified Sampling selected with a " << samples << "*" << samples << " jitter grid" << std::endl;
	}
	if(aperature > 0) {
		std::cout << "Depth of Field selected with an aperature of " << aperature << std::endl;
	}

	// Parse the .nff File and prepare the scene.
	settings.parse(filename);
	settings.setAperatureSize(aperature);
	settings.setPhongShading(phong);
	settings.setSampleSize(samples);

	std::cout << "Loaded " << filename << std::endl;

	// Get the values from the .nff File.
	ViewPort view = settings.getViewPort();

	// Get the Resolution and set up the Calculations.
	IntegersForVector2 resolution = view.getResolution();

	// Change the vector to be the Pixel Count Size.
	pixels.resize(view.getResolutionSize());
	// Set the Pixel Vector to the Default Color.
	std::fill(pixels.begin(), pixels.end(), settings.getBackgroundColor());

    std::vector<std::thread> threads;
    threads.reserve(resolution.getY());
	// Create a for() loop to loop through pixel locations.
	for (int y = 0; y < resolution.getY(); ++y)
	{
        threads.push_back(std::thread(PerformRayCast, y));
	}

    for(std::vector<std::thread>::iterator iter = threads.begin(); iter != threads.end(); ++iter) {
        iter->join();
    }

	// Write the final image to the Portable Pix Map PPM File that is the .ppm File.
	PpmFile::write(output, resolution, pixels);

	return 0;
}
