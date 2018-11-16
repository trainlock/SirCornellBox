#include "Triangle.h"

Triangle::Triangle(){
	v0 = glm::vec3();
	v1 = glm::vec3();
	v2 = glm::vec3();
	color = ColorDbl(0, 0, 0);
	normal = glm::vec3(0, 0, 0);
}

Triangle::Triangle(glm::vec3 _v0, glm::vec3 _v1, glm::vec3 _v2, ColorDbl _color, std::string _name){
	v0 = _v0, v1 = _v1, v2 = _v2, color = _color, name = _name;
	normal = calculateNormal();
	glm::normalize(normal);
}

Triangle::~Triangle(){}

ColorDbl Triangle::getColor(){
	return color;
}

std::string Triangle::getName(){
	return name;
}

std::array<glm::vec3, 3> Triangle::getVertices(){
	return{ v0, v1, v2 };
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
	glm::vec3 rayDir = ray->getDirRay(); // Pe
	glm::vec3 edge1, edge2, edgeNormal, T, D, Q;
	float a, f, u, v, t;

	// Möller Trumbore Alhorithm
	T = rayStart - v0; // T
	edge1 = v1 - v0; // E1
	edge2 = v2 - v0; // E2
	D = rayDir - rayStart;
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
