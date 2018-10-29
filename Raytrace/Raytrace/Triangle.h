#pragma once
#include "Vertex.h"
#include "ColorDbl.h"
#include "Direction.h"
#include <list>
#include <vector>
#include "Ray.h"
#include "Surface.h"

class Triangle
{
public:
	bool islight = false;
	Triangle();
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new);
	// todo
	//behöver lägga till normalisering av normalen i constructor
	Triangle(Vertex V0new, Vertex V1new, Vertex V2new, Direction N, Surface C = Surface()) : V0(V0new), V1(V1new), V2(V2new), normal(N), trisurf(C) {};
	~Triangle();
	bool rayIntersection(Ray arg, glm::vec4& intersect); // todo
	Triangle(const Triangle& tri);
	Direction &getnormal() { return normal; };
	Surface getsurf() { return trisurf; };
	std::vector<Vertex> getvertex() {
		std::vector<Vertex> vertexlist;
		vertexlist.push_back(V0);
		vertexlist.push_back(V1);
		vertexlist.push_back(V2);
		return vertexlist;
	};
	Vertex getrandpointontri();
	void settolight() { islight = true; };
	 
private: 
	Vertex V0, V1, V2;
	//ColorDbl trianglecolor;
	Direction normal;
	Surface trisurf;
	
	
};

