#pragma once
#include "Triangle.h"
#include <vector>
class Scene
{
public:
	Scene();
	~Scene();
	void rayIntersectionforlist(Ray arg); // todo , for each triangle
private:
	std::vector<Triangle*> Trianglelist;
};

