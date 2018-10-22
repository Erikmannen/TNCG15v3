#include "Vertex.h"

Vertex::~Vertex()
{
}


std::ostream & operator<<(std::ostream & os, const Vertex & vt)
{
	// TODO: insert return statement here
	os << '(' << vt.coords.x << ',' << vt.coords.y << ',' << vt.coords.z<<","<<vt.coords.w <<')'   << std::endl;// << ' w: '<<vt.w
	return os;
}
