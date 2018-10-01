#include "Sphere.h"
#define MINVALUE 1e-5f


Sphere::~Sphere()
{
}

bool Sphere::SphereIntersection(Ray arg, glm::vec3& intersect)
{
	//TODO
	// setting up mark notation fö 6 
	// I = normalized dirr
	glm::vec3 I = glm::normalize( arg.getend().getcoords() - arg.getstart().getcoords());
	Vertex o = arg.getstart();
	Vertex c = position;
	float r = radius;
	glm::vec3 oc = o.getcoords() - c.getcoords();
	// substitutions
	float a = glm::dot(I, I);
	float b = glm::dot(2.0f * I, oc);
	float ac = glm::dot(oc , oc) - glm::pow(r, 2);
	// ad^2+bd+ac= 0 <=> d=-b/2 +- √((b/2)^2 + ac)
	//+,- => 2 solutions
	float d1 = -b / 2.0f;
	float d2 = d1;
	float rest = glm::pow(d1, 2) - ac;
	d1 += rest;
	d2 -= rest;

	if (rest < MINVALUE)
		return false;

	rest = glm::sqrt(rest);
	if (d1 <= 0 && d2 <= 0) {
		return false;
	}
	else if (d2 < d1) {
		intersect = o.getcoords() + d2 * I;
		return true;
	}
	else if (d1 < d2) {
		intersect = o.getcoords() + d1 * I;
		return true;
	}
	else {
		intersect = o.getcoords() + d2 * I;
		return true;
	}

	//This will never happen.
	return false;
}


