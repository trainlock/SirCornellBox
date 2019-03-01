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

glm::vec3 Ray::calculateLambertian(glm::vec3 pt, glm::vec3 normal) {
	//glm::vec3 newDir = glm::vec3(0.0f);
	//glm::vec3 newPt = glm::vec3(0.0f);
	//float inclination, azimuth; // Radians

	//// Initialise random angles in degrees
	//azimuth = rand() % 360;
	//inclination = rand() % 90;

	//// Convert to radians
	//azimuth = glm::radians(azimuth);
	//inclination = glm::radians(inclination);

	//// Calculate new direction
	//newPt.x = cos(azimuth);
	//newPt.y = sin(azimuth);
	//newPt.z = sin(inclination);
	////std::cout << "RAY: Pt = " << glm::to_string(pt) << "; newPt = " << glm::to_string(newPt) << "; inclination = " << inclination << "; newPt - Pt = " << glm::to_string(newPt - pt) << std::endl;


	float inclanation = (M_PI / 4) + (rand() / RAND_MAX) * (M_PI / 4);
	float azimuth = (rand() / RAND_MAX) * (2 * M_PI);
	glm::vec3 _in = glm::vec3(dirRay.x, dirRay.y, dirRay.z);
	glm::vec3 _normal = glm::normalize(glm::vec3(normal.x, normal.y, normal.z));
	glm::vec3 _tangent = glm::normalize((glm::cross(_in, _normal)));
	glm::vec3 _out = _normal;

	_out = glm::normalize(glm::rotate(_out, inclanation, _tangent));
	_out = glm::normalize(glm::rotate(_out, azimuth, _normal));

	glm::vec3 newDir = glm::vec3(_out.x, _out.y, _out.z);
	
	// Return new direction
	return newDir;
}