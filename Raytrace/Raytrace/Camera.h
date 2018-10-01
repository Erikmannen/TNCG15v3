#pragma once
#include "Pixel.h"
#include <iostream>
#include <string>
#include <array>
#include <stdlib.h>
#include <stdio.h>
static const int WIDTH = 2;
static const int HEIGHT = 2;

class Camera
{
public:
	Camera();
	~Camera();
	void render();//todo
	void createImageFile(const std::string name, const double &max);

private:
	//Eyepoint motsvarar Ep
	Vertex Ep1, Ep2;
	//800 x 800 array av pixels 
	//int img[800][800];//[WIDTH][HEIGHT];
	std::array<std::array<Pixel, WIDTH>, HEIGHT> Img;
	
};

