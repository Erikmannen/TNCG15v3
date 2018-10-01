#include "Camera.h"

Camera::Camera()
{
	//Ep1.Set(-2, 0, 0,0);
	//Ep2.Set(-1, 0, 0,0);
}


Camera::~Camera()
{
}

void Camera::render()
{
	for (int h = 0; h < HEIGHT; ++h)
		for (int w = 0; w < WIDTH; ++w)
		{
			ColorDbl def(200);
			Pixel myPixel(def);

			Img[h][w] = def;
			// Läsa subpixlar för att få fram den hela pixeln
		}

	createImageFile("img.ppm", 200);
}

void Camera::createImageFile(const std::string name, const double &max)
{
	//std:cout << "Creating image..." << std::endl;
	FILE *fp = fopen(name.c_str(), "wb");
	(void)fprintf(fp, "P3\n%d %dn255n", WIDTH, HEIGHT, "255");
	for (auto &row : Img) 
	{
		for (Pixel &pixel : row)
		{
			ColorDbl color = pixel.getRayColor();
			std::cout << color << std::endl;

			(void)fprintf(fp, "%d %d %d ",
				(int)(color.Red),
				(int)(color.Green),
				(int)(color.Blue));

		}
	}
	(void)fclose(fp);

}