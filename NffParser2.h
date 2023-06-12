// Computer Graphics Project Assignment 2 Ray Tracing 2
// NffParser2.h
#ifndef NFFPARSER_H
#define NFFPARSER_H

#include "Color2.h"
#include "ViewPort2.h"
#include "Intersectable2.h"
#include "Light2.h"
#include <string>
#include <vector>

// Parses the Neutral File Format NFF file and holds some minor settings. If more settings are needed then split into parser and settings classes.
class NffParser
{
public:
    NffParser();
    ~NffParser();

    bool isPhongRendering() const;
    float getAperatureSize() const;
    int getSampleSize() const;
    Color& getBackgroundColor();
    ViewPort& getViewPort();
    std::vector<Intersectable*>& getObjects();
    std::vector<Light*>& getLights();

    void setPhongShading(const bool&);
    void setAperatureSize(const float&);
    void setSampleSize(const int&);

    void parse(const std::string&);

private:
    bool isPhong;
    float aperature;
    int samples;
    Color backgroundColor;
    ViewPort viewPort;
    std::vector<Intersectable*> objects;
    std::vector<Light*> lights;
};

#endif

