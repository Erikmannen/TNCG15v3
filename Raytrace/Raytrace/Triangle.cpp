#include "Triangle.h"
#define EPSILON 0.00000000000000001
#define MAXVALUE 1000000000000000

Triangle::Triangle()
{

}


Triangle::~Triangle()
{
}


//intersection using Möller-Trumbore algo
//return intersection point if got 1 else returns 0
//returning t if found using u and v to determine if inbound
double Triangle::rayIntersection(Ray arg)
{

	// distance of ray to vertex
	glm::vec3 T = arg.getstart().getcoords() -V0.getcoords();
	
	//edges
	glm::vec3 E1 = V1.getcoords() - V0.getcoords();
	glm::vec3 E2 = V2.getcoords() - V0.getcoords();
	//direction needs to be normalised 
	glm::vec3 D = glm::normalize(arg.getend().getcoords() - arg.getstart().getcoords());
	
	//Edge normal
	glm::vec3 P = glm::cross(D, E2);
	//determinant
	double determinant = glm::dot(E1, P);
	// used in tests
	glm::vec3 Q = glm::cross(T, E1);
	
	// intersection is (t,u,v)
	double t = glm::dot(Q, E2) / determinant;
	double u = glm::dot(P , T) / determinant;
	double v = glm::dot(Q , D) / determinant;
	
	// use u and v to determine if intersection
	// if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
	if (std::abs(determinant) < EPSILON)
		return 0; // no intersection
	
	// intersection lies outside of the triangle. less than 0 or greater than 1 (normalised)

	if (u < 0.f || u > 1.f)
		return 0;

	// The intersection lies outside of the triangle
	if (v < 0.f ||u +v  > 1.f)
		return 0;

	//behöver antagligen fixa med interaction
	if (t > EPSILON && t < MAXVALUE)
		return t;


	//else
	return 0;


	
	
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
