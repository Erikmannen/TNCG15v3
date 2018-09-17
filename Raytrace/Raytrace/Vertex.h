#pragma once
#include <iostream> 
class Vertex
{
public:
	Vertex() : x(0),y( 0),z( 0), w(0) {};
	Vertex(double Inx, double Iny, double Inz,double Inw) 
		:x( Inx),y(Iny),z(Inz),w(Inw) {};
	void Set(double Inx, double Iny, double Inz, double Inw);
	Vertex(const Vertex & V)
		:x(V.x),y(V.y),z(V.z),w(V.w) {};
	~Vertex();
	
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vt);

private: 
	double x, y, z, w;
};

