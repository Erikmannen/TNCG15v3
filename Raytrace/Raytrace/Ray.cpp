#include "Ray.h"

Ray::Ray()
{
	Vertex myvertex;
	Startpoint = myvertex;
	Endpoint = myvertex;
	Points = { &Startpoint,&Endpoint };
}


Ray::~Ray()
{
}

std::ostream & operator<<(std::ostream & os, const Ray & ray)
{
	// TODO: insert return statement here
	os <<"Startpoint :"<< ray.Startpoint << "Endpoint: "<<ray.Endpoint ;
	return os;
}
