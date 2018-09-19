#pragma once
#include "Triangle.h"
#include <vector>
// T kan vara triangle och senare sphere
template <typename T>
struct Intersectionobjects{
	T object;
	//Triangle tri;
	glm::vec3 point;
};



class Scene
{
public:
	Scene();
	~Scene();
	//returns vector  with all intersected objects of type intype
	//template<typename objectintersector>
	std::vector<Intersectionobjects<Triangle>> rayIntersectionforlist(Ray arg); // todo , for each triangle
private:
	std::vector<Triangle> Trianglelist;
	
};

