#include "Sphere.h"
#include <algorithm>

Sphere::Sphere(){}

Sphere::Sphere(glm::vec3 _centerPos, float _radius, Material _mat) {
	this->centerPos = _centerPos;
	this->radius = _radius;
	this->mat = _mat;
	this->color = mat.getColor();
}

Sphere::~Sphere(){}

bool Sphere::calculateSurfacePt(glm::vec3 rayPos, glm::vec3 rayDir, glm::vec3 *surfacePt){
	float b, c, d;
	float EPSILON = 0.00001;

	// Calculate b
	b = glm::dot((2.0f * rayDir), (rayPos - this->centerPos));

	// Calculate c
	c = glm::dot((rayPos - this->centerPos), (rayPos - this->centerPos)) - pow(this->radius, 2);

	// Check if ray hits the sphere
	if (pow((b / 2.0f), 2) - c > 0.0f) {
		float d1 = -(b / 2.0f) - sqrt(pow((b / 2.0f), 2) - c);
		float d2 = -(b / 2.0f) + sqrt(pow((b / 2.0f), 2) - c);

		// Calculate d  
		d = std::min(d1, d2);

		glm::vec3 pos1 = (rayPos + d1 * rayDir);
		glm::vec3 pos2 = (rayPos + d2 * rayDir);

		if (glm::distance(pos1, rayPos) < EPSILON && d2 > 0.0f) {
			surfacePt->x = pos2.x;
			surfacePt->y = pos2.y;
			surfacePt->z = pos2.z;
			return true;
		}
		else if(d1 > 0.0f){
			surfacePt->x = pos1.x;
			surfacePt->y = pos1.y;
			surfacePt->z = pos1.z;
			return true;
		}
	}
	// No hit
	return false;
}

ColorDbl Sphere::getColor(){
	return mat.getColor();
	//return this->color;
}

Material Sphere::getMaterial() {
	return mat;
}

glm::vec3 Sphere::getCenterPt(){
	return centerPos;
}

float Sphere::getRadius(){
	return radius;
}
