#include "Triangle.h"

Triangle::Triangle(){
	v0 = glm::vec3();
	v1 = glm::vec3();
	v2 = glm::vec3();
	mat = Material(ColorDbl(0, 0, 0), 0.0f, 0.0f, LAMBERTIAN);
	normal = glm::vec3(0, 0, 0);
}

Triangle::Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, Material _mat, std::string _name){
	v0 = _v0, v1 = _v1, v2 = _v2;
	mat = _mat;
	name = _name;
	normal = glm::normalize(calculateNormal());
}

Triangle::~Triangle(){}

ColorDbl Triangle::getColor(){
	return mat.getColor();
}

Material Triangle::getMaterial() {
	return mat;
}

std::string Triangle::getName(){
	return name;
}

std::array<glm::vec3, 3> Triangle::getVertices(){
	return{ v0, v1, v2 };
}

glm::vec3 Triangle::getNormal() {
	return normal;
}

glm::vec3 Triangle::getRandomPt() {
	float u = rand() / RAND_MAX;
	float v = rand() / RAND_MAX;

	if (u + v > 1.0) {
		return getRandomPt();
	}
	return getBarycentric(u, v);
}

glm::vec3 Triangle::getBarycentric(float u, float v){
	glm::vec3 pt;
	pt.x = (1 - u - v) * v0.x + u * v1.x + v * v2.x;
	pt.y = (1 - u - v) * v0.y + u * v1.y + v * v2.y;
	pt.z = (1 - u - v) * v0.z + u * v1.z + v * v2.z;
	return pt;
}

glm::vec3 Triangle::calculateNormal(){
	glm::vec3 d1 = glm::vec3(v1.x - v0.x, v1.y - v0.y, v1.z - v0.z);
	glm::vec3 d2 = glm::vec3(v2.x - v0.x, v2.y - v0.y, v2.z - v0.z);

	return glm::cross(d1, d2);
}

bool Triangle::rayIntersection(Ray *ray, glm::vec3 *_v){
	// Write code for intersection here
	const float EPSILON = 0.000000000001f;
	glm::vec3 rayStart = ray->getStartPt(); // Ps
	glm::vec3 rayDir = ray->getDirRay();	// Pe
	glm::vec3 edge1, edge2, edgeNormal, T, D, Q;
	float a, f, u, v, t;

	// M�ller Trumbore Alhorithm
	T = rayStart - v0;	// T
	edge1 = v1 - v0;	// E1
	edge2 = v2 - v0;	// E2
	D = ray->getDirRay();//rayDir - rayStart;
	edgeNormal = glm::cross(D, edge2); // P
	a = glm::dot(edgeNormal, edge1);

	if (abs(a) < EPSILON) {
		return false;
	}

	f = 1 / a;
	u = glm::dot(edgeNormal, T) * f;

	if (u < 0.0f || u > 1.0f) {
		return false;
	}

	Q = glm::cross(T, edge1);
	v = glm::dot(Q, D) * f;

	if (v < 0.0f || v > 1.0f || u + v > 1.0f) {
		return false;
	}

	t = glm::dot(Q, edge2) * f;

	if (t > EPSILON) {
		_v->x = (1 - u - v)*v0.x + u*v1.x + v*v2.x;
		_v->y = (1 - u - v)*v0.y + u*v1.y + v*v2.y;
		_v->z = (1 - u - v)*v0.z + u*v1.z + v*v2.z;
		return true;
	}
	return false;
}

std::ostream& operator<<(std::ostream& os, const Triangle& t){
	os << "v0: " << glm::to_string(t.v0) << std::endl 
	   << "v1: " << glm::to_string(t.v1) << std::endl 
	   << "v2: " << glm::to_string(t.v2);
	return os;
}

Triangle Triangle::operator=(Triangle *t){
	this->v0 = t->getVertices()[0];
	this->v1 = t->getVertices()[1];
	this->v2 = t->getVertices()[2];
	this->color = t->getColor();
	return *this;
}
