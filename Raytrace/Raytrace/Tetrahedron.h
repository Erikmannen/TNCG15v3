#pragma once
#include "Vertex.h"
#include "Surface.h"
#include "Triangle.h"
#include "Direction.h"


class Tetrahedron
{
public:
	Tetrahedron();
	Tetrahedron(Vertex inbot, Vertex inleft, Vertex inright, Vertex intop,Surface insurf );
	bool tetraIntersection(Ray arg, glm::vec4& intersect);
	std::vector<Triangle> gettris() { return tris;};
private:
	Vertex bot, left, right, top;
	Surface tetrasurf;
	std::vector<Triangle> tris;
};

