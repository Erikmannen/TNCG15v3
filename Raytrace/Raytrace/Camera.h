#pragma once
#include "Vertex.h"
#include "Pixel.h"

const int WIDTH = 800;
const int HEIGHT = 800;

class Camera
{
public:
	Camera();
	~Camera();
	void render();//todo
	void createImage();

private:
	//Eyepoint motsvarar Ep
	Vertex Ep1, Ep2;
	//800 x 800 array av pixels
	Pixel Img[WIDTH][HEIGHT];


};

