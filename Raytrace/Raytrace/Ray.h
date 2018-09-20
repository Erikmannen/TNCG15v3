#pragma once
#include "Vertex.h"
#include <list>
class Ray
{
public:
	Ray();
	Ray(Vertex Start, Vertex End)
		:Startpoint(Start), Endpoint(End) {}// , Points({ Startpoint,Endpoint }
	~Ray();
	Vertex getstart();
	Vertex getend();


	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
private:
	Vertex Startpoint, Endpoint;
	//std::list<Vertex> Points;
	//Triangle& endtriangle;
};

