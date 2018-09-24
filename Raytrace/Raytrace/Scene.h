#pragma once
#include "Triangle.h"
#include <vector>
// T kan vara triangle och senare sphere

struct Intersectionobjects{
	Triangle object;
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
	std::vector<Intersectionobjects> rayIntersectionforlist(Ray arg); // todo , for each triangle
	void addTriangle(Triangle T);
	
	void CreateWorld();
private:
	std::vector<Triangle> Trianglelist;
	
	
};

