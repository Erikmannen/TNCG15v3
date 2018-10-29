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

const int WIDTH = 200;
const int HEIGHT = 200;
#define MAXVALUE 1e5f
const int  MAXDEPTH =  2; // will create artefacts  
const int SHADOWRAYS = 2;

class Camera
{
public:
	Camera();
	~Camera();
	void render(Scene& myscene);//todo
	void createImageFile(const std::string name, const double &max);
	
	Vertex getcamerapos() { return Ep1; };
	
	Ray* pixeltoray( int w,  int h);
	Ray* pixeltoray2( int w,  int h);
	void setuppixels();
	double rays(Scene& myscene);
	
	
	ColorDbl Castray(Ray& myray, Scene myscene,int depth  = 0);
	ColorDbl Castray2(Ray& myray, Scene myscene,int depth  = 0);
private:
	
	ColorDbl handler(Surface surface ,Direction normal, Vertex point, Ray myray, Scene myscene, int depth);
	ColorDbl handler2(Surface surface ,Direction normal, Vertex point, Ray myray, Scene myscene, int depth);
	ColorDbl handler3(Surface surface ,Direction normal, Vertex point, Ray myray, Scene myscene, int depth);
	
	int closest(Ray ray, Scene myscene);
	ColorDbl shadow(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene, ColorDbl color);
	
	Ray sampleShadowray(Vertex fromPoint, Scene myscene);

	ColorDbl direct(Vertex point , Scene myscene,Direction normal);
	ColorDbl indirect(Surface s,Vertex point, Scene myscene, Direction normal,int depth);
	ColorDbl direct2(Vertex point , Scene myscene,Direction normal, glm::vec3 objNormal, ColorDbl color,ColorDbl brdf);

	ColorDbl dirrrad(Vertex point, Surface s, Direction normal, Scene myscne);
	ColorDbl indirrrad(Vertex point, Surface s, Direction normal);
	glm::vec3 CalcRandomPDFRay(glm::vec3 &normal);
	//Eyepos motsvarar Ep
	Vertex Ep1, Ep2;
	Direction upDir;
	Direction dir;
	//800 x 800 array av pixels 
	Pixel Img[WIDTH][HEIGHT];
	int Subpixels = 1; // no divided yet
	//fov for camera
	float fov = ((float)M_PI) / 1.5f;
	glm::vec4 pixelplane[4];
	glm::vec4 planeWidthAxis;
	glm::vec4 planeHeigthAxis;
	float pixelStep;
	
};

