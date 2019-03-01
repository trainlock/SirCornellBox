#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdlib.h> // rand

#include "Scene.h"
#include "Pixel.h"
#include "lodepng.h"
#include "../SirCornellBox/glm/gtx/string_cast.hpp"

class Camera{
public:
	Camera();
	Camera(Scene *_scn, glm::vec3 _eye);
	~Camera();

	void createImage();
	void truncatePixels();
	void pixelsToPicture();
	void render();
	ColorDbl castRay(Ray *ray, int depth, float importance);

	// TODO: Add Radiosity or light contribution
private:
	// Position of eye
	glm::vec3 eye;

	Scene *scene;
	const int height = 200;
	const int width = 200;
	std::vector<Pixel> pixels;
	std::vector<unsigned char> pxToPic;
};

