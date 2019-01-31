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
	const float EPSILON = 0.1f;
	float distIntersection = 0.0f;
	float distLightIntersection = 0.0f;
	bool isTriangleClosest = true;
	float lengthToSphere;
	float lengthToTriangle;

	glm::vec3 intersectionPt = glm::vec3(0.0f);
	glm::vec3 lightPt = scene->getLights().back().getPos();
	glm::vec3 closestPt = glm::vec3(0.0f);

	TriangleIntersection closestTriangle = scene->detectTriangle(ray);

	// TODO: Hits sphere from the light source but not from the eye
	// TODO: Fix so that the sphere can be hit from the eye or change the if statements to fit light hit
	std::cout << "CAMERA: Before assignment" << std::endl;
	SphereIntersection closestSphere = scene->detectSphere(ray);
	std::cout << "CAMERA: Closest Distance to Ray = " << closestSphere.distToRay << std::endl;

	lengthToSphere = closestSphere.distToRay;
	lengthToTriangle = glm::distance(closestTriangle.point, ray->getStartPt());

	// Check if the ray hits a sphere or a triangle
	if (lengthToSphere < lengthToTriangle && closestSphere.isHit) {
		closestPt = closestSphere.surfacePt;
		isTriangleClosest = false;
		std::cout << "Closest is a Sphere" << std::endl;
		// TODO: Check if the sphere is hit (hint: use sphere.isHit)

	}
	else {
		closestPt = closestTriangle.point;
		isTriangleClosest = true;
	}

	// Find direction between start point and light point
	glm::vec3 direction = scene->getLights().back().getPos() - closestPt;

	// Normalise the direction
	direction = glm::normalize(direction);// * EPSILON;

	// Set new starting point and direction to the ray
	ray->setStartPt(closestPt);
	ray->setDirRay(direction);


	// Intensity added to colorDbl of each pixel as such px.getColor().r*intensity
	// Loop through all of the lights in the scene
	// If light shines upon thee, take light into your heart and become one with the light!
	if (scene->getLights().back().lightIntersection(ray, &intersectionPt, scene->triangles)) {
		// Color from ray and intensity from light

		// Get distance between light and closest intersection point
		distLightIntersection = glm::distance(lightPt, closestPt); 
		
		// Distance to intersecting wall
		distIntersection = glm::distance(intersectionPt, ray->getStartPt());

		// Check if there is a sphere between closest point and the light source
		std::cout << "CAMERA: BEFORE IF" << std::endl;
		SphereIntersection closestSphereIntersect = scene->detectSphere(ray);
		std::cout << "CAMERA: AFTER IF" << std::endl;
		float sphereIntersectionDist = glm::distance(closestSphereIntersect.surfacePt, ray->getStartPt());
		if (sphereIntersectionDist < distIntersection && closestSphereIntersect.isHit) {
			distIntersection = sphereIntersectionDist;
		}


		// TODO: Fix light intersection by checking if a sphere is between the wall or not
		// TODO: Check which is closest
		// TOOD: Colour point based on the closest point (triangle or sphere?)





		// Check if distance to wall is greater than distance to light source
		if (distIntersection > distLightIntersection || distIntersection < EPSILON) {

			// Add intensity to ray and then multiply color in triangle with color in ray
			Light light = scene->getLights().back();
			if (isTriangleClosest) {
				color = (closestTriangle.triangle.getColor() * light.getEmission());// *(1 / distLightIntersection));
			}
			else {
				color = (closestSphere.sphere.getColor() * light.getEmission());// *(1 / distLightIntersection));
				std::cout << "color = " << color << std::endl;
				std::cout << closestSphere.surfacePt.x << std::endl;
			}
		}else {
			// Fix so that the pixels that are in shadow accually are in shadow!
			// If an objects is in the way between the walls and the light then that pixel is in shadow. 
			//std::cout << "In shadow" << std::endl;
			color = ColorDbl(0.0, 0.0, 1.0);
		}
	}
	else {
		std::cout << "Unreachable" << std::endl;
		color = ColorDbl(0.0, 1.0, 0.0);
	}
	return color;
}
