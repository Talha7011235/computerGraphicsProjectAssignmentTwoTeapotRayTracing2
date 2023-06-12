// Computer Graphics Project Assignment 2 Ray Tracing 2
// Ray2.cpp
#include "Ray2.h"
#include "Project2Vector3.h"
#include "Shading2.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdlib>
#include <ctime>

Ray::Ray() : origin(), direction(0, 0, -1), scene(), bounces(0) {}
Ray::Ray(const Ray &r) : origin(r.origin), direction(r.direction), scene(r.scene), bounces(r.bounces) {}
Ray::Ray(Vector3 o, Vector3 d, NffParser *s, const int& b, const int& sa, const float& a) : origin(o), direction(d), scene(s), bounces(b), samples(sa), aperature(a) {}

Color Ray::Cast() const
{
    // Specify an Aperature implementing the Depth of Field only on the First Bounce that is a concept inspired from the
    // website https://medium.com/@elope139/depth-of-field-in-path-tracing-e61180417027.
    if (aperature > 0)
    {
        // Generate a right vector and and up vector for the forward direction of the ray.
        Vector3 right = Vector3::normalize(Vector3::cross(Vector3(0, 1, 0), direction));
        Vector3 up = Vector3::cross(direction, right);

        Color pixelColor;

        // Determine the step for how much distance is between each jitter ray. Then, loop through the two-dimensional jitter field.
        Vector3 focalPoint = origin + direction * scene->getViewPort().getDepthField();
        float step = (rand() % 10) / 10.f * aperature;
        for (int x = -1; x < 2; x+=2)
        {
            for (int y = -1; y < 2; y+=2)
            {
                // Create an offset ray origin and appropriate focal direction.
                Vector3 depthOfFieldOrigin = origin + (right * x * step) + (up * y * step);
                Vector3 dofDirection = Vector3::normalize(focalPoint - depthOfFieldOrigin);

                // Do the cast at this new origin and direction and add it to the color
                pixelColor += castSingle(depthOfFieldOrigin, dofDirection);
            }
        }

        // Return the Averaged Color Value
        return pixelColor / 4;
    }

    // If the Depth of Field is not done, then only cast a single ray at the direction.
    return castSingle(origin, direction);
}

// The "Color Ray::castSingle(const Vector3 &origin, const Vector3 &direction) const" Function sends a single source ray into the world and
// performs jittering anti-aliasing if the Private Member Integer Variable "int samples" is set higher than 1.
Color Ray::castSingle(const Vector3 &origin, const Vector3 &direction) const
{
    // Generate the up and right vectors in relation to the forward vector in order to jitter the rays.
    Vector3 right = Vector3::normalize(Vector3::cross(Vector3(0, 1, 0), direction));
    Vector3 up = Vector3::cross(direction, right);

    Color finalColor;

    // Generate a jitter pattern. Generating a one-dimensional pattern as the jitter is meant to be a square field. Therefore, both the horizontal and vertical
    // fields use the same pattern.
    // Even: -1 1, -2 -1 1 2
    // Odd: -1 0 1, -2 -1 0 1 2
    int halfJitter = samples / 2;
    
    // Determine the step for how much distance is between each jitter ray. Loop through the two-dimensional jitter field.
    float step = 0.005f / scene->getSampleSize();
    for (int x = -halfJitter; x <= halfJitter; ++x)
    {
        for (int y = -halfJitter; y <= halfJitter; ++y)
        {
            Vector3 jitterDirection = direction + (right * x * step) + (up * y * step);
            // Set Default Color to the Background Color.
            Color pixelColor = scene->getBackgroundColor();

            // Cast the Ray into scene and receive the Intersection Record.
            Intersection hitRecord = mainCast(origin, jitterDirection);

            // If the Ray was a hit, then process the information.
            if (hitRecord.isHit())
            {
                // Perform a Lighting Ray Trace to determine the Color of the Pixel.
                pixelColor = lightCast(hitRecord);

                // Create an if statement for if the surface material is translucent and we still have bounces left.
                if (bounces > 0)
                {
                    Color refractiveColor, reflectiveColor;
                    if (hitRecord.getMaterial().getTransmittance() > 0)
                    {
                        // Generate a Refractive View Angle.
                        Vector3 refraction = direction.refract(hitRecord.getNormal(), hitRecord.getMaterial().getIndexOfRefraction());   

                        // Generate a Bias Point in the direction of the Refractive Angle.
                        Vector3 hitPoint = hitRecord.getPoint() + refraction * 0.0001;

                        // Ray Trace, or in other words cast, the Refractive Ray and add its Color to the system.
                        Ray refract(hitPoint, refraction, scene, bounces - 1, 1, 0);
                        refractiveColor = refract.Cast();
                    }

                    if (hitRecord.getMaterial().getSpecular() > 0)
                    {
                        // Generate a Refraction Vector and a Bias Point for the Refraction.
                        Ray bounce(hitRecord.getBiasPoint(), direction.reflect(hitRecord.getNormal()), scene, bounces - 1, 1, 0);
                        reflectiveColor = bounce.Cast().getShade(hitRecord.getMaterial().getSpecular());
                    }

                    Color mixed = refractiveColor * hitRecord.getMaterial().getTransmittance() + reflectiveColor * (1.f - hitRecord.getMaterial().getTransmittance());
                    pixelColor += mixed;
                }
            }

            finalColor += pixelColor;

            // Ignore the zero value with even grids.
            if (y == 0 && scene->getSampleSize() % 2 == 0)
            {
                y++;
            }
        }

        // Ignore the zero value with even grids.
        if (x == 0 && scene->getSampleSize() % 2 == 0)
        {
            x++;
        }
    }

    return finalColor / (samples * samples);
}

// The Function "Intersection Ray::mainCast(const Vector3 &inOrigin, const Vector3 &inDirection) const" sends a final form of a Ray, after Depth of Field
// and jitter, into the scene to collide with objects.
Intersection Ray::mainCast(const Vector3 &inOrigin, const Vector3 &inDirection) const
{
    // Set up the Ray Tracing, that is the Cast, Temporary Variables.
    float near = std::numeric_limits<float>::max();
    float tValueIsTheDepth;
    // The "iUV" is the intersection UV coordinates based on where the Ray hits the Intersectable Object.
    Vector3 iUv;
    // The Function "isHit()" is False by default.
    Intersection hitRecord;

    // Get the objects from the scene and loop through them.
    std::vector<Intersectable *> objects = scene->getObjects();
    for (std::vector<Intersectable *>::const_iterator iter = objects.begin(); iter != objects.end(); ++iter)
    {
        // Set up the Intersection Variables. Then, do intersection with the object.
        tValueIsTheDepth = std::numeric_limits<float>::max();
        if ((*iter)->Intersect(inOrigin, inDirection, tValueIsTheDepth, near, iUv))
        {
            // If there is a Hit Record, then check the t-value that is represented by the Float Variable "float tValueIsTheDepth" to see if the
            // New Hit Record is closer than the Old Hit Record.
            if (tValueIsTheDepth > 0.0001f && tValueIsTheDepth < near)
            {
                // Update "near" value to the latest depth.
                near = tValueIsTheDepth;

                // Generate a Hit Point and find the normal inside the Intersectable.
                Vector3 hitPoint = inOrigin + inDirection * near;
                Vector3 hitNormal = (*iter)->getGetHitNormal(hitPoint, iUv);

                // Generate a new Hit Record to return. As a result, the isHit() Function is True when generated.
                hitRecord = Intersection(hitPoint, hitNormal, iUv, (*iter)->getShading(), near);
            }
        }
    }

    // Return the Hit Record.
    return hitRecord;
}

// The Function "Color Ray::lightCast(const Intersection &hitRecord)" takes an Intersection object and aggregates the Light Values.
Color Ray::lightCast(const Intersection &hitRecord) const
{
    // Set up the Temporaty Variables for the Ray.
    bool isShaded = false;
    Shading material = hitRecord.getMaterial();
    // Set the Pixel Color to Unlit Value.
    Color pixelColor = material.getColor();

    // Retrieve the objects and lights from the scene
    std::vector<Intersectable *> objects = scene->getObjects();
    std::vector<Light *> lights = scene->getLights();

    // If we have lights continue
    if (lights.size() > 0)
    {
        // Set up the Light Intensity Values.
        float lightIntensity = 1.f / sqrt(lights.size());
	// Set Pixel Color to lit.
        pixelColor = {0, 0, 0};

        // In order to get the Lighting Value, do a for() loop to loop through the lights.
        for (std::vector<Light *>::const_iterator light = lights.begin(); light != lights.end(); ++light)
        {
            // Get the Vector of the Light in order to determine how far the Vector of the Light is and the direction to the Vector of the Light.
            Vector3 lightVec = (*light)->getPosition() - hitRecord.getPoint();
            float mag = lightVec.magnitude();
            Vector3 lightDir = lightVec / mag;

            // Set the "near" to the distance so that any object that is past does not cause Shading.
            float lightNear = mag;
            // Create a for() loop to loop through objects to determine if there is a collision. Although using the mainCast() function can work,
            // however, it is necessary to break early if a hit is detected. It does not matter how close or far the object is in relation to blocking the light.
            for (std::vector<Intersectable *>::const_iterator iter = objects.begin(); iter != objects.end(); ++iter)
            {
                float tValueIsTheDepth = std::numeric_limits<float>::max();
		// The "Vector3 ignored" exists only to be returned by the Intersect() Function.
                Vector3 ignored;
                if ((*iter)->Intersect(hitRecord.getBiasPoint(), lightDir, tValueIsTheDepth, lightNear, ignored))
                {
                    // If there is any intersection, then that means the Shading is complete. Therefore, "break".
                    if (tValueIsTheDepth > 0.0001f && tValueIsTheDepth < lightNear)
                    {
                        isShaded = true;
                        break;
                    }
                }
            }

            // If there is no intersection then calculate the lighting.
            if (!isShaded)
            {
                // Generate the Half Vector.
                Vector3 H = Vector3::normalize(Vector3::invert(direction) + lightDir);
                Color c = material.getColor();

                // Generate Diffuse and Specular based on the Surface Normal and the Light Angle.
                float diffuse = std::max(0.f, Vector3::dot(hitRecord.getNormal(), lightDir));
                float specular = pow(std::max(0.f, Vector3::dot(hitRecord.getNormal(), H)), material.getShine());

                // Calculate the Pixel Color with the lights. If the light is not shadowed, the Diffuse and Specular contribution from that one light
		// would be computed as the following:
                pixelColor = {
                    pixelColor.getColorRed() + ((material.getDiffuse() * c.getColorRed() * diffuse + material.getSpecular() * specular) * lightIntensity),
                    pixelColor.getColorGreen() + ((material.getDiffuse() * c.getColorGreen() * diffuse + material.getSpecular() * specular) * lightIntensity),
                    pixelColor.getColorBlue() + ((material.getDiffuse() * c.getColorBlue() * diffuse + material.getSpecular() * specular) * lightIntensity)};
            }
        }

        if (pixelColor == Color())
        {
            pixelColor = material.getColor() * 0.05f;
        }
    }

    // Return the color of the Intersection.
    return pixelColor;
}
