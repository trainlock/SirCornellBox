#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "ColorDbl.h"
enum reflectionType {
	LAMBERTIAN,
	GLASS, 
	METAL
};

class Material{
public:
	Material();
	Material(ColorDbl _color, float _p, float _refIdx);

	~Material();

	ColorDbl getColor();
	float getBRDF();
	float getRefraction();

	// TODO: Add lambertian reflection
	// TODO: Set material properties after reflection type

private:
	ColorDbl color;
	float refractionIndex;
	float p; // 0 < p < 1
};

