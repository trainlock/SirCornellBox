#pragma once
#include <sstream>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Scene.h"
#include "Pixel.h"
#include "lodepng.h"

class Camera{
public:
	Camera();
	Camera(Scene *_scn, glm::vec3 _eye);
	~Camera();

	void createImage();
	void pixelsToPicture();
	void render();
private:
	// Position of eye
	glm::vec3 eye;

	Scene *scene;
	const int height = 100;
	const int width = 100;
	std::vector<Pixel> pixels;
	std::vector<unsigned char> pxToPic;
};

