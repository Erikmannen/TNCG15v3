#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include <list>


class Triangle;

class Ray
{
public:
	Ray();
	Ray(Vertex Start, Vertex End)
		:Startpoint(Start), Endpoint(End) {};// , Points({ Startpoint,Endpoint }
	~Ray();
	Ray(const Ray& myray): Startpoint(myray.Startpoint),Endpoint(myray.Endpoint),raycolor(myray.raycolor)  {};
	Vertex getstart() { return Startpoint; };
	Vertex getend() { return Endpoint; };
	


	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
private:
	Vertex Startpoint, Endpoint;
	ColorDbl raycolor;
	
	//Triangle* endpointtriangle;
	//std::list<Vertex> Points;
	//Triangle& endtriangle;
};

