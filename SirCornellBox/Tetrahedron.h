#pragma once

#include <vector>
#include "Triangle.h"
#include "Material.h"

class Tetrahedron{
public:
	Tetrahedron();
	Tetrahedron(glm::vec3 _pos, Material _mat);
	~Tetrahedron();

	void createTetra(glm::vec3 _pos, Material _mat);

	std::vector<Triangle> getTriangles();

	bool rayIntersection(Ray *ray);
private:
	std::vector<Triangle> triangles;
};

