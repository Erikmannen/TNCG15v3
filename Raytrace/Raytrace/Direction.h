#pragma once
#include <glm.hpp>
class Direction
{
public:
	Direction() :
		x(0.0), y(0.0), z(0.0) {};

	Direction(double x1, double y1, double z1) :
		x(x1), y(y1), z(z1) {};

	Direction(Direction& D) :
		x(D.x), y(D.y), z(D.z) {};

	~Direction();

private:
	double x, y, z;
};

