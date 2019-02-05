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
	float EPSILON = 0.00001;

	// Calculate b
	b = glm::dot((2.0f * rayDir), (rayPos - this->centerPos));

	// Calculate c
	c = glm::dot((rayPos - this->centerPos), (rayPos - this->centerPos)) - pow(this->radius, 2);

	//std::cout << "pow((b / 2.0f), 2) - c = " << pow((b / 2.0f), 2) - c << std::endl;
	// TODO: use dp or dm????
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


		/*if (glm::distance(pos1, rayPos) < glm::distance(pos2, rayPos)) {
			surfacePt->x = pos1.x;
			surfacePt->y = pos1.y;
			surfacePt->z = pos1.z;
			return true;
		}
		else {
			surfacePt->x = pos2.x;
			surfacePt->y = pos2.y;
			surfacePt->z = pos2.z;
			return true;
		}*/

		//if (d > 0.0f) {
		//	// Calculate surface point
		//	glm::vec3 pos = (rayPos + d * rayDir);
		//	surfacePt->x = pos.x;
		//	surfacePt->y = pos.y;
		//	surfacePt->z = pos.z;
		//	return true;
		//}
	}
	// No hit
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
