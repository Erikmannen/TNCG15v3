#pragma once
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
#include "Surface.h"

// T kan vara triangle och senare sphere

struct triangleintersection{
	Triangle object;
	//Triangle tri;
	glm::vec3 point;
	//Surface surface;
};

struct sphereintersection {
	Sphere object;
	//Triangle tri;
	glm::vec3 point;
//	Surface surface;
};



class Scene
{
public:
	Scene();
	~Scene();
	//returns vector  with all intersected objects of type intype
	//template<typename objectintersector>
	std::vector<triangleintersection> rayIntersectionfortri(Ray arg); // todo , for each triangle
	std::vector<sphereintersection> rayIntersectionforsph(Ray arg); // todo , for each triangle
	
	//void addTriangle(Triangle T);
	void addsph(Sphere newsph) { Spherelist.push_back(newsph); };
	size_t trilistsize() { return Trianglelist.size(); };
	size_t sphlistsize() { return Spherelist.size(); };
	void CreateWorld();
	ColorDbl lightcontribution(Vertex v, Direction norm);
	std::vector<Triangle> gettrilist() { return Trianglelist; };
private:
	std::vector<Triangle> Trianglelist;
	std::vector<Sphere> Spherelist;
	
	
};

