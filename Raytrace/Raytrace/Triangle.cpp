#include "Triangle.h"



Triangle::Triangle()
{
}


Triangle::~Triangle()
{
}

void Triangle::rayIntersection(Ray arg)
{
	/*
	glm::vec3 ps = arg.getstart().getcoords();
	glm::vec3 pe = arg.getend().getcoords();
	glm::vec3 newV0 = V0.getcoords();
	glm::vec3 newV1 = V1.getcoords();
	glm::vec3 newV2 = V2.getcoords();*/
	
	
	glm::vec3 T = arg.getstart().getcoords() -V0.getcoords();
	glm::vec3 E1 = V1.getcoords() - V0.getcoords();
	glm::vec3 E2 = V2.getcoords() - V0.getcoords();
	glm::vec3 D = arg.getend().getcoords() - arg.getstart().getcoords();
	glm::vec3 P = glm::cross(D, E2);
	glm::vec3 Q = glm::cross(T, E1);
	glm::vec3 t = (Q* E2) / (P* E1);
	//glm::vec3 t = glm::dot(Q, E2) / glm::dot(P, E1);
	

		/*
		Mark fö 6
		T = ps-v0,
		E1 = v1-v0,
		E2 = v2-v0,
		D = pe-ps, 
		P = D xE2
		Q = T xE1
		t  =(Q * E2 )/(P * E1) där t är intersectionpoint
	 */

	
}
