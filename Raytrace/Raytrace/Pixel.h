#pragma once
#include "ColorDbl.h"
#include "Ray.h"
#include <list>;
class Pixel
{
public:
	Pixel();
	Pixel(ColorDbl incolor)
		:pixelcolor(incolor) {};
	Pixel(ColorDbl incolor,std::list<Ray*> inrays)
		:pixelcolor(incolor),Rays(inrays) {};
	~Pixel();
private: 
	ColorDbl pixelcolor; 
	// reference to all rays passing through
	std::list<Ray*> Rays;

};

