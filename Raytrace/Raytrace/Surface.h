#pragma once
#include "Ray.h"
#include "Vertex.h"
#include "ColorDbl.h"
const int Lambertian = 0;
const int Perfect = 1;
const int Lightsource = 2; 

class Surface
{
public:
	
	Surface(ColorDbl insurfcolor = ColorDbl(0.0), const int model = Lambertian,ColorDbl em = ColorDbl(0.0)) : surfacecolor(insurfcolor), reflectionmodel(model){
		if (model == Lightsource)
		{
			emission = ColorDbl(255,255,255);// set emission if lightsource 
		}
	};
	~Surface();
	
	ColorDbl Surfacereflect(Ray& rayin,Ray& rayout,Direction& normal);
	Ray rayreflection(Ray& rayin,Vertex& Position, Direction& normal);

	ColorDbl lamreflec();
	ColorDbl Perfectreflec();

	bool modelcheck(const int in) { return in == reflectionmodel; };
	
	double getcoeff() { return coeff; };
	ColorDbl getsurfcolor() { return surfacecolor; };
	ColorDbl getemission() {
		return emission;
	};

	void setsurf(ColorDbl incolor,int model= Lambertian) { surfacecolor = incolor;
	reflectionmodel = model;};
	
private:
	ColorDbl surfacecolor;
	int reflectionmodel; // for grade 3
	ColorDbl emission;
									  //emission , absorption 
	// coefficient coeff needs to be between [0,1] not sure how to chose it
	double coeff = 0.7;
	
	//reflection model? 

};

