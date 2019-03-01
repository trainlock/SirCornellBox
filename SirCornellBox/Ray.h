#pragma once
#define _USE_MATH_DEFINES
#define GLM_ENABLE_EXPERIMENTAL // TODO: Remove

#include <vector>
#include <random>
#include <cmath> 

#include <stdlib.h> // rand

#include "ColorDbl.h"
#include "../SirCornellBox/glm/glm.hpp"
#include "../SirCornellBox/glm/gtx/rotate_vector.hpp"

#include "./glm/gtx/string_cast.hpp" // TODO: Remove

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

	glm::vec3 calculateLambertian(glm::vec3 pt, glm::vec3 normal);

private:
	glm::vec3 start, end;
	glm::vec3 dirRay;
	ColorDbl color;
	glm::mat4 translationMat;
};

