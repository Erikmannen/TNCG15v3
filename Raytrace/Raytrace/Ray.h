#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include <list>
#include "Direction.h"
#include <random>
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>

#define M_PI 3.14159265358979323846
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
	Ray hemisphere(Vertex& Position, Direction& normaldirr);
	Ray reflection(Vertex& Postition, Direction& normaldirr);

	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
private:
	Vertex Startpoint, Endpoint;
	ColorDbl raycolor;
	
	//Triangle* endpointtriangle;
	//std::list<Vertex> Points;
	//Triangle& endtriangle;
};

