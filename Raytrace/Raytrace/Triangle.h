#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include <list>
#include "Ray.h"
#include "Surface.h"

class Triangle
{
public:
	Triangle();
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new);
	// todo
	//beh�ver l�gga till normalisering av normalen i constructor
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new, Direction N, Surface C = Surface()) : V0(V0new), V1(V1new), V2(V2new), normal(N), trisurf(C) {};
	~Triangle();
	 bool rayIntersection(Ray arg,glm::vec3& intersect); // todo
	 Triangle(const Triangle& tri);
	 Direction &getnormal() { return normal; };
	 Surface getsurf() { return trisurf; };
private: 
	Vertex V0, V1, V2;
	//ColorDbl trianglecolor;
	Direction normal;
	Surface trisurf;

};

