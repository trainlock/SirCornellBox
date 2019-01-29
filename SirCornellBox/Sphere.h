#pragma once

#include "../SirCornellBox/glm/glm.hpp"
#include "../SirCornellBox/glm/ext.hpp"
#include "ColorDbl.h"
class Sphere{
public:
	Sphere();
	Sphere(glm::vec3 _centerPos, float _radius, ColorDbl _color);
	~Sphere();

	bool calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir, glm::vec3 *surfacePt);
	ColorDbl getColor();
	glm::vec3 getCenterPt();
	float getRadius();

private:
	glm::vec3 centerPos;
	float radius;
	ColorDbl color;
};

