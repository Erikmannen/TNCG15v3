#pragma once
#include "Pixel.h"
#include <iostream>
#include <string>
#include <array>
#include "Scene.h"
#include <random>
#include "Vertex.h"
#include "Surface.h"
#include <typeinfo>
#include <gtx/vector_angle.hpp>
#include <random>

const int WIDTH = 20;
const int HEIGHT = 20;
#define MAXVALUE 1e5f
const int  MAXDEPTH =  5; // hur många gånger ska de reflekterats

class Camera
{
public:
	Camera();
	~Camera();

	void render(Scene& myscene);
	void createImageFile(const std::string name, const double &max);

	Vertex getcamerapos() { return Ep1; };
	Ray* pixeltoray( int w,  int h);
	
	
	ColorDbl Castray(Ray& myray, Scene myscene,int depth);
private:
	//Eyepoint motsvarar Ep
	Vertex Ep1, Ep2;
	//800 x 800 array av pixels 
	Pixel Img[WIDTH][HEIGHT];
	int Subpixels = 1; // no divided yet
	//fov for camera
	float fov = ((float)M_PI) / 1.5f;
};

