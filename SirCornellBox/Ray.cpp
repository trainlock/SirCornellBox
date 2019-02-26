#include "Ray.h"

Ray::Ray(){}

Ray::Ray(glm::vec3 _start){
	this->start = _start;
}

Ray::~Ray(){}

void Ray::setDirRay(glm::vec3 _dirRay){
	this->dirRay = _dirRay;
}

void Ray::setStartPt(glm::vec3 _start){
	this->start = _start;
}

void Ray::setEndPt(glm::vec3 _end){
	this->end = _end;
	this->dirRay = glm::normalize(this->end - this->start);
}

glm::vec3 Ray::getStartPt(){
	return this->start;
}

glm::vec3 Ray::getEndPt(){
	return this->end;
}

glm::vec3 Ray::getDirRay(){
	return this->dirRay;
}

void Ray::setTransMat(glm::mat4 transMat){
	this->translationMat = transMat;
}

glm::mat4 Ray::getTransMat(){
	return this->translationMat;
}

glm::vec3 Ray::calculateLambertian(glm::vec3 pt) {
	glm::vec3 newDir = glm::vec3(0.0f);
	glm::vec3 newPt = glm::vec3(0.0f);
	float inclination, azimuth; // Radians

	// Initialise random
	std::default_random_engine generator;
	std::default_random_engine newGenerator;

	// Get random angles
	std::uniform_real_distribution<double> distribution(0, 2.0f * M_PI);
	azimuth = distribution(generator);
	std::uniform_real_distribution<double> newDistribution(0, M_PI / 2.0f);
	inclination = newDistribution(newGenerator);

	// Calculate new direction
	newPt.x = cos(azimuth);
	newPt.y = sin(azimuth);
	newPt.z = sin(inclination);
	//std::cout << "RAY: newPt.z = " << newPt.z << "; inclination = " << inclination << std::endl;

	// Return new direction
	return newPt;
}