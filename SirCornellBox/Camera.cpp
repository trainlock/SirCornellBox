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
	glm::vec3 direction;
	float delta = 2.0f / width;
	float middle = delta / 2.0f;

	ColorDbl color = ColorDbl(1.0, 1.0, 1.0);
	float colorMult = 255.99f;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			ray.setStartPt(eye);

			// Divide into subpixel for reflections
			direction = glm::vec3(0.0f, ((1.0f - middle) - (float)(j)*delta), ((1.0f - middle) - (float)(i)*delta)) - ray.getStartPt();
			ray.setDirRay(glm::normalize(direction));
			color = castRay(&ray, 0, color, 1.0f);

			pixels.push_back(Pixel(color, &ray));
		}
	}
}

ColorDbl Camera::castRay(Ray *ray, int depth, ColorDbl color, float importance) {
	const float EPSILON = 0.1f;
	const int MAX_DEPTH = 0; // TODO: Test if the room can be created without the black parts

	float distIntersection = 0.0f;
	float distLightIntersection = 0.0f;
	float lengthToSphere;
	float lengthToTriangle;
	bool isTriangleClosest = true;

	glm::vec3 intersectionPt = glm::vec3(0.0f);
	glm::vec3 lightPt = scene->getLights().back().getPos();
	glm::vec3 closestPt = glm::vec3(0.0f);
	glm::vec3 normal = glm::vec3(0.0f);
	glm::vec3 localPt;
	glm::vec3 worldPt;

	Light light = scene->getLights().back();
	ColorDbl indirectLight = color;
	ColorDbl directLight;
	ColorDbl surfaceColor;
	ColorDbl color1;
	reflectionType type;
	Material mat;

	//std::cout << "START: Color = " << color << std::endl;

	TriangleIntersection closestTriangle = scene->detectTriangle(ray);
	SphereIntersection closestSphere = scene->detectSphere(ray);

	lengthToSphere = closestSphere.distToRay;
	lengthToTriangle = glm::distance(closestTriangle.point, ray->getStartPt());

	// Check if the ray hits a sphere or a triangle
	if (lengthToSphere < lengthToTriangle && closestSphere.isHit) {
		closestPt = closestSphere.surfacePt;
		isTriangleClosest = false;
		normal = glm::normalize(-(closestSphere.sphere.getCenterPt() - closestSphere.surfacePt));
		mat = closestSphere.sphere.getMaterial();
	}
	else {
		closestPt = closestTriangle.point;
		isTriangleClosest = true;
		normal = closestTriangle.triangle.getNormal();
		mat = closestTriangle.triangle.getMaterial();
	}
	// Get type and color of surface for closest point
	type = mat.getType();
	surfaceColor = mat.getColor();

	// Find direction between start point and light point
	glm::vec3 direction = light.getPos() - closestPt;

	// Normalise the direction
	direction = glm::normalize(direction);

	// Set new starting point and direction to the ray
	ray->setStartPt(closestPt);
	ray->setDirRay(direction);

	// Check if triangle is light
	if (isTriangleClosest && type == LIGHT) {
		std::cout << "light" << std::endl;
		// Return light emission
		return light.getEmission()*importance;
	}

	// Check material
	// If lambertian ==>
	// 0. Check if depth is reached
		// Return light/color
	// 1. Direct light
		// Check if something covers part of the light source
		// Add direct to contributed light
	// 2. New direction (use local)
		// Calculate new importance to ray (BRDF, value = 0.8 for diffuse material)
	// 3. Collect indirect light
		// Add indirect to contributed light
		// Increase depth counter
	// 4. Recursive with all contributed light (in color)

	// Check if a diffuse area is hit
	if (type == LAMBERTIAN) {
		// Get direct light
		directLight = scene->ComputeDirectLight(closestPt);

		// Calculate new importance
		importance = importance * mat.getBRDF();

		// Calculate new direction of ray
		localPt = scene->ConvertToLocal(ray, closestPt, normal);
		worldPt = scene->ConvertToWorld(ray, localPt);
		ray->setDirRay(worldPt);

		// Calculate indirect light with new direction of ray until depht is reached (recursive)
		if (depth < MAX_DEPTH) {
			//std::cout << "CAMERA: depth = " << depth << std::endl;
			depth++;
			indirectLight += castRay(ray, depth, indirectLight, importance);
		}

		//std::cout << "Indirect light = " << indirectLight << ", ray Dir = " << glm::to_string(ray->getDirRay()) << ", directLight = " << directLight << std::endl;

		// Summarise all lights
		color = (directLight + indirectLight) * surfaceColor;
		//std::cout << "END: Color = " << color << ", surfaceclr = " << surfaceColor << std::endl;
		//std::cout << "indirectLight = " << indirectLight << ", surfaceColor = " << surfaceColor << ",  color = " << color << std::endl;

		// Return all light and color
		return color;
	}














































	/*
	// Check if surface point on a triangle is diffuse
	else if (isTriangleClosest && closestTriangle.triangle.getMaterial().getType() == LAMBERTIAN) {
		// Get direct light

		// If light shines upon thee, take light into your heart and become one with the light!
		if (light.lightIntersection(ray, &intersectionPt, scene->triangles)) {
			// Get distance between light and closest intersection point
			distLightIntersection = glm::distance(lightPt, closestPt);

			// Distance to intersecting wall
			distIntersection = glm::distance(intersectionPt, closestPt);

			// Check if there is a sphere between closest point and the light source
			SphereIntersection closestSphereIntersect = scene->detectSphere(ray);
			float sphereIntersectionDist = glm::distance(closestSphereIntersect.surfacePt, ray->getStartPt());
			if (sphereIntersectionDist < distIntersection) {
				distIntersection = sphereIntersectionDist;
			}
			// Check if distance to wall is greater than distance to light source
			if (distIntersection > distLightIntersection || distIntersection < EPSILON) {
				// Add intensity to ray and then multiply color in triangle with color in ray
				if (isTriangleClosest && !closestSphere.isHit) {
					color = (closestTriangle.triangle.getColor() * light.getEmission()*(1 / pow(distLightIntersection, 2)));
				}
			}
			else {
				color = ColorDbl(0.0, 0.0, 1.0);
			}
		}
		else {
			std::cout << "Unreachable" << std::endl;
			return ColorDbl(0.0, 0.0, 0.0);
		}

		// Integrate over hemisphere around the point

		// BRDF 
		// Lambertian calculation
		color = closestTriangle.triangle.getColor();

		// Recursive

		// Indirect light
		// TODO: set new direction
		if (depth < 4) {
			castRay(ray, depth + 1, color, 1.0f);
		}
		
		// Return color * light.getEmission() * (direct + indirect light)
	}

	else if (!isTriangleClosest && closestSphere.sphere.getMaterial().getType() == LAMBERTIAN) {
		// Get direct light
		// Intensity added to colorDbl of each pixel as such px.getColor().r*intensity
		// Loop through all of the lights in the scene
		// If light shines upon thee, take light into your heart and become one with the light!
		if (scene->getLights().back().lightIntersection(ray, &intersectionPt, scene->triangles)) {
			// Get distance between light and closest intersection point
			distLightIntersection = glm::distance(lightPt, closestPt);

			// Distance to intersecting wall
			distIntersection = glm::distance(intersectionPt, closestPt);

			// Check if there is a sphere between closest point and the light source
			SphereIntersection closestSphereIntersect = scene->detectSphere(ray);
			float sphereIntersectionDist = glm::distance(closestSphereIntersect.surfacePt, ray->getStartPt());
			if (sphereIntersectionDist < distIntersection) {
				distIntersection = sphereIntersectionDist;
			}
			// Check if distance to wall is greater than distance to light source
			if (distIntersection > distLightIntersection || distIntersection < EPSILON) {
				// Add intensity to ray and then multiply color in triangle with color in ray
				Light light = scene->getLights().back();
				color = (closestSphere.sphere.getColor() * light.getEmission()*(1 / pow(distLightIntersection, 2)));
				//importance = importance*brdf;
			}
			else {
				color = ColorDbl(0.0, 0.0, 1.0);
			}
		}
		else {
			std::cout << "Unreachable" << std::endl;
			return ColorDbl(0.0, 0.0, 0.0);
		}

		// Integrate over hemisphere around the point

		// BRDF 
		// Lambertian calculation
		color = closestSphere.sphere.getColor();

		// Recursive

		// Indirect light
		if (depth < 4) {
			castRay(ray, depth + 1, color, importance);
		}
		// Return color * light.getEmission() * (direct + indirect light)
	}
	





	// Intensity added to colorDbl of each pixel as such px.getColor().r*intensity
	// Loop through all of the lights in the scene
	// If light shines upon thee, take light into your heart and become one with the light!
	if ()) {
		// Color from ray and intensity from light

		// Get distance between light and closest intersection point
		distLightIntersection = glm::distance(lightPt, closestPt); 
		
		// Distance to intersecting wall
		distIntersection = glm::distance(intersectionPt, closestPt);

		// Check if there is a sphere between closest point and the light source
		SphereIntersection closestSphereIntersect = scene->detectSphere(ray);
		float sphereIntersectionDist = glm::distance(closestSphereIntersect.surfacePt, ray->getStartPt());
		if (sphereIntersectionDist < distIntersection) {
			distIntersection = sphereIntersectionDist;
		}

		// Check if distance to wall is greater than distance to light source
		if (distIntersection > distLightIntersection || distIntersection < EPSILON) {

			// Add intensity to ray and then multiply color in triangle with color in ray
			Light light = scene->getLights().back();
			if (isTriangleClosest && !closestSphere.isHit) {
				color = (closestTriangle.triangle.getColor() * light.getEmission()*(1 / pow(distLightIntersection, 2)));
			}
			else {
				color = (closestSphere.sphere.getColor() * light.getEmission()*(1 / pow(distLightIntersection, 2)));
			}
		}
		else {
			// Fix so that the pixels that are in shadow accually are in shadow!
			// If an objects is in the way between the walls and the light then that pixel is in shadow. 

			color = ColorDbl(0.0, 0.0, 1.0);
		}
	}
	else {
		std::cout << "Unreachable" << std::endl;
		color = ColorDbl(0.0, 1.0, 0.0);
	}
	return color;
	*/
}
