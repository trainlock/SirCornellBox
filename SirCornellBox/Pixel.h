#pragma once

#include "ColorDbl.h"
#include "Ray.h"

class Pixel{
public:
	Pixel();
	Pixel(ColorDbl _color, Ray *_ray);
	~Pixel();

	ColorDbl getColor();

private:
	ColorDbl color;
	Ray *ray;
};

