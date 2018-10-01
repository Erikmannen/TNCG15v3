#include "Sphere.h"
#define MINVALUE 1e-5f


Sphere::~Sphere()
{
}

bool Sphere::SphereIntersection(Ray arg, glm::vec3& intersect)
{
	//TODO
	// setting up mark notation 
	// I = normalized dirr
	glm::vec3 I = glm::normalize( arg.getend().getcoords() - arg.getstart().getcoords());
	Vertex o = arg.getstart();
	Vertex c = position;
	float r = radius;

	glm::vec3 oc = o.getcoords() - c.getcoords();

	float b = glm::dot(2.0f * I, oc);
	float a = glm::dot(I, I);
	float d1 = -b / 2.0f;
	float d2 = d1;


	float delta = d1 * d1 - (glm::dot(oc, oc) - r * r);
	if (delta < -MINVALUE) {
		return false; // complex solutions
	}
	else if (delta > -MINVALUE && delta < MINVALUE) {
		//intersect = d1;
		return true;
	}

	float dSqrt = std::sqrt(delta);

	d1 -= dSqrt;
	d2 += dSqrt;

	if (d1 > MINVALUE) {
		//intersect = d1;
		return true;
	}

	else if (d2 > MINVALUE) {
		//intersect = d2;
		return true;
	}
	return false;


}
