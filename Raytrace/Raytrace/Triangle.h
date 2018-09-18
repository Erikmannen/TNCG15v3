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
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new, Direction N, ColorDbl C) : V0(V0new), V1(V1new), V2(V2new), normal(N), trianglecolor(C) {};
	~Triangle();
	void rayIntersection(Ray arg); // todo

private: 
	Vertex V0, V1, V2;

	ColorDbl trianglecolor;
	Direction normal;


};

