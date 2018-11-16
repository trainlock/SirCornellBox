#pragma once
#include "ColorDbl.h"
#include "Ray.h"
#include "Triangle.h"
#include "../SirCornellBox/glm/glm.hpp"

class Light {
public:
	Light();
	Light(glm::vec3 _pos, float _intensity);
	~Light();

	ColorDbl getEmission();
	float getIntensity();
	glm::vec3 getPos();

	bool lightIntersection(Ray *ray, glm::vec3 *_p, std::vector<Triangle> _triangles);

private:
	glm::vec3 pos;
	float intensity; // Intensity is infinate, interpolate between [0, 255]
};

