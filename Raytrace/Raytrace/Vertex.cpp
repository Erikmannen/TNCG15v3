#include "Vertex.h"






void Vertex::Set(double Inx, double Iny, double Inz, double Inw)
{
	coords = glm::uvec3(Inx, Iny, Inz);
	w = Inw;
}


Vertex::~Vertex()
{
}

glm::vec3 Vertex::getcoords()
{
	return coords;
}

std::ostream & operator<<(std::ostream & os, const Vertex & vt)
{
	// TODO: insert return statement here
	os << '(' << vt.coords.x << ',' << vt.coords.y << ',' << vt.coords.z <<')' << ' w: '<<vt.w  << std::endl;
	return os;
}
