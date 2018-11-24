#include "Pixel.h"

Pixel::Pixel(){}

Pixel::Pixel(ColorDbl _color, Ray * _ray){
	color = _color;
	ray = _ray;
}

Pixel::~Pixel(){}


void Pixel::setColor(double r, double g, double b) {
	color = ColorDbl(r, g, b);
}

ColorDbl Pixel::getColor() {
	return color;
}
