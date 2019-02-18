#include "ColorDbl.h"

ColorDbl::ColorDbl()
{
}

ColorDbl::ColorDbl(double _r, double _g, double _b) {
	r = _r, g = _g, b = _b;
}


ColorDbl::~ColorDbl()
{
}

void ColorDbl::setColor(ColorDbl _color){
	r = _color.r;
	g = _color.g;
	b = _color.b;
}

void ColorDbl::setColor(double _r, double _g, double _b){
	r = _r, g = _g, b = _b;
}

ColorDbl ColorDbl::getColor(){
	return ColorDbl(r, g, b);
}

ColorDbl ColorDbl::operator*(const float f) {
	this->r *= f;
	this->g *= f;
	this->b *= f;
	return *this;
}

ColorDbl ColorDbl::operator*(const ColorDbl c){
	return ColorDbl(r*c.r, g*c.g, b*c.b);
}

ColorDbl ColorDbl::operator+(const ColorDbl c) {
	return ColorDbl(r+c.r, g+c.g, b+c.b);
}

ColorDbl ColorDbl::operator+=(const ColorDbl c) {
	return ColorDbl(r + c.r, g + c.g, b + c.b);
}

ColorDbl ColorDbl::operator/=(const float f)
{
	this->r /= f;
	this->g /= f;
	this->b /= f;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ColorDbl& c) {
	os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
	return os;
}