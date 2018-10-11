#pragma once
#include <glm.hpp>
#include "Scene.h"
#include "Pixel.h"
#include <vector>

const int WIDTH = 20;
const int HEIGHT = 20;
class Camera2
{
public:
	Camera2();
	~Camera2();
	//Renders scene connected to camera
	void render(Scene& myscene);
	Vertex getPixelPos(int h, int w, std::uniform_real_distribution<> dis, std::random_device &rd);


	//Creates image from pixel matrix
	void createImage(const std::string name, const double &max);
private: 
	Vertex pixelplane[4];
	Vertex eye1;
	Vertex eye2;
	Scene scene;
	glm::vec4 planeWidthAxis;
	glm::vec4 planeHeigthAxis;
	float pixelStep;

	std::vector<std::vector<Pixel>> pixels;

};

