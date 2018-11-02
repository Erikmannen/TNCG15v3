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
		:Startpoint(Start), Endpoint(End) {
		raycolor = ColorDbl();};
	Ray(Vertex Start, Vertex End,ColorDbl rayco)
		:Startpoint(Start), Endpoint(End),raycolor(rayco) {};// , Points({ Startpoint,Endpoint }
	~Ray();
	//Ray(const Ray& myray): Startpoint(myray.Startpoint),Endpoint(myray.Endpoint),raycolor(myray.raycolor)  {};
	Vertex getstart() { return Startpoint; };
	Vertex getend() { return Endpoint; };
	Direction getdirection() {
		glm::vec3 temp(Startpoint.getcoords() -Endpoint.getcoords());
							return Direction(temp.x,temp.y,temp.z);};

	void setend(Vertex v) { Endpoint = v; };
	void setraycolor(ColorDbl incolor) { raycolor = incolor; };
	ColorDbl getraycolor() { return raycolor; };


	Ray hemisphere(Vertex& Position, Direction& normaldirr);
	Ray reflection(Vertex& Postition, Direction& normaldirr);
	
	friend std::ostream& operator<<(std::ostream& os, const Ray& ray);
private:
	Vertex Startpoint, Endpoint;
	ColorDbl raycolor = ColorDbl();
	
	//Triangle* endpointtriangle;
	//std::list<Vertex> Points;
	//Triangle& endtriangle;
};

