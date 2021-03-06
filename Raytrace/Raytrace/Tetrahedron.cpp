#include "Tetrahedron.h"


Tetrahedron::Tetrahedron()
:bot(Vertex(0,0,0)), left(Vertex(0, 0, 0)), right(Vertex(0, 0, 0)), top(Vertex(0, 0, 0)), tetrasurf(Surface())
{
}

Tetrahedron::Tetrahedron(Vertex inbot, Vertex inleft, Vertex inright, Vertex intop, Surface insurf)
	: bot(inbot) , left(inleft) , right(inright) , top(intop), tetrasurf(insurf)
{
	// kryss 0 -2 och 1 -2
	// v0 = top , v1 = left , v2 = right v3 = bot
	glm::vec3 normal0 = (glm::normalize(glm::cross(top.getcoords() - right.getcoords(), left.getcoords() - right.getcoords())));
	glm::vec3 normal1 = (glm::normalize(glm::cross(top.getcoords() - right.getcoords(), bot.getcoords() - right.getcoords())));
	glm::vec3 normal2 = (glm::normalize(glm::cross(top.getcoords() - bot.getcoords(), left.getcoords() - bot.getcoords())));
	glm::vec3 normal3 = (glm::normalize(glm::cross(bot.getcoords() - left.getcoords(), right.getcoords() - left.getcoords())));

	Direction nom0(normal0.x, normal0.y, normal0.z);
	Direction nom1(normal1.x, normal1.y, normal1.z);
	Direction nom2(normal2.x, normal2.y, normal2.z);
	Direction nom3(normal3.x, normal3.y, normal3.z);
	std::cout << nom0.getDir().x<<","<< nom0.getDir().y<< nom0.getDir().z << "\n";
	std::cout << nom1.getDir().x<<","<< nom1.getDir().y<< nom1.getDir().z << "\n";
	std::cout << nom2.getDir().x<<","<< nom2.getDir().y<< nom2.getDir().z << "\n";
	std::cout << nom3.getDir().x<<","<< nom3.getDir().y<< nom3.getDir().z << "\n";

	std::cout << tetrasurf.getsurfcolor()<< "\n";

	tris.push_back( Triangle(right, top, left, nom0, tetrasurf));
	tris.push_back(Triangle(right, top, bot, nom1, tetrasurf));
	tris.push_back(Triangle(bot, top, left, nom2, tetrasurf));
	tris.push_back(Triangle(left, bot, right, nom3, tetrasurf));

}

bool Tetrahedron::tetraIntersection(Ray arg, glm::vec4 & intersect)
{
	if (tris[0].rayIntersection(arg,intersect) || tris[1].rayIntersection(arg, intersect) || tris[2].rayIntersection(arg, intersect) || tris[3].rayIntersection(arg, intersect))
		return true;
	return false;

}

