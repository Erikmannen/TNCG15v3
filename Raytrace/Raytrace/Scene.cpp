#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::rayIntersectionforlist(Ray arg)
{
	// for each tri in trianglelist 
	// auto fixar typ matchning och * => itterator
	// som en for each d�r varje triangle i listan kallar p� func
	for (auto* tri:Trianglelist){
		tri->rayIntersection(arg);
	};


}
