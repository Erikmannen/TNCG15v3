#pragma once
#include "Triangle.h"
#include "Sphere.h"
#include <vector>

#include "Surface.h"

// T kan vara triangle och senare sphere

struct triangleintersection{
	Triangle object;
	Vertex point;
};

struct sphereintersection {
	Sphere object;
	Vertex point;

};



class Scene
{
public:
	Scene();
	~Scene();
	//returns vector  with all intersected objects of type 
	std::vector<triangleintersection> rayIntersectionfortri(Ray arg); 
	std::vector<sphereintersection> rayIntersectionforsph(Ray arg); 

	size_t trilistsize() { return Trianglelist.size(); };
	size_t sphlistsize() { return Spherelist.size(); };
	void CreateWorld();

	ColorDbl lightcontribution(Vertex v, Direction norm); // todo

	void addsph(Sphere newsph) { Spherelist.push_back(newsph); };
	std::vector<Triangle> gettrilist() { return Trianglelist; };
private:
	std::vector<Triangle> Trianglelist;
	std::vector<Sphere> Spherelist;
	
	
};

