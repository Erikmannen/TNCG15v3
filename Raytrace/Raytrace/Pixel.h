#pragma once
#include "ColorDbl.h"
#include "Ray.h"
#include <vector>
class Pixel
{
public:
	Pixel();
	Pixel(ColorDbl incolor)
		:pixelcolor(incolor) {};
	Pixel(ColorDbl incolor,std::vector<Ray> inrays)
		:pixelcolor(incolor),Raylist(inrays) {};
	~Pixel();
private: 
	ColorDbl pixelcolor; 
	// reference to all rays passing through
	std::vector<Ray> Raylist;

};

