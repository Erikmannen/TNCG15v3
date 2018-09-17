#pragma once
#include "Triangle.h";
#include <list>;
class Scene
{
public:
	Scene();
	~Scene();
	void rayIntersection(Ray arg); // todo , for each triangle
private:
	std::list<Triangle*> Trianglelist;
};

