#include "Camera.h"



Camera::Camera()
{
	Ep1.Set(-2, 0, 0,0);
	Ep2.Set(-1, 0, 0,0);
}


Camera::~Camera()
{
}

void Camera::render()
{
}

void Camera::createImage()
{
	for (int h = 0; h < HEIGHT; ++h)
		for (int w = 0; w < WIDTH; ++w)
		{
			ColorDbl def(0.0);
			Pixel myPixel(def);
			
			// Läsa subpixlar för att få fram den hela pixeln
		}
}
