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

std::vector<Intersectionobjects<Triangle>> Scene::rayIntersectionforlist(Ray arg)
{
	//return
	std::vector<Intersectionobjects<Triangle>> intersections;

	// for each tri in trianglelist 
	// auto fixar typ matchning och * => itterator
	// som en for each där varje triangle i listan kallar på func
	//endast för trianglar atm för allmän måste tri bytas mot template

	for (auto tri:Trianglelist){
		Intersectionobjects<Triangle> Intersector; // tri or sphere (returntype for intersectionobjects)
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
