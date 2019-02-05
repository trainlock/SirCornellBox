#pragma once

#include <vector>
#include <iostream>
#include "Triangle.h"
#include "Light.h"
#include "Tetrahedron.h"
#include "Sphere.h"
#include "../SirCornellBox/glm/gtx/perpendicular.hpp"

struct TriangleIntersection {
	Triangle triangle;
	glm::vec3 point;
	float t;
};

struct SphereIntersection {
	Sphere sphere;
	glm::vec3 surfacePt;
	float distToRay;
	bool isHit = false;
};

class Scene{
public:
	Scene();
	~Scene();

	std::vector<Light> getLights();

	TriangleIntersection detectTriangle(Ray *ray);
	SphereIntersection Scene::detectSphere(Ray *ray);

	void ConvertToLocal(Ray *ray, glm::vec3 intersectionPt, glm::vec3 normal);
	void ConvertToWorld(Ray *ray, glm::vec3 intersectionPt);

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

