#pragma once
#include "Vertex.h"
#include "Surface.h"
class Sphere
{
public:
	
	Sphere(Vertex pos = Vertex(), float r  =0, Surface s = Surface()) :position(pos),radius(r),spheresurf(s){};
	Direction getnormal(Vertex v) {  glm::vec3  norm =glm::normalize(v.getcoords() - position.getcoords()); 
									Direction d(norm.x,norm.y,norm.z);
									return d;};
	~Sphere();
	bool SphereIntersection(Ray arg, glm::vec3& intersect);
	Surface getsurf() { return spheresurf; };
private: 
	Vertex position;
	float radius;
	Surface spheresurf;
};

