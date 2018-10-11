#pragma once
#include "Triangle.h"


// a lightsource is a triangle
class Lightsource
{
public:
	Lightsource(Triangle tri = Triangle());
	~Lightsource();
};

