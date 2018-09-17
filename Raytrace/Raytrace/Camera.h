#pragma once
#include "Vertex.h";
#include "Pixel.h";

class Camera
{
public:
	Camera();
	~Camera();
	void render();//todo
	void createImage();

private:
	//Eyepoint motsvarar Ep
	Vertex Ep1, Ep;
	//800 x 800 array av pixels
	Pixel Img[800][800];


};

