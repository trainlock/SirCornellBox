#include "Tetrahedron.h"



Tetrahedron::Tetrahedron(){
	ColorDbl color = ColorDbl(1.0, 1.0, 0.0);
	createTetra(glm::vec3(0.0f, 0.0f, 0.0f), color);
}

Tetrahedron::Tetrahedron(glm::vec3 _pos, ColorDbl _color){
	createTetra(_pos, _color);
}


Tetrahedron::~Tetrahedron(){}

void Tetrahedron::createTetra(glm::vec3 _pos, ColorDbl _color) {
	float lengthSide = 1.0f / 3.0f;
	glm::vec3 v0 = glm::vec3( 0.0f + _pos.x,  0.0f + _pos.y, lengthSide + _pos.z);
	glm::vec3 v1 = glm::vec3(-lengthSide + _pos.x,  lengthSide + _pos.y, -lengthSide + _pos.z);
	glm::vec3 v2 = glm::vec3( lengthSide + _pos.x, -lengthSide + _pos.y, -lengthSide + _pos.z);
	glm::vec3 v3 = glm::vec3(-lengthSide + _pos.x, -lengthSide + _pos.y, -lengthSide + _pos.z);
	triangles.push_back(Triangle(v1, v2, v3, _color, "tetra_t0"));
	triangles.push_back(Triangle(v0, v3, v2, _color, "tetra_t1"));
	triangles.push_back(Triangle(v0, v1, v3, _color, "tetra_t2"));
	triangles.push_back(Triangle(v0, v2, v1, _color, "tetra_t3"));
}

std::vector<Triangle> Tetrahedron::getTriangles() {
	return this->triangles;
}

bool Tetrahedron::rayIntersection(Ray *ray){
	// Check if ray intersects the tethraderon
	return false;
}