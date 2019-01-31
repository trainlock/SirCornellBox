#include "Sphere.h"
#include <algorithm>

Sphere::Sphere(){}

Sphere::Sphere(glm::vec3 _centerPos, float _radius, ColorDbl _color) {
	this->centerPos = _centerPos;
	this->radius = _radius;
	this->color = _color;
}

Sphere::~Sphere(){}

bool Sphere::calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir, glm::vec3 *surfacePt){
	float b, c, d;

	// Calculate b
	b = glm::dot((2.0f * rayDir), (rayPos - this->centerPos));

	// Calculate c
	c = glm::dot((rayPos - this->centerPos), (rayPos - this->centerPos)) - pow(this->radius, 2);

	//std::cout << "pow((b / 2.0f), 2) - c = " << pow((b / 2.0f), 2) - c << std::endl;
	// TODO: use dp or dm????
	// Check if ray hits the sphere
	if (pow((b / 2.0f), 2) - c > 0.0f) {
		// Calculate d 
		d = std::min(-(b / 2.0f) - sqrt(pow((b / 2.0f), 2) - c), -(b / 2.0f) + sqrt(pow((b / 2.0f), 2) - c));
		
		// Calculate surface point
		glm::vec3 pos = (rayPos + d * rayDir);
		surfacePt->x = pos.x;
		surfacePt->y = pos.y;
		surfacePt->z = pos.z;
		//std::cout << "TRUE" << std::endl;

		return true;
	}
	else {
		// No hit
		return false;
	}
	return false;
}

ColorDbl Sphere::getColor()
{
	return this->color;
}

glm::vec3 Sphere::getCenterPt(){
	return centerPos;
}

float Sphere::getRadius(){
	return radius;
}
