#pragma once
#include "Vertex.h";
#include "ColorDbl.h";
#include "Direction.h";
#include "Ray.h"; 
class Triangle
{
public:
	Triangle();
	~Triangle();
	void rayIntersection(Ray arg); // todo

private: 
	Vertex V0, V1, V2;
	ColorDbl trianglecolor;
	Direction normal;


};

