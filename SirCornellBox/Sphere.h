#pragma once

#include "ColorDbl.h"
#include "Material.h"
#include "../SirCornellBox/glm/glm.hpp"
#include "../SirCornellBox/glm/ext.hpp"

class Sphere{
public:
	Sphere();
	Sphere(glm::vec3 _centerPos, float _radius, Material _mat);
	~Sphere();

	bool calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir, glm::vec3 *surfacePt);
	ColorDbl getColor();
	Material getMaterial();
	glm::vec3 getCenterPt();
	float getRadius();

private:
	glm::vec3 centerPos;
	float radius;
	ColorDbl color;
	Material mat;
};

