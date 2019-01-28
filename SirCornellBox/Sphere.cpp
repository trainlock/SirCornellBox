#include "Sphere.h"

Sphere::Sphere(){}

Sphere::Sphere(glm::vec3 _centerPos, float _radius) {
	this->centerPos = _centerPos;
	this->radius = _radius;
}

Sphere::~Sphere(){}

glm::vec3 Sphere::calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir){
	float b, c, dp, dm;
	glm::vec3 surfacePt;

	// Calculate b
	b = glm::dot((2.0f * rayDir), (rayPos - this->centerPos));

	// Calculate c
	c = glm::dot((rayPos - this->centerPos), (rayPos - this->centerPos)) - pow(this->radius, 2);

	// Calculate d 
	// TODO: use dp or dm????
	dp = -(b / 2.0f) + sqrt(pow((b / 2.0f), 2) - c);
	dm = -(b / 2.0f) - sqrt(pow((b / 2.0f), 2) - c);

	// Calculate surface point
	surfacePt = rayPos + dm * rayDir;

	// Return surface point
	return surfacePt;
}

glm::vec3 Sphere::getCenterPt(){
	return centerPos;
}

float Sphere::getRadius(){
	return radius;
}
