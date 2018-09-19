#pragma once
#include "Triangle.h"
#include <vector>
// T kan vara triangle och senare sphere
template <typename T>
struct Intersections{
	T object;
	//Triangle tri;
	glm::vec3 point;
};

class Scene
{
public:
	Scene();
	~Scene();
	//returns vector or list with all intersected triangles
	template<typename in> std::vector<in> rayIntersectionforlist(Ray arg); // todo , for each triangle
private:
	std::vector<Triangle*> Trianglelist;
};

