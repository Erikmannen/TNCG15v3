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

Ray Ray::hemisphere(Vertex& Position, Direction& normaldirr)
{
	// randnrgenerator
	std::default_random_engine generator;
	// uniform brdf 
	std::uniform_real_distribution<double> distribution(0.0, 1.0);

	// se fö 11
	double xi = distribution(generator); // xi 
	double yj = distribution(generator); // yj

	// 2pi*xi , asin(sqrt(yj)
	float Inclinationangle = 2 * M_PI * xi;
	float Azimuthangle = asin(sqrt(yj));
	
	Direction randdirr = normaldirr;
	//rotera först runt infallsvinkel 
	
		// rotera runt normalen 
		randdirr.setDir( glm::rotate(
			randdirr.getDir(), Inclinationangle, normaldirr.getDir()
		));
		//rotera runt tangenten ? 

		Vertex endpos(randdirr.getDir().x, randdirr.getDir().y, randdirr.getDir().z);


	return Ray(Position, endpos);
}


std::ostream & operator<<(std::ostream & os, const Ray & ray)
{
	// TODO: insert return statement here
	os <<"Startpoint :"<< ray.Startpoint << "Endpoint: "<<ray.Endpoint <<std::endl;
	return os;
}
