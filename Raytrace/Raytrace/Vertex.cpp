#include "Vertex.h"






void Vertex::Set(double Inx, double Iny, double Inz, double Inw)
{
	x = Inx;
	y = Iny;
	z = Inz;
	w = Inw;
}


Vertex::~Vertex()
{
}

std::ostream & operator<<(std::ostream & os, const Vertex & vt)
{
	// TODO: insert return statement here
	os << '(' << vt.x << ',' << vt.y << ',' << vt.z <<',' <<vt.w << ')' << std::endl;
	return os;
}
