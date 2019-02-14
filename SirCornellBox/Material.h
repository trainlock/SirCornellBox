#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "ColorDbl.h"

enum reflectionType {
	LAMBERTIAN,
	GLASS, 
	METAL, 
	LIGHT
};

class Material{
public:
	Material();
	Material(ColorDbl _color, float _p, float _refIdx, reflectionType _type);
	Material(ColorDbl _color, float _p, float _refIdx, reflectionType _type, float _emission);

	~Material();

	ColorDbl getColor();
	float getBRDF();
	float getRefraction();
	reflectionType getType();


	// TODO: Add lambertian reflection
	// TODO: Set material properties after reflection type

private:
	ColorDbl color;
	reflectionType type;
	float emission;
	float refractionIndex;
	float p; // 0 < p < 1
};

