#pragma once

#include <vector>

#include "ColorDbl.h"
#include "../SirCornellBox/glm/glm.hpp"

class Ray{
public:
	Ray();
	Ray(glm::vec3 _start);
	~Ray();

	void setDirRay(glm::vec3 _dirRay);
	void setStartPt(glm::vec3 _start);
	void setEndPt(glm::vec3 _end);

	glm::vec3 getStartPt();
	glm::vec3 getEndPt();
	glm::vec3 getDirRay();

	void setTransMat(glm::mat4 transMat);
	glm::mat4 getTransMat();

private:
	glm::vec3 start, end;
	glm::vec3 dirRay;
	ColorDbl color;
	glm::mat4 translationMat;
};

