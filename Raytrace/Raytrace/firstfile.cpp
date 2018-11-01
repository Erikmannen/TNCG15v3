#include <iostream> 
#include <glm.hpp>
#include "Ray.h"
#include "Triangle.h"
#include "Scene.h"
#include "Camera.h"

using namespace std;

void dispintersection(Triangle & tri, Ray& ray)
{
	glm::vec4 t = glm::vec4(0.0);
	bool intersection = tri.rayIntersection(ray, t);
	if (intersection == true)
		cout << "ray intersected" << endl;
	else
		cout << "did not interesect" << endl;
	cout << "(" << t.x << "," << t.y << "," << t.z << ")" << endl;
}
void testtri()
{
	Triangle t(
		Vertex(-1.0f, 0.5f, 0.0f),
		Vertex(-1.0f, 0.0f, 1.0f),
		Vertex(-1.0f, -0.5f, 0.0f));

	Ray r(
		Vertex(0.0f, 0.0f, 0.0f),
		Vertex(-2.0f, 0.0f, 0.0f));

	cout << endl << "test 1 - Hit expected" << endl;
	glm::vec4  tOut(0,0,0,0);
	bool intersected = false;
	intersected = t.rayIntersection(r, tOut);
	if (intersected == true)
		cout << "hit1" << endl;
	else
		cout << "miss1" << endl;
	
	cout << endl << "test 2 - Hit not expected " << endl;
	Ray r2(
		Vertex(0.0f, 0.0f, 0.0f),
		Vertex(-1.0f, 0.49f, 0.0f));

	tOut = glm::vec4(0,0,0,0);
	intersected = false;
	intersected = t.rayIntersection(r2, tOut);
	if (intersected == true)
		cout << "hit2" << endl;
	else
		cout << "miss2" << endl;

	Ray r3(
		Vertex(0.0f, 0.0f, 0.0f),
		Vertex(1.0f, 0.49f, 0.0f));
	cout<< endl << "test 3  - Hit not expected" <<endl;

	tOut = glm::vec4(0, 0, 0, 0);
	intersected = false;
	intersected = t.rayIntersection(r3, tOut);
	if (intersected == true)
		cout << "hit3 " << endl;
	else
		cout << "miss3" << endl;

}

void testsph()
{
	// pos radius surface
	Vertex pos1(-5, 0, 0);
	Vertex pos2(-5, 0, 0);
	float radius1 = 1;
	float radius2 = 2;

	Sphere s1(pos1, radius1);
	Sphere s2(pos1, radius2);

	//Sphere s(1.0f, glm::vec3(-5.0f, 0.0f, 0.0f), new Surface(ColorDbl(0.0)));
//	Sphere s2(2.0f, glm::vec3(-5.0f, 0.0f, 0.0f), new Surface(ColorDbl(0.0));
	
	Vertex v; 
	Vertex u(1, 0, 0);
	Ray r(u,v);

	//float tOut = 0;
	bool intersected = false;
	glm::vec3 tout(0, 0, 0);
	intersected = s1.SphereIntersection(r, tout);

	std::cout << endl<< "test sph1- should be 4" << endl;
	if (intersected == true)
		std::cout << "hit sph" << endl;
	else
		std::cout << " miss sph" << endl;
	cout << "(" << tout.x << "," << tout.y << "," << tout.z << ")" << endl;

	//EXPECT_TRUE(intersected) << "Intersection with sphere expected";
	//EXPECT_FLOAT_EQ(tOut, 4.0f) << "distance to sphere should be 4";

	std::cout << endl << "test sph1- should be ?" << endl;
	
	tout = glm::vec3(0,0,0);
	intersected = false;
	intersected = s2.SphereIntersection(r, tout);
	if (intersected == true)
		std::cout << "hit sph2" << endl;
	else
		std::cout << " miss sph2" << endl;
	cout << "(" << tout.x << "," << tout.y << "," << tout.z << ")" << endl;

	
	
}

int main()
{
	cout << "hello world" << endl;
	glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);

	Ray myray;
	cout << Position.x << endl;
	cout << myray << endl;
	cout << "break" << endl;
	cout << myray.getstart().getcoords()[1] << endl;
	Ray ri = Ray(Vertex(0.0f, 0.0f, 0.0f), Vertex(0.0f, 1.0f, 0.0f));
	Ray rj = Ray(Vertex(0.0f, 0.0f, 0.0f), Vertex(0.0f, 1.0f, 0.0f));
	
	
	Ray r(Vertex(0.0f, 0.0f, 0.0f),Vertex(0.0f, 1.0f, 0.0f));
	cout << r 
		<<"riktiga start :  (0.0f, 0.0f, 0.0f) " <<"\n"<<
		 "riktiga end : (0.0f, 1.0f, 0.0f)" << endl;

	Ray r1(Vertex(0.0f, 0.0f, 0.0f), Vertex(4.0f, 0.0f, 2.0f));
	cout << r1
		<< "riktiga start :  (0.0f, 0.0f, 0.0f) " << "\n" <<
		"riktiga end : (4.0f, 0.0f, 2.0f)" << endl;
	//wont intersect with r but with r1
	Triangle mytri(Vertex(2.0f, 5.0f, 2.0f),
				   Vertex(2.0f, -5.0f, 2.0f),
				   Vertex(4.0f, 0.0f, 2.0f));
	
	//testraytriangleintersection();
	
	dispintersection(mytri, r);
	cout << "\n\n";
	dispintersection(mytri, r1);

	testtri();
	testsph();
	Scene scene;
	std::cout << scene.trilistsize() << endl;
	Vertex pos1(-5, 0, 0);
	Vertex pos2(-5, 0, 0);
	double radius1 = 1;
	double radius2 = 2;

	Sphere s1(pos1, radius1);
	Sphere s2(pos1, radius2);

	scene.addsph(s1);
	scene.addsph(s2);
	auto list = scene.gettrilist();
	for (Triangle& i : list)
	{
		std::cout << i.getsurf().getsurfcolor() << ' ';
	}	
	Scene scen2;
	Camera cam;
	Sphere sph(Vertex(8,-3,-3),1.0f,Surface(ColorDbl(204,102,102),Lambertian));
	scen2.addsph(sph);
	for (Triangle tri : scen2.gettrilist())
	{
		if(tri.getsurf().modelcheck(Perfect))
		{
			cout << "true " << endl;
		}
	}
	Tetrahedron tetra(Vertex(10, 0, -5, 0), Vertex(11, 1, -5, 0), Vertex(12, 0, -5, 0), Vertex(11, 1.5, -2, 0), Surface(ColorDbl(20,200,0), Lambertian));
	scen2.addtetra(tetra);


	cam.render(scen2);
	while (true)
	{

	}
	

	return 0;
}

