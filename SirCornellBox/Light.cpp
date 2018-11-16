#include "Light.h"

Light::Light(){}

Light::Light(glm::vec3 _pos, float _intensity){
	pos = _pos;
	intensity = _intensity;
}

Light::~Light(){}

ColorDbl Light::getEmission(){
	// Assume white light, to begin with
	return ColorDbl(0.8, 0.8, 1.0)*intensity;
}

float Light::getIntensity() {
	return intensity;
}

glm::vec3 Light::getPos(){
	return pos;
}

bool Light::lightIntersection(Ray *ray, glm::vec3 *_p, std::vector<Triangle> _triangles){
	// Check if light intersects with point
	for (auto &triangle : _triangles) {
		glm::vec3 tmpPt;
		// Check if the ray intersects the triangle
		// If so, add the triangle to the returning vector
		if (triangle.rayIntersection(ray, &tmpPt)) {
			_p = &tmpPt;
			return true;
		}
	}
	return false;
}
