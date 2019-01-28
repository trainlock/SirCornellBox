#pragma once

#include "../SirCornellBox/glm/glm.hpp"
#include "../SirCornellBox/glm/ext.hpp"
#include "../SirCornellBox/glm/gtx/string_cast.hpp"

class Sphere{
public:
	Sphere();
	Sphere(glm::vec3 _centerPos, float _radius);
	~Sphere();

	glm::vec3 calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir);

	glm::vec3 getCenterPt();
	float getRadius();

private:
	glm::vec3 centerPos;
	float radius;
};

