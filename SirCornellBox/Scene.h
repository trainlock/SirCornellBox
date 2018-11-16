#pragma once
#include <vector>
#include <iostream>
#include "Triangle.h"
#include "Light.h"

struct TriangleIntersection {
	Triangle triangle;
	glm::vec3 point;
	float t;
};

class Scene{
public:
	Scene();
	~Scene();

	TriangleIntersection detectTriangle(Ray *ray);
	std::vector<Light> getLights();

	std::vector<Triangle> triangles;
private:
	std::vector<glm::vec3> vertices;
	std::vector<Light> lights;
	void initLights();
	void initVertices();
	void initTriangles();
};

