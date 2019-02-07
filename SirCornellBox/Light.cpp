#include "Light.h"

Light::Light(){
	// Can add light as a square or circle in the roof or at another place.
}

Light::Light(glm::vec3 _pos, float _intensity){
	pos = _pos;
	intensity = _intensity;

	float heightHalf = 1.0f;
	float widthHalf = 1.0f;

	glm::vec3 v0 = glm::vec3(_pos.x - widthHalf, _pos.y - heightHalf, _pos.z);
	glm::vec3 v1 = glm::vec3(_pos.x + widthHalf, _pos.y - heightHalf, _pos.z);
	glm::vec3 v2 = glm::vec3(_pos.x + widthHalf, _pos.y + heightHalf, _pos.z);
	glm::vec3 v3 = glm::vec3(_pos.x - widthHalf, _pos.y + heightHalf, _pos.z);

	ColorDbl color = ColorDbl(1.0, 1.0, 1.0) * intensity;
	float p = 0.0f;
	float refIdx = 0.0f;
	Material mat = Material(color, p, refIdx);
	lights.push_back(Triangle(v0, v1, v2, mat, "light_t0"));
	lights.push_back(Triangle(v0, v2, v3, mat, "light_t1"));
}

Light::~Light(){}

ColorDbl Light::getEmission(){
	// Assume white light, to begin with
	return ColorDbl(1.0, 1.0, 1.0)*intensity;
}

float Light::getIntensity() {
	return intensity;
}

glm::vec3 Light::getPos(){
	return pos;
}

bool Light::lightIntersection(Ray *ray, glm::vec3 *_p, std::vector<Triangle> _triangles){
	float distance = 100000000.0f;
	bool isFound = false;
	glm::vec3 tmpPt = glm::vec3(0.0f, 0.0f, 0.0f);

	// Check if light intersects with point
	for (auto &triangle : _triangles) {
		// Check if the ray intersects the triangle
		// If so, add the triangle to the returning vector
		if (triangle.rayIntersection(ray, &tmpPt)) {

			// Check which intersection that is the closest
			float distTriangle = glm::distance(ray->getStartPt(), tmpPt);
			if (distTriangle < distance && distTriangle > 0.0f) {
				distance = distTriangle;
				_p->x = tmpPt.x;
				_p->y = tmpPt.y;
				_p->z = tmpPt.z;
				isFound = true;
			}
		}
	}
	return isFound;
}
