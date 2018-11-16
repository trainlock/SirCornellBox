#include <iostream>
#include "Scene.h"
#include "Camera.h"

// Bra sida: https://lodev.org/lodepng/
int main(int argc, char **argv) {
	std::cout << "Hello World! " << std::endl;

	/*
	Eye positions
	glm::vec3 eye1 = { -2, 0, 0 };
	glm::vec3 eye2 = { -1, 0, 0 };
	*/

	//glm::vec3 eye = glm::vec3(-2, 0, 0);
	glm::vec3 eye = glm::vec3(-1, 0, 0);

	Scene scn;
	Camera cam(&scn, eye);
	//cam.setPixels();
	cam.render();
	cam.createImage();

	std::cout << "The END!" << std::endl;
	std::system("pause");
	return 0;
}
