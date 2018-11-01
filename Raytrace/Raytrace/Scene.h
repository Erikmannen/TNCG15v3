#pragma once
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
#include <list>
#include "Surface.h"
#include "Tetrahedron.h"

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
	std::list<triangleintersection> rayIntersectionfortri(Ray arg); 
	std::list<sphereintersection> rayIntersectionforsph(Ray arg); 
	
	size_t trilistsize() { return Trianglelist.size(); };
	size_t sphlistsize() { return Spherelist.size(); };
	void CreateWorld();

	ColorDbl lightcontribution(Vertex v, Direction norm); // todo

	void addsph(Sphere newsph) { Spherelist.push_back(newsph); };
	void addtetra(Tetrahedron newtetra) { 
		int counter = 0;
		for(Triangle tri : newtetra.gettris())
		{
			std::cout<<tri.getsurf().getsurfcolor();
			Trianglelist.push_front(tri);
		}
		};
	std::list<Triangle> gettrilist() { return Trianglelist; };
	Triangle getlights() { return light; };
private:
	std::list<Triangle> Trianglelist;
	
	std::vector<Sphere> Spherelist;
	Triangle light;
	
};

