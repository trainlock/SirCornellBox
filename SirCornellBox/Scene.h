#pragma once

#include <vector>
#include <iostream>
#include "Triangle.h"
#include "Light.h"
#include "Tetrahedron.h"
#include "Sphere.h"

struct TriangleIntersection {
	Triangle triangle;
	glm::vec3 point;
	float t;
};

struct SphereIntersection {
	Sphere sphere;
	glm::vec3 surfacePt;
	float distToRay;
};

class Scene{
public:
	Scene();
	~Scene();

	std::vector<Light> getLights();

	TriangleIntersection detectTriangle(Ray *ray);
	SphereIntersection Scene::detectSphere(Ray *ray);

	std::vector<Triangle> triangles;
	std::vector<Sphere> spheres;
private:
	std::vector<Triangle> roomTriangles;
	std::vector<glm::vec3> vertices;
	std::vector<Light> lights;
	void initLights();
	void initVertices();
	void initTriangles();
	void initObjects();
};

