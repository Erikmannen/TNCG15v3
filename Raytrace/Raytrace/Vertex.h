#pragma once
#include <iostream> 
#include <glm.hpp>
class Vertex
{
public:
	Vertex() : coords(0,0,0), w(0) {};
	Vertex(double Inx, double Iny, double Inz,double Inw) 
		:coords(Inx,Iny,Inz),w(Inw) {};
	void Set(double Inx, double Iny, double Inz, double Inw);
	Vertex(const Vertex & V)
		:coords(V.coords), w(V.w) {};
	~Vertex();
	
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vt);

private: 
	glm::vec3 coords; 
	double w;
};

