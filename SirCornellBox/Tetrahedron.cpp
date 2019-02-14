#include "Tetrahedron.h"

Tetrahedron::Tetrahedron(){
	ColorDbl color = ColorDbl(1.0, 1.0, 0.0);
	float p = 0.8f;
	float refIdx = 1.0f;
	Material mat = Material(color, p, refIdx, LAMBERTIAN);
	createTetra(glm::vec3(0.0f, 0.0f, 0.0f), mat);
}

Tetrahedron::Tetrahedron(glm::vec3 _pos, Material _mat){
	createTetra(_pos, _mat);
}

Tetrahedron::~Tetrahedron(){}

void Tetrahedron::createTetra(glm::vec3 _pos, Material _mat) {
	float lengthSide = 1.0f / 3.0f;

	glm::vec3 v0 = glm::vec3( 0.0f + _pos.x,  0.0f + _pos.y, lengthSide + _pos.z);
	glm::vec3 v1 = glm::vec3( 0.0f + _pos.x,  lengthSide + _pos.y, -lengthSide + _pos.z);
	glm::vec3 v2 = glm::vec3( lengthSide + _pos.x, -lengthSide + _pos.y, -lengthSide + _pos.z);
	glm::vec3 v3 = glm::vec3(-lengthSide + _pos.x, -lengthSide + _pos.y, -lengthSide + _pos.z);

	triangles.push_back(Triangle(v1, v2, v3, _mat, "tetra_t0"));
	triangles.push_back(Triangle(v0, v3, v2, _mat, "tetra_t1"));
	triangles.push_back(Triangle(v0, v1, v3, _mat, "tetra_t2"));
	triangles.push_back(Triangle(v0, v2, v1, _mat, "tetra_t3"));
}

std::vector<Triangle> Tetrahedron::getTriangles() {
	return this->triangles;
}

bool Tetrahedron::rayIntersection(Ray *ray){
	// Check if ray intersects the tethraderon
	return false;
}