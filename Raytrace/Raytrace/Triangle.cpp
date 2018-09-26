#include "Triangle.h"
#define MINVALUE 1e-5f
#define MAXVALUE 1e5f
Triangle::Triangle()
{
	Vertex tempvertex;
	ColorDbl tempcolor;
	V0 = V1 = V2 = tempvertex;
	trianglecolor = tempcolor;
	normal.setDir(glm::normalize(glm::cross(V0.getcoords() - V2.getcoords(), V1.getcoords() - V2.getcoords())));
}

Triangle::Triangle(Vertex V0new, Vertex V1new, Vertex V2new)
	: V0(V0new), V1(V1new), V2(V2new)
{
	ColorDbl tempcolor;
	trianglecolor = tempcolor;
	normal.setDir(glm::normalize(glm::cross(V0.getcoords() - V2.getcoords(), V1.getcoords() - V2.getcoords())));

}


Triangle::~Triangle()
{
}

Triangle::Triangle(const Triangle & tri)
{
	V0 = tri.V0;
	V1 = tri.V1;
	V2 = tri.V2;
	trianglecolor = tri.trianglecolor;
	normal = tri.normal;
}

//intersection using Möller-Trumbore algo
//return intersection point in var intersect 
//returning true if intersecting or false if not
bool Triangle::rayIntersection(Ray arg, glm::vec3& intersect)
{

	// distance of ray to vertex
	glm::vec3 T = arg.getstart().getcoords() - V0.getcoords();

	//edges
	glm::vec3 E1 = V1.getcoords() - V0.getcoords();
	glm::vec3 E2 = V2.getcoords() - V0.getcoords();
	//direction needs to be normalised 
	glm::vec3 D = glm::normalize(arg.getend().getcoords() - arg.getstart().getcoords());

	//Edge normal
	glm::vec3 P = glm::cross(D, E2);
// used in tests
	glm::vec3 Q = glm::cross(T, E1);
	//determinant
	float determinant = glm::dot(E1, P);
	

	// intersection is (t,u,v)
	float t = glm::dot(Q, E2) / determinant;
	float u = glm::dot(P, T) / determinant;
	float v = glm::dot(Q, D) / determinant;

	std::cout << "before first if" << 
		"\n"  <<"T:"<< "(" << T.x << "," << T.y << "," << T.z << ")" << 
		"\n" << "E1:" << "(" << E1.x << "," << E1.y << "," << E1.z << ")" <<
		"\n" << "E2:" << "(" << E2.x << "," << E2.y << "," << E2.z << ")" <<
		"\n" << "D:" << "(" << D.x << "," << D.y << "," << D.z << ")" <<
		"\n" << "P:" << "(" << P.x << "," << P.y << "," << P.z << ")" <<
		"\n" << "determinant:" << determinant << std::endl;


	// use u and v to determine if intersection
	// if determinant is near zero, ray lies in plane of triangle or ray is parallel to plane of triangle
	if (determinant > -MINVALUE && determinant < MINVALUE)//if (std::abs(determinant) < MINVALUE)
		return false; // no intersection

	std::cout << "passed first" << std::endl;
	// intersection lies outside of the triangle. less than 0 or greater than 1 (normalised)

	if (u < 0.f || u > 1.f)
		return false;
	std::cout << "passed 1" << std::endl;
	// The intersection lies outside of the triangle
	if (v < 0.f || u + v  > 1.f)
		return false;

	std::cout << "passed 2" << std::endl;
	//behöver antagligen fixa med interaction
	if (t > MINVALUE && t < MAXVALUE)
	{
		intersect = arg.getstart().getcoords() + t * D;
		return true;
	}

	std::cout << "passed 3" << std::endl;


	//else
	return false;




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

