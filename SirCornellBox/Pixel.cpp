#include "Pixel.h"

Pixel::Pixel(){}

Pixel::Pixel(ColorDbl _color, Ray * _ray){
	color = _color;
	ray = _ray;
}

Pixel::~Pixel(){}

ColorDbl Pixel::getColor() {
	return color;
}
