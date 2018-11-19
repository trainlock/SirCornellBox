#pragma once

#include <vector>
#include "Triangle.h"

class Tetrahedron{
public:
	Tetrahedron();
	Tetrahedron(glm::vec3 _pos, ColorDbl _color);
	~Tetrahedron();

	void createTetra(glm::vec3 _pos, ColorDbl _color);

	std::vector<Triangle> getTriangles();

	bool rayIntersection(Ray *ray);
private:
	std::vector<Triangle> triangles;
};

