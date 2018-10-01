#pragma once
#include "Pixel.h"
#include <iostream>
#include <string>
#include <array>

const int WIDTH = 20;
const int HEIGHT = 20;

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
	Pixel Img[WIDTH][HEIGHT];
	
};

