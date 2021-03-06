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
	std::uniform_real_distribution<float> distribution(0.0, 1.0);

	// se f� 11
	float xi = distribution(generator); // xi 
	float yj = distribution(generator); // yj
	
	//def v1 postion motsvarar directions 
	auto v1 = glm::normalize(-Position.getcoords() - glm::dot(-Position.getcoords(), normaldirr.getDir())*normaldirr.getDir());
	//v2 = normal 
	auto v3 = -glm::cross(v1, normaldirr.getDir());
	// 2pi*xi , asin(sqrt(yj)
	float Inclinationangle = 2 * M_PI * xi;
	float Azimuthangle = asin(sqrt(yj));
	
	Direction randdirr = normaldirr;
	//rotera f�rst runt infallsvinkel 
	
		// rotera runt normalen 
		randdirr.setDir( glm::normalize(glm::rotate(
			randdirr.getDir(), Inclinationangle, v3
		)));
		//rotera runt tangenten ? 
		randdirr.setDir(glm::normalize(glm::rotate(
			randdirr.getDir(), Inclinationangle, normaldirr.getDir()
		)));
		Vertex endpos(randdirr.getDir().x, randdirr.getDir().y, randdirr.getDir().z);


	return Ray(Position, endpos);
}

Ray Ray::reflection(Vertex & Postition, Direction & normaldirr)
{
	glm::vec4 newend =   glm::vec4(glm::reflect(Endpoint.getcoords()-Startpoint.getcoords(), normaldirr.getDir()),1); // +glm::vec4(Postition.getcoords(),Postition.getw()) +
	Ray r(Postition, Vertex(newend.x, newend.y, newend.z,newend.w));
	return r;
}


std::ostream & operator<<(std::ostream & os, const Ray & ray)
{
	// TODO: insert return statement here
	os <<"Startpoint :"<< ray.Startpoint << "Endpoint: "<<ray.Endpoint <<std::endl;
	return os;
}
