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

void Ray::setTransMat(glm::mat4 transMat)
{
	this->translationMat = transMat;
}

glm::mat4 Ray::getTransMat()
{
	return this->translationMat;
}
