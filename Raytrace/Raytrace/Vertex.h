#pragma once
class Vertex
{
public:
	Vertex() : Vertex(0, 0, 0, 0) {};
	Vertex(double Inx, double Iny, double Inz,double Inw) 
		:x( Inx),y(Iny),z(Inz),w(Inw) {};
	void Set(double Inx, double Iny, double Inz, double Inw);
	Vertex(Vertex & V)
		:x(V.x),y(V.y),z(V.z),w(V.w) {};
	~Vertex();

private: 
	double x, y, z,w;
};

