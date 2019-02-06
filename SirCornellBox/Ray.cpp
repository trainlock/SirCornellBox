#include "Ray.h"

Ray::Ray(){}

Ray::Ray(glm::vec3 _start){
	start = _start;
}

Ray::~Ray(){}

void Ray::setDirRay(glm::vec3 _dirRay){
	dirRay = _dirRay;
}

void Ray::setStartPt(glm::vec3 _start){
	start = _start;
}

void Ray::setEndPt(glm::vec3 _end){
	end = _end;
}

glm::vec3 Ray::getStartPt(){
	return start;
}

glm::vec3 Ray::getEndPt(){
	return end;
}

glm::vec3 Ray::getDirRay(){
	return dirRay;
}

void Ray::setTransMat(glm::mat4 transMat)
{
	this->translationMat = transMat;
}

glm::mat4 Ray::getTransMat()
{
	return this->translationMat;
}
