#include "ColorDbl.h"

ColorDbl::ColorDbl(){
	this->r = 0, this->g = 0, this->b = 0;
}

ColorDbl::ColorDbl(double _r, double _g, double _b) {
	this->r = _r, this->g = _g, this->b = _b;
}

ColorDbl::ColorDbl(double _d) {
	this->r = _d, this->g = _d, this->b = _d;
}

ColorDbl::~ColorDbl(){}

void ColorDbl::setColor(ColorDbl _color){
	this->r = _color.r;
	this->g = _color.g;
	this->b = _color.b;
}

void ColorDbl::setColor(double _r, double _g, double _b){
	this->r = _r, this->g = _g, this->b = _b;
}

ColorDbl ColorDbl::getColor(){
	return ColorDbl(this->r, this->g, this->b);
}

ColorDbl ColorDbl::operator=(const double f) {
	this->r = f, this->g = f, this->b = f;
	return *this;
}

ColorDbl ColorDbl::operator=(const float f) {
	this->r = f, this->g = f, this->b = f;
	return *this;
}

ColorDbl ColorDbl::operator*(const float f) {
	this->r *= f, this->g *= f, this->b *= f;
	return *this;
}

ColorDbl ColorDbl::operator*(const ColorDbl c){
	this->r *= c.r, this->g *= c.g, this->b *= c.b;
	return *this;
}

ColorDbl ColorDbl::operator*=(const ColorDbl c) {
	this->r *= c.r, this->g *= c.g, this->b *= c.b;
	return *this;
}

ColorDbl ColorDbl::operator+=(const float f) {
	this->r += f, this->g += f, this->b += f;
	return *this;
}

ColorDbl ColorDbl::operator+(const ColorDbl c) {
	this->r + c.r, this->g + c.g, this->b + c.b;
	return *this;
}

ColorDbl ColorDbl::operator+=(const ColorDbl c) {
	this->r += c.r, this->g += c.g, this->b += c.b;
	return *this;
}

ColorDbl ColorDbl::operator/(const float f) {
	this->r /= f, this->g /= f, this->b /= f;
	return *this;
}

ColorDbl ColorDbl::operator/=(const float f){
	this->r /= f, this->g /= f, this->b /= f;
	return *this;
}

std::ostream& operator<<(std::ostream& os, const ColorDbl& c) {
	os << "(" << c.r << ", " << c.g << ", " << c.b << ")";
	return os;
}