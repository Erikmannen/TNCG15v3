#include "Surface.h"



Surface::Surface()
{
}


Surface::~Surface()
{
}

ColorDbl Surface::Surfacereflect(Ray& rayin, Ray & rayout, Direction & normal)
{
	if (reflectionmodel == Lambertian)
		
	{
		return lamreflec();
	}
	else if (reflectionmodel == Perfect)
	{
		return Perfectreflec();
	}
	std::cout << "nomodel" << "\n";
	return ColorDbl();
}

Ray Surface::rayreflection(Ray& rayin, Vertex & Position, Direction & normal)
{
	if (reflectionmodel == Lambertian)
		
	{
		return rayin.hemisphere(Position,normal);
	}
	else if (reflectionmodel == Perfect)
	{
		return rayin.reflection(Position,normal);
	}
	std::cout << "nomodel" << "\n";
	return Ray();
}


ColorDbl Surface::lamreflec()
{
	// for perfect reflection all is conserved
	// coeff [0,1]
	return emission * coeff / M_PI;
}
ColorDbl Surface::Perfectreflec()
{
	// for perfect reflection all is conserved
	// coeff [0,1]
	return emission;
}
