#pragma once
#include "Ray.h"
#include "Vertex.h"
#include "ColorDbl.h"
const int Lambertian = 0;
const int Perfect = 1;
const int reflextioncoff = 2;
const int Lightsource = 3; 
//const int Perfect = 1;
class Surface
{
public:
	
	Surface(ColorDbl insurfcolor = ColorDbl(0.0), const int model = Lambertian) : surfacecolor(insurfcolor), reflectionmodel(model){
		if (model == Lightsource)
		{
			emission = ColorDbl(0, 0, 0);// set emission if lightsource 
		}
	};
	~Surface();
	ColorDbl getsurfcolor() { return surfacecolor; };
	ColorDbl Surfacereflect(Ray& rayin,Ray& rayout,Direction& normal);
	Ray rayreflection(Ray& rayin,Vertex& Position, Direction& normal);
	ColorDbl lamreflec();
	ColorDbl Perfectreflec();
	bool modelcheck(const int in) { return in == reflectionmodel; };
	double getcoeff() { return coeff; };

private:
	ColorDbl surfacecolor;
	int reflectionmodel = Lambertian; // for grade 3
	ColorDbl emission = ColorDbl(0.0);
									  //emission , absorption 
	// coefficient coeff needs to be between [0,1] not sure how to chose it
	double coeff = 0.7;
	
	//reflection model? 

};

