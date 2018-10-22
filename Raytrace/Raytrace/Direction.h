#pragma once
#include <glm.hpp>
class Direction
{
public:

	Direction(double x1  = 0, double y1 = 0, double z1 = 0) :
		Dir(x1, y1, z1) {};

	Direction(const Direction & dir) :Dir(dir.Dir){};

	~Direction();
	void setDir(glm::vec3 newDir) { Dir = newDir; };
	glm::vec3 getDir() { return Dir; };
private:
	glm::vec3 Dir;
};