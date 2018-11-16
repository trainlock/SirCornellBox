#pragma once
#define GLM_ENABLE_EXPERIMENTAL

#include <string>
#include <ostream>
#include <array>
#include "ColorDbl.h"
#include "Ray.h"
#include "../SirCornellBox/glm/glm.hpp"
#include "../SirCornellBox/glm/ext.hpp"
#include "../SirCornellBox/glm/gtx/string_cast.hpp"

class Triangle{
public:
	Triangle();
	Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, ColorDbl _color, std::string _name);
	~Triangle();

	friend std::ostream& operator<<(std::ostream& os, const Triangle& t);
	Triangle operator=(Triangle *t);

	ColorDbl getColor();
	std::string getName();
	std::array<glm::vec3, 3> getVertices();

	glm::vec3 calculateNormal();
	bool rayIntersection(Ray *ray, glm::vec3 *_v);
private:
	glm::vec3 v0, v1, v2;
	glm::vec3 normal;
	ColorDbl color;
	std::string name;
};

