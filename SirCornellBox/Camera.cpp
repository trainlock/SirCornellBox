#include "Camera.h"
#define _CRT_SECURE_NO_WARNINGS

Camera::Camera(){}

Camera::Camera(Scene *_scn, glm::vec3 _eye){
	scene = _scn;
	eye = _eye;
}

Camera::~Camera(){}

void Camera::createImage() {
	truncatePixels();
	pixelsToPicture();

	std::cout << "Lets be creative!" << std::endl;

	const char* filename = "test.png";
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(filename, pxToPic, this->width, this->height);

	// If there is an error, display it
	if (error) std::cout << "enocoder error " << error << ":" << lodepng_error_text(error) << std::endl;

	std::cout << "My work here is done" << std::endl;
}

void Camera::truncatePixels() {
	float colorMult = 255.99f;
	double r, g, b, imax = 0.0;
	for (auto px : pixels) {
		if (px.getColor().r > imax) {
			imax = px.getColor().r;
		}
		if (px.getColor().g > imax) {
			imax = px.getColor().g;
		}
		if (px.getColor().b > imax) {
			imax = px.getColor().b;
		}
	}
	for (auto px : pixels) {
		r = trunc(px.getColor().r * (colorMult / imax));
		g = trunc(px.getColor().g * (colorMult / imax));
		b = trunc(px.getColor().b * (colorMult / imax));
		px.setColor(r, g, b);
	}
}

void Camera::pixelsToPicture() {
	float alpha = 255.99f;
	for (auto px : pixels) {
		pxToPic.push_back((char)(int)px.getColor().r);
		pxToPic.push_back((char)(int)px.getColor().g);
		pxToPic.push_back((char)(int)px.getColor().b);
		pxToPic.push_back((char)alpha);
	}
}

void Camera::render(){
	// Render goes here
	Ray ray(eye);
	float delta = 2.0f / width;
	float middle = delta / 2.0f;

	ColorDbl color = ColorDbl(1.0, 1.0, 1.0);
	float colorMult = 255.99f;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ray.setStartPt(eye);

			// Divide into subpixel for reflections
			ray.setDirRay(glm::vec3(0.0f, ((1.0f - middle) - (float)(j)*delta), ((1.0f - middle) - (float)(i)*delta)));
			color = castRay(&ray, 0, color)*colorMult;

			pixels.push_back(Pixel(color, &ray));
		}
	}
}

ColorDbl Camera::castRay(Ray *ray, int depht, ColorDbl color) {
	const float EPSILON = 0.000001f;
	float distIntersection = 0.0f, distLightIntersection = 0.0f;
	glm::vec3 intersectionPt = glm::vec3(0.0f, 0.0f, 0.0f);

	TriangleIntersection closestTriangle = scene->detectTriangle(ray);

	// Find direction between start point and light point
	glm::vec3 direction = scene->getLights().back().getPos() - closestTriangle.point;
	distLightIntersection = glm::distance(scene->getLights().back().getPos(), closestTriangle.point);

	// Make the found vector tiny to be able to search areas close by
	direction = glm::normalize(direction)*EPSILON;

	ray->setStartPt(closestTriangle.point);
	ray->setDirRay(direction);

	// Intensity added to colorDbl of each pixel as such px.getColor().r*intensity
	// Loop through all of the lights in the scene
	// If light shines upon thee, take light into your heart and become one with the light!
	if (scene->getLights().back().lightIntersection(ray, &intersectionPt, scene->triangles)) {
		// Color from ray and intensity from light

		// Distance to intersecting wall
		distIntersection = glm::distance(intersectionPt, ray->getStartPt());

		// Check if distance to wall is greater than distance to light source
		if (distIntersection > distLightIntersection) {
		// Add intensity to ray and then multiply color in triangle with color in ray
			color = closestTriangle.triangle.getColor() * scene->getLights().back().getEmission() * (1 / distLightIntersection);
		}
		else {
			// Fix so that the pixels that are in shadow accually are in shadow!
			// If an objects is in the way between the walls and the light then that pixel is in shadow. 
			color = ColorDbl(0.0, 0.0, 0.0);
		}
	}
	else {
		color = ColorDbl(0.0, 0.0, 0.0);
	}
	return color;
}
