#include "Camera.h"
#define _CRT_SECURE_NO_WARNINGS

Camera::Camera(){}

Camera::Camera(Scene *_scn, glm::vec3 _eye){
	scene = _scn;
	eye = _eye;
}

Camera::~Camera(){}

void Camera::createImage() {
	pixelsToPicture();

	std::cout << "Lets be creative!" << std::endl;

	const char* filename = "test.png";
	std::vector<unsigned char> png;
	unsigned error = lodepng::encode(filename, pxToPic, this->width, this->height);

	// If there is an error, display it
	if (error) std::cout << "enocoder error " << error << ":" << lodepng_error_text(error) << std::endl;

	std::cout << "My work here is done" << std::endl;
}

void Camera::pixelsToPicture() {
	float alpha = 255.99f;
	for (auto px : pixels) {
		pxToPic.push_back((char)(int)px.getColor().r*100.0f);
		pxToPic.push_back((char)(int)px.getColor().g*100.0f);
		pxToPic.push_back((char)(int)px.getColor().b*100.0f);
		pxToPic.push_back((char)alpha);
	}
}

void Camera::render(){
	// Render goes here
	Ray ray(eye);
	float delta = 2.0f / width;
	float middle = delta / 2.0f;
	float colorMult = 255.99f;
	const float EPSILON = 0.000001f;
	int counterLight = 0;
	float distIntersection, distLightIntersection;
	glm::vec3 intersectionPt;
	ColorDbl color;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ray.setStartPt(eye);
			ray.setDirRay(glm::vec3(0.0f, ((1.0f - middle) - (float)(j)*delta), ((1.0f - middle) - (float)(i)*delta)));
			TriangleIntersection closestTriangle = scene->detectTriangle(&ray);

			// TODO: Add light to triangle
			// Light point: scene->getLights().back().pos
			// Start point at triangle: closestTriangle.point
			// Traverse from start to light point
			// If something blocks then that point is not directly illuminated

			// Find direction between start point and light point
			glm::vec3 direction = scene->getLights().back().getPos() - closestTriangle.point;
			distLightIntersection = glm::length(direction);

			// Make the found vector tiny to be able to search areas close by
			direction = glm::normalize(direction)*EPSILON;

			ray.setStartPt(closestTriangle.point);
			ray.setDirRay(direction);
			
			// Intensity added to colorDbl of each pixel as such px.getColor().r*intensity
			// Loop through all of the lights in the scene
			// If light shines upon thee, take light into your heart and become one with the light!
			if (scene->getLights().back().lightIntersection(&ray, &intersectionPt, scene->triangles)) {
				// Color from ray and intensity from light
				// Add intensity to ray and then multiply color in triangle with color in ray
				
				// Distance to intersecting wall
				distIntersection = glm::distance(intersectionPt, ray.getStartPt());
				
				// Check if distance to wall is greater than distance to light source
				if (distIntersection > distLightIntersection) {
					color = closestTriangle.triangle.getColor() * scene->getLights().back().getEmission();// *(1 / distLightIntersection);
					counterLight++;
				}
				else {
					// Fix so that the pixels that are in shadow accually are in shadow!
					// If an objects is in the way between the walls and the light then that pixel is in shadow. 
					color = ColorDbl(0.0, 0.0, 0.0);
				}
				//std::cout << "Hi my bud light!" << std::endl;
			}
			else {
				color = ColorDbl(0.0, 0.0, 0.0);
			}

			//color = closestTriangle.triangle.getColor();
			//std::cout << "Color: " << color << ", Triangle: " << closestTriangle.triangle.getName() << std::endl;
			pixels.push_back(Pixel(color, &ray));
		}
	}
	std::cout << "Light: " << counterLight << std::endl;
}
