#include "Scene.h"



Scene::Scene()
{
}


Scene::~Scene()
{
}

template<typename in>
std::vector<in> Scene::rayIntersectionforlist(Ray arg)
{
	// for each tri in trianglelist 
	// auto fixar typ matchning och * => itterator
	// som en for each d�r varje triangle i listan kallar p� func
	for (auto* tri:Trianglelist){
		double intersec = tri->rayIntersection(arg);
		double result = 
		if()
	};


}
