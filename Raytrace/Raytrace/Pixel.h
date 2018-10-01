#pragma once
#include "ColorDbl.h"
#include "Ray.h"
#include <vector>
class Pixel
{
public:
	Pixel()
		:pixelcolor(0.0) {};
	Pixel(ColorDbl incolor)
		:pixelcolor(incolor) {};
	Pixel(ColorDbl incolor,std::vector<Ray> inrays)
		:pixelcolor(incolor),Raylist(inrays) {};
	~Pixel();
	void setRayColor(ColorDbl newcolor) { pixelcolor = newcolor; };
	ColorDbl getRayColor();
	void addraytopixel(Ray& newray) { Raylist.push_back(newray); };
	Ray getfirstray() { return Raylist[0]; }//kanske beböver if(raylist[0]
	std::vector<Ray> &getraylist() { return Raylist; }; // retunera referens

private: 
	ColorDbl pixelcolor; 
	// reference to all rays passing through
	std::vector<Ray> Raylist;

};

