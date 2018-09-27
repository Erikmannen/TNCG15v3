#pragma once
#include <glm.hpp>
class Direction
{
public:
	Direction() :
		Dir(0.0, 0.0, 0.0) {};

	Direction(double x1, double y1, double z1) :
		Dir(x1, y1, z1) {};

	Direction(Direction& D) :
		Dir(D.Dir) {};

	~Direction();
	void setDir(glm::vec3 newDir) { Dir = newDir; };
	glm::vec3 getDir() { return Dir; };
private:
	glm::vec3 Dir;
};