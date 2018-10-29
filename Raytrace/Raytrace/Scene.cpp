#include "Scene.h"



Scene::Scene()
{
	CreateWorld();
}


Scene::~Scene()
{
}

void Scene::CreateWorld()
{
	Vertex V1(0, 6, 5);
	Vertex V2(10, 6, 5);
	Vertex V3(-3, 0, 5);
	Vertex V4(13, 0, 5);
	Vertex V5(0, -6, 5);
	Vertex V6(10, -6, 5);
	Vertex V7(0, 6, -5);
	Vertex V8(10, 6, -5);
	Vertex V9(-3, 0, -5);
	Vertex V10(13, 0, -5);
	Vertex V11(0, -6, -5);
	Vertex V12(10, -6, -5);
	Vertex V13(0, 0, 5);
	Vertex V14(10, 0, 5);
	Vertex V15(0, 0, -5);
	Vertex V16(10, 0, -5);


	Direction N1(0, 0, -1); // Top
	Direction N2(0, 0, 1); // Bottom
	Direction N3(0, 1, 0); // Front
	Direction N4(2 / sqrt(5), 1 / sqrt(5), 0); // Front left
	Direction N5(2 / sqrt(5), -1 / sqrt(5), 0); // Back left
	Direction N6(0, -1, 0); // Back
	Direction N7(-2 / sqrt(5), -1 / sqrt(5), 0); // Back right
	Direction N8(-2 / sqrt(5), 1 / sqrt(5), 0); // Front right

	ColorDbl finc(255, 0, 204);
	ColorDbl whitec(210, 210, 210);
	ColorDbl white2(220, 220, 220);
	ColorDbl bc(0, 0, 200);
	ColorDbl rc(200, 0, 0);
	ColorDbl gc(0, 200, 0);
	ColorDbl cc(0, 200, 200);
	ColorDbl yc(200, 200, 0);
	ColorDbl blackc(15, 15, 15);


	Surface fin(finc);
	Surface white(whitec);
	Surface b(bc);
	Surface r(rc);
	Surface g(gc);
	Surface c(cc,Perfect); // perfect
	Surface y(yc);
	Surface black(blackc);
	Surface Mirror(ColorDbl(0.0f), Perfect);
	Surface lights(ColorDbl(255, 255, 255), Lightsource, ColorDbl(255, 255, 255));


	// Top
	Triangle T1(V1, V13, V3, N1, white2);
	Triangle T2(V3, V13, V5, N1, white2);
	Triangle T3(V1, V2, V5, N1, lights); // tought lightsource
	Triangle T4(V2, V6, V5, N1, white2);// tought lightsource
	Triangle T5(V2, V4, V14, N1, white2);
	Triangle T6(V4, V6, V14, N1, white2);

	Trianglelist.push_back(T1);
	Trianglelist.push_back(T2);
	Trianglelist.push_back(T3);
	Trianglelist.push_back(T4);
	Trianglelist.push_back(T5);
	Trianglelist.push_back(T6);


	// Bottom
	Triangle T7(V7, V15, V9, N2, white);
	Triangle T8(V9, V15, V11, N2, white);
	Triangle T9(V7, V8, V11, N2, white); 
	Triangle T10(V8, V12, V11, N2, white);
	Triangle T11(V8, V10, V16, N2, white);
	Triangle T12(V10, V12, V16, N2, white);

	Trianglelist.push_back(T7);
	Trianglelist.push_back(T8);
	Trianglelist.push_back(T9);
	Trianglelist.push_back(T10);
	Trianglelist.push_back(T11);
	Trianglelist.push_back(T12);

	// Front _
	Triangle T13(V5, V6, V11, N3, fin);
	Triangle T14(V6, V12, V11, N3, fin);

	Trianglelist.push_back(T13);
	Trianglelist.push_back(T14);

	// Front left
	Triangle T15(V3, V5, V9, N4, b);
	Triangle T16(V5, V11, V9, N4, b);

	Trianglelist.push_back(T15);
	Trianglelist.push_back(T16);

	// Back left
	Triangle T17(V1, V3, V7, N5, r);
	Triangle T18(V3, V9, V7, N5, r);

	Trianglelist.push_back(T17);
	Trianglelist.push_back(T18);

	// Back
	Triangle T19(V1, V2, V7, N6, g);
	Triangle T20(V2, V8, V7, N6, g);

	Trianglelist.push_back(T19);
	Trianglelist.push_back(T20);

	// Back right
	Triangle T21(V2, V4, V8, N7, c);
	Triangle T22(V4, V10, V8, N7, c);

	Trianglelist.push_back(T21);
	Trianglelist.push_back(T22);

	// Front right
	Triangle T23(V4, V6, V10, N8, y);
	Triangle T24(V6, V12, V10, N8, y);

	Trianglelist.push_back(T23);
	Trianglelist.push_back(T24);
	
	//create lightsource
	//Vertex lightpos(5,0,4.5,1);
	T3.islight = true;
	light = T3; // t4 har varit go2 tester
	
	//Trianglelist.push_back(light);
	//light.push_back(lightsourcetri);
	//light.object = lightsourcetri;
	
}

ColorDbl Scene::lightcontribution(Vertex v, Direction norm)
{

	return ColorDbl();
}



std::list<triangleintersection> Scene::rayIntersectionfortri(Ray arg)
{
	//return
	std::list<triangleintersection> intersections;

	// for each tri in trianglelist
		for (Triangle tri : Trianglelist) {
			triangleintersection Intersector; // tri (returntype for intersectionobjects)
			glm::vec4 intersect; // to be passed into intersectionfuntion
			bool didintersect = tri.rayIntersection(arg, intersect);
			//x(t) = ps +t(pe-ps) == intersect

			if (didintersect == true) {
				Intersector.object = tri;
				glm::vec4 temp = glm::vec4(intersect - glm::vec4(0.001f*tri.getnormal().getDir(), 0));
				Intersector.point = Vertex(temp.x,temp.y,temp.z,temp.w);
				intersections.push_back(Intersector);
			}
		}
		/*glm::vec3 rayStart = arg.getstart().getcoords();
		intersections.sort([&rayStart]( triangleintersection &a,  triangleintersection &b) {
			
			return glm::length(a.point.getcoords() - rayStart) < glm::length(b.point.getcoords() - rayStart);
		});*/
		return intersections;
}

std::list<sphereintersection> Scene::rayIntersectionforsph(Ray arg)
{
	//return
	std::list<sphereintersection> intersections;

	// for each sph in spherelist 		
			for (Sphere sph : Spherelist) {
				sphereintersection Intersector; // sph (returntype for intersectionobjects)
				glm::vec3 intersect; // to be passed into intersectionfuntion
				bool didintersect = sph.SphereIntersection(arg, intersect);
				//x(t) = ps +t(pe-ps) == intersect

				if (didintersect == true) {
					Intersector.object = sph;
					glm::vec4 temp = glm::vec4(intersect + 0.001f*sph.getnormal(Vertex(intersect.x, intersect.y, intersect.z)).getDir(), 0);
					Intersector.point = Vertex(temp.x, temp.y, temp.z, temp.w);
					intersections.push_back(Intersector);
				}
			}
		
		return intersections;


}
/*
std::vector<Tetrahedron> Scene::rayIntersectionforstetra(Ray arg)
{
	//return
	std::vector<Tetrahedron> intersections;

	for (Tetrahedron tetra : Tetralist) {
		
		tetraintersection Intersector; // sph (returntype for intersectionobjects)
		for(Triangle tri : tetra.gettris())
		{tri.rayIntersection() }
		
	}

	return intersections;
}
*/
