#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::addTriangle(Triangle T)
{
	//Trianglelist.push_back(T);
}

std::vector<Intersectionobjects> Scene::rayIntersectionforlist(Ray arg)
{
	//return
	std::vector<Intersectionobjects> intersections;

	// for each tri in trianglelist 
	//  fixar typ matchning och * => itterator
	// som en for each d�r varje triangle i listan kallar p� func
	//endast f�r trianglar atm f�r allm�n m�ste tri bytas mot template

	for (Triangle tri:Trianglelist){
		Intersectionobjects Intersector; // tri (returntype for intersectionobjects)
		glm::vec3 intersect; // to be passed into intersectionfuntion
		bool didintersect = tri.rayIntersection(arg,intersect);
		//x(t) = ps +t(pe-ps) == intersect

		if (didintersect == true) {
			Intersector.object = tri;
			Intersector.point = intersect - tri.getnormal().getDir();
			intersections.push_back(Intersector);
		}
	};

	return intersections;


}
