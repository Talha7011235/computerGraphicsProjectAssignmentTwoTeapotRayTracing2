// Computer Graphics Project Assignment 2 Ray Tracing 2
// Color2.cpp
#include "Color2.h"
#include <algorithm>
#include <sstream>

Color::Color() : redColor(0), greenColor(0), blueColor(0) {}
Color::Color(float r, float g, float b) : redColor(r), greenColor(g), blueColor(b) {}

float Color::getColorRed() const
{
	return redColor;
}

float Color::getColorGreen() const
{
	return greenColor;
}

float Color::getColorBlue() const
{
	return blueColor;
}

// Retrieve the color as an unsigned byte to facilitate the creation of the Portable Pixmap Format File that is the .ppm File.
unsigned char Color::getRedColorByte() const
{
	return (unsigned char)(std::clamp(redColor, 0.f, 1.f) * 255);
}

unsigned char Color::getGreenColorByte() const
{
	return (unsigned char) (std::clamp(greenColor, 0.f, 1.f) * 255);
}

unsigned char Color::getBlueColorByte() const
{
	return (unsigned char) (std::clamp(blueColor, 0.f, 1.f) * 255);
}

Color Color::operator+(const Color& right) const {
	return { redColor + right.redColor, greenColor + right.greenColor, blueColor + right.blueColor};
}

Color& Color::operator+=(const Color& right) {
	redColor += right.redColor;
	greenColor += right.greenColor;
	blueColor += right.blueColor;
	return *this;
}
Color Color::operator*(const Color& right) const {
	return {
		(redColor + right.redColor) / 2,
		(greenColor + right.greenColor) / 2,
		(blueColor + right.blueColor) / 2
	};
}
Color Color::operator*(const float& right) const {
	return {
		(redColor * right),
		(greenColor * right),
		(blueColor * right)
	};
}
Color& Color::operator*=(const Color& right) {
	redColor += right.redColor;
	greenColor += right.greenColor;
	blueColor += right.blueColor;
	redColor /= 2;
	greenColor /= 2;
	blueColor /= 2;
	return *this;
}

Color Color::operator/(const float value) {
	return { redColor / value, greenColor / value, blueColor / value };
}

// The Neutral File Format NFF, in other words the .nff Files, use an RGB in float format.
std::istream& operator >> (std::istream& in, Color& value)
{
	in >> value.redColor >> value.greenColor >> value.blueColor;
	return in;
}

std::string Color::toString() const {
	std::stringstream stream;
	stream << redColor << ", " << greenColor << ", " << blueColor;
	return stream.str();
}

std::ostream& operator << (std::ostream& out, const Color& value)
{
	// To support the Portable Pixel Map Versin 6 P6 Style of the Portable Pixel Map PPM, specifically the .ppm File, output as bytes instead of as Floating Point
	// American Standard Code for Informatin Interchange ASCII values.
	out << value.getRedColorByte() << value.getGreenColorByte() << value.getBlueColorByte();
	return out;
}

bool Color::operator ==(const Color& right) const {
	return redColor == right.redColor && greenColor == right.greenColor && blueColor == right.blueColor;
}

float lerp(float start, float end, float amount) {
	return start * (1.0 - amount) + (end * amount);
}

Color Color::mix(const Color& base, const Color& mixin, const float& amount) {
	return { lerp(base.redColor, mixin.redColor, amount),lerp(base.greenColor, mixin.greenColor, amount),lerp(base.blueColor, mixin.blueColor, amount) };
}

Color Color::getShade(const float& shadeValue) const {
	float newRed = std::clamp(redColor * shadeValue, 0.f, 1.f);
	float newGreen = std::clamp(greenColor * shadeValue, 0.f, 1.f);
	float newBlue = std::clamp(blueColor * shadeValue, 0.f, 1.f);
	return {newRed, newGreen, newBlue};
}
