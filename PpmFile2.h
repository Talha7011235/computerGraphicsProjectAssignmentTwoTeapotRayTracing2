// Computer Graphics Project Assignment 2 Ray Tracing 2
// PpmFile2.h
#ifndef PPMFILE_H
#define PPMFILE_H

#include "Project2IntegersForVector2.h"
#include "Color2.h"
#include <string>
#include <vector>

class PpmFile
{
public:
    static void write(const std::string fileName, IntegersForVector2 resolution, std::vector<Color> pixels);
};

#endif
