#include "Ray.h"

Ray::Ray()
{
	Vertex myvertex;
	Startpoint = myvertex;
	Endpoint = myvertex;
	ColorDbl color;
	raycolor = color;
	//Points = { &Startpoint,&Endpoint };
	//endtriangle = Triangle temp;
}


Ray::~Ray()
{
}


std::ostream & operator<<(std::ostream & os, const Ray & ray)
{
	// TODO: insert return statement here
	os <<"Startpoint :"<< ray.Startpoint << "Endpoint: "<<ray.Endpoint <<std::endl;
	return os;
}
