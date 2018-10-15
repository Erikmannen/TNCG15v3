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
	Vertex V15(0, 0, 5);
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
	ColorDbl whitec(255, 255, 255);
	ColorDbl bc(0, 0, 200);
	ColorDbl rc(200, 0, 0);
	ColorDbl gc(0, 200, 0);
	ColorDbl cc(0, 200, 200);
	ColorDbl yc(200, 200, 0);

	Surface fin(finc);
	Surface white(whitec);
	Surface b(bc);
	Surface r(rc);
	Surface g(gc);
	Surface c(cc);
	Surface y(yc);


	// Top
	Triangle T1(V1, V13, V3, N1, white);
	Triangle T2(V3, V13, V5, N1, white);
	Triangle T3(V1, V2, V5, N1, white);
	Triangle T4(V2, V6, V5, N1, white);
	Triangle T5(V2, V4, V14, N1, white);
	Triangle T6(V4, V6, V14, N1, white);

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
	Triangle T23(V4, V6, V8, N8, y);
	Triangle T24(V6, V12, V10, N8, y);

	Trianglelist.push_back(T23);
	Trianglelist.push_back(T24);

}

ColorDbl Scene::lightcontribution(Vertex v, Direction norm)
{

	return ColorDbl();
}



std::vector<triangleintersection> Scene::rayIntersectionfortri(Ray arg)
{
	//return
	std::vector<triangleintersection> intersections;

	// for each tri in trianglelist
		for (Triangle tri : Trianglelist) {
			triangleintersection Intersector; // tri (returntype for intersectionobjects)
			glm::vec3 intersect; // to be passed into intersectionfuntion
			bool didintersect = tri.rayIntersection(arg, intersect);
			//x(t) = ps +t(pe-ps) == intersect

			if (didintersect == true) {
				Intersector.object = tri;
				Intersector.point = intersect - 0.001f*tri.getnormal().getDir();
				intersections.push_back(Intersector);
			}
		}
		
		return intersections;
}

std::vector<sphereintersection> Scene::rayIntersectionforsph(Ray arg)
{
	//return
	std::vector<sphereintersection> intersections;

	// for each sph in spherelist 		
			for (Sphere sph : Spherelist) {
				sphereintersection Intersector; // sph (returntype for intersectionobjects)
				glm::vec3 intersect; // to be passed into intersectionfuntion
				bool didintersect = sph.SphereIntersection(arg, intersect);
				//x(t) = ps +t(pe-ps) == intersect

				if (didintersect == true) {
					Intersector.object = sph;
					Intersector.point = intersect + 0.001f*sph.getnormal(Vertex(intersect.x,intersect.y,intersect.z)).getDir();
					intersections.push_back(Intersector);
				}
			}
		
		return intersections;


}
