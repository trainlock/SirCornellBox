#include "Scene.h"

Scene::Scene(){
	initLights();
	initVertices();
	initTriangles();
	initObjects();
}

Scene::~Scene(){}

void Scene::initLights() {
	// Assume white light!
	lights.push_back(Light(glm::vec3(0, 2, 4.9f), 10000.0f));
}

void Scene::initVertices(){
	// Roof
	vertices.push_back(glm::vec3(0.0f, 6.0f, 5.0f));
	vertices.push_back(glm::vec3(10.0f, 6.0f, 5.0f));
	vertices.push_back(glm::vec3(13.0f, 0.0f, 5.0f));
	vertices.push_back(glm::vec3(10.0f, -6.0f, 5.0f));
	vertices.push_back(glm::vec3(0.0f, -6.0f, 5.0f));
	vertices.push_back(glm::vec3(-3.0f, 0.0f, 5.0f));
	vertices.push_back(glm::vec3(5.0f, 0.0f, 5.0f)); // Middle point

	// Floor
	vertices.push_back(glm::vec3(0.0f, 6.0f, -5.0f));
	vertices.push_back(glm::vec3(10.0f, 6.0f, -5.0f));
	vertices.push_back(glm::vec3(13.0f, 0.0f, -5.0f));
	vertices.push_back(glm::vec3(10.0f, -6.0f, -5.0f));
	vertices.push_back(glm::vec3(0.0f, -6.0f, -5.0f));
	vertices.push_back(glm::vec3(-3.0f, 0.0f, -5.0f));
	vertices.push_back(glm::vec3(5.0f, 0.0f, -5.0f)); // Middle point
}

void Scene::initTriangles() {
	// KOLLA INTE HÄR; DET ÄR RÄTT (LOVAR OCH SVÄR PÅ DEN EVIGA MÅNEN)
	// Colors
	ColorDbl roofColor = ColorDbl(0.4, 0.4, 0.4); // Grey
	//ColorDbl roofColor	= ColorDbl(0.0, 0.0, 0.0); // Black
	ColorDbl floorColor = ColorDbl(1.0, 1.0, 1.0); // white
	ColorDbl wallColor1 = ColorDbl(1.0, 0.0, 1.0); // Magenta
	ColorDbl wallColor2 = ColorDbl(0.0, 1.0, 1.0); // Cyan
	ColorDbl wallColor3 = ColorDbl(1.0, 1.0, 0.0); // Yellow
	ColorDbl wallColor4 = ColorDbl(1.0, 0.0, 0.0); // Red
	ColorDbl wallColor5 = ColorDbl(0.0, 1.0, 0.0); // Green
	ColorDbl wallColor6 = ColorDbl(0.0, 0.0, 1.0); // Blue

	float p = 0.0f;
	float refIdx = 0.0f;
	Material matRoof = Material(roofColor, p, refIdx);
	Material matFloor = Material(floorColor, p, refIdx);
	Material matWall1 = Material(wallColor1, p, refIdx);
	Material matWall2 = Material(wallColor2, p, refIdx);
	Material matWall3 = Material(wallColor3, p, refIdx);
	Material matWall4 = Material(wallColor4, p, refIdx);
	Material matWall5 = Material(wallColor5, p, refIdx);
	Material matWall6 = Material(wallColor6, p, refIdx);

	// Triangles Roof
	Triangle t1(vertices.at(0), vertices.at(1), vertices.at(6), matRoof, "t1");
	Triangle t2(vertices.at(1), vertices.at(2), vertices.at(6), matRoof, "t2");
	Triangle t3(vertices.at(2), vertices.at(3), vertices.at(6), matRoof, "t3");
	Triangle t4(vertices.at(3), vertices.at(4), vertices.at(6), matRoof, "t4");
	Triangle t5(vertices.at(4), vertices.at(5), vertices.at(6), matRoof, "t5");
	Triangle t6(vertices.at(5), vertices.at(0), vertices.at(6), matRoof, "t6");

	// Triangles Floor
	Triangle t7(vertices.at(8), vertices.at(7), vertices.at(13), matFloor, "t7");
	Triangle t8(vertices.at(9), vertices.at(8), vertices.at(13), matFloor, "t8");
	Triangle t9(vertices.at(10), vertices.at(9), vertices.at(13), matFloor, "t9");
	Triangle t10(vertices.at(11), vertices.at(10), vertices.at(13), matFloor, "t10");
	Triangle t11(vertices.at(12), vertices.at(11), vertices.at(13), matFloor, "t11");
	Triangle t12(vertices.at(7), vertices.at(12), vertices.at(13), matFloor, "t12");

	// Triangles Wall 1
	Triangle t13(vertices.at(0), vertices.at(8), vertices.at(1), matWall1, "t13");
	Triangle t14(vertices.at(0), vertices.at(7), vertices.at(8), matWall1, "t14");

	// Triangles Wall 2
	Triangle t15(vertices.at(1), vertices.at(9), vertices.at(2), matWall2, "t15");
	Triangle t16(vertices.at(1), vertices.at(8), vertices.at(9), matWall2, "t16");

	// Triangles Wall 3
	Triangle t17(vertices.at(2), vertices.at(10), vertices.at(3), matWall3, "t17");
	Triangle t18(vertices.at(2), vertices.at(9), vertices.at(10), matWall3, "t18");

	// Triangles Wall 4
	Triangle t19(vertices.at(3), vertices.at(11), vertices.at(4), matWall4, "t19");
	Triangle t20(vertices.at(3), vertices.at(10), vertices.at(11), matWall4, "t20");

	// Triangles Wall 5
	Triangle t21(vertices.at(4), vertices.at(12), vertices.at(5), matWall5, "t21");
	Triangle t22(vertices.at(4), vertices.at(11), vertices.at(12), matWall5, "t22");

	// Triangles Wall 6
	Triangle t23(vertices.at(5), vertices.at(7), vertices.at(0), matWall6, "t23");
	Triangle t24(vertices.at(5), vertices.at(12), vertices.at(7), matWall6, "t24");

	// Set triangles
	// Roof
	roomTriangles.push_back(t1);
	roomTriangles.push_back(t2);
	roomTriangles.push_back(t3);
	roomTriangles.push_back(t4);
	roomTriangles.push_back(t5);
	roomTriangles.push_back(t6);

	// Floor
	roomTriangles.push_back(t7);
	roomTriangles.push_back(t8);
	roomTriangles.push_back(t9);
	roomTriangles.push_back(t10);
	roomTriangles.push_back(t11);
	roomTriangles.push_back(t12);

	// Wall 1
	roomTriangles.push_back(t13);
	roomTriangles.push_back(t14);

	// Wall 2
	roomTriangles.push_back(t15);
	roomTriangles.push_back(t16);

	// Wall 3
	roomTriangles.push_back(t17);
	roomTriangles.push_back(t18);

	// Wall 4
	roomTriangles.push_back(t19);
	roomTriangles.push_back(t20);

	// Wall 5
	roomTriangles.push_back(t21);
	roomTriangles.push_back(t22);

	// Wall 6
	roomTriangles.push_back(t23);
	roomTriangles.push_back(t24);

	// Add all triangles to triangles
	triangles.insert(triangles.end(), roomTriangles.begin(), roomTriangles.end());
}

void Scene::initObjects() {
	// Create tetrahedron
	float p = 0.8f;
	float refIdx = 1.0f;
	ColorDbl color = ColorDbl(0.0, 1.0, 0.0);
	Material mat = Material(color, p, refIdx);
	Tetrahedron tetra = Tetrahedron(glm::vec3(8, 0, -4), mat);
	std::vector<Triangle> tetraTriangles = tetra.getTriangles();
	triangles.insert(triangles.end(), tetraTriangles.begin(), tetraTriangles.end());

	// Create sphere
	color = ColorDbl(1.0, 0.0, 1.0);
	mat = Material(color, p, refIdx);
	Sphere sphere = Sphere(glm::vec3(4, 2, -2), 0.5f, mat);
	spheres.push_back(sphere);
}

std::vector<Light> Scene::getLights() {
	return lights;
}

TriangleIntersection Scene::detectTriangle(Ray *ray){
	// Detect intersecting triangles with ray and store in a triangle intersection
	float distance = 10000000.0f;

	TriangleIntersection closestTriangle;
	TriangleIntersection tmpIntersection;
	glm::vec3 tmpPt;

	for (auto &triangle : triangles) {
		tmpPt = glm::vec3(0.0f);
		// Check if ray intersects triangle
		if (triangle.rayIntersection(ray, &tmpPt)) {
			tmpIntersection.triangle = triangle;
			tmpIntersection.point = tmpPt;

			// Check if triangle is the closest on to origin of ray
			float distTriangle = glm::distance(ray->getStartPt(), tmpIntersection.point);
			if (distTriangle < distance && distTriangle > 0.0f) {
				distance = distTriangle;
				closestTriangle = tmpIntersection;
			}
		}
	}
	return closestTriangle;
}

SphereIntersection Scene::detectSphere(Ray *ray) {
	// Detect intersection between the sphere and ray and save it in a sphere intersection
	float EPSILON = 0.0001f;
	float distCenter = 0.0f;
	float distance = 10000.0f;

	SphereIntersection closestSphere;
	SphereIntersection tmpSphere;
	glm::vec3 tmpPt;

	// Initialise closest sphere with nonsense
	closestSphere.distToRay = 10000.0f;

	for (auto &sphere : spheres) {
		// Check if sphere is hit
		// Get point of intersection for the ray (might not hit the sphere)
		if (sphere.calculateSurfacePt(ray->getStartPt(), ray->getDirRay(), &tmpPt)) {
			tmpSphere.sphere = sphere;
			tmpSphere.surfacePt = tmpPt;
			tmpSphere.distToRay = glm::distance(tmpPt, ray->getStartPt());
			tmpSphere.isHit = true;

			// Check if the current surface point is the one closest to the ray starting point
			if (tmpSphere.distToRay < distance) {
				distance = tmpSphere.distToRay;

				closestSphere.sphere = tmpSphere.sphere;
				closestSphere.surfacePt = tmpSphere.surfacePt;
				closestSphere.distToRay = tmpSphere.distToRay;
				closestSphere.isHit = tmpSphere.isHit;
			}
		}
	}
	return closestSphere;
}


glm::vec3 Scene::ConvertToLocal(Ray *ray, glm::vec3 intersectionPt, glm::vec3 normal) {
	glm::vec3 X, Y, Z, I;

	I = ray->getDirRay();
	Z = normal;
	X = glm::normalize(glm::perp(I, Z));
	Y = glm::cross(-X, Z);
	glm::mat4 rotationMatrix = glm::mat4(glm::vec4(X, 0), glm::vec4(Y, 0), glm::vec4(Z, 0), glm::vec4(0, 0, 0, 1));
	glm::mat4 translationMatrix = glm::mat4(glm::vec4(1, 0, 0, 0), glm::vec4(0, 1, 0, 0), glm::vec4(0, 0, 1, 0), glm::vec4(-intersectionPt.x, -intersectionPt.y, -intersectionPt.z, 1));
	glm::mat4 M = rotationMatrix * translationMatrix;

	//glm::vec4 iPtT = glm::outerProduct(M, iPt);
	glm::vec4 localPos = M * glm::vec4(intersectionPt, 1.0f) * glm::inverse(M);
	ray->setTransMat(M);
	return glm::vec3(localPos.x, localPos.y, localPos.z);
}

glm::vec3 Scene::ConvertToWorld(Ray *ray, glm::vec3 localVec) {
	glm::vec4 worldPt = ray->getTransMat()*glm::vec4(localVec, 1.0f)*glm::inverse(ray->getTransMat());
	return glm::vec3(worldPt.x, worldPt.y, worldPt.z);
}

