#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include <list>
#include "Ray.h"
class Triangle
{
public:
	Triangle();
	// todo
	//behöver lägga till normalisering av normalen i constructor
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new, Direction N, ColorDbl C) : V0(V0new), V1(V1new), V2(V2new), normal(N), trianglecolor(C) {};
	~Triangle();
	 bool rayIntersection(Ray arg,glm::vec3& intersect); // todo
	 Direction &getnormal() { return normal; };
private: 
	Vertex V0, V1, V2;

	ColorDbl trianglecolor;
	Direction normal;


};

