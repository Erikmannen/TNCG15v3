#pragma once
#include "Vertex.h"
#include "Surface.h"
class Sphere
{
public:
	
	Sphere(Vertex pos = Vertex(), float r  =0, Surface s = Surface()) :position(pos),radius(r),spheresurf(s){};

	~Sphere();
	bool SphereIntersection(Ray arg, glm::vec3& intersect);
private: 
	Vertex position;
	float radius;
	Surface spheresurf;
};

