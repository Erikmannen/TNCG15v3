#pragma once
#include <iostream> 
#include <glm.hpp>
class Vertex
{
public:
	
	Vertex(float Inx = 0, float Iny = 0, float Inz = 0, float inw = 0)
		:coords(Inx, Iny, Inz,inw) {};
	Vertex(glm::vec3 v)
		:coords(v.x, v.y, v.z, 0) {};
	void Set(float Inx, float Iny, float Inz, float Inw) { coords.x = Inx;
	coords.y = Iny;
	coords.z = Inz;
	coords.w = Inw;
	};
	Vertex(const Vertex & V)
		:coords(V.coords) {};
	~Vertex();
	glm::vec3 getcoords() { return glm::vec3(coords.x, coords.y, coords.z);};
	double getw() {	return coords.w;};
	
	friend std::ostream& operator<<(std::ostream& os, const Vertex& vt);

private: 
	glm::vec4 coords; 
	};

