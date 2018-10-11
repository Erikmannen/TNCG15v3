#include "Camera2.h"



Camera2::Camera2()
{
	pixels.resize(HEIGHT, std::vector<Pixel>(WIDTH, Pixel()));

	pixelplane[0] = Vertex(0.0f, 1.0f, 1.0f, 1.0f);
	pixelplane[1] = Vertex(0.0f, -1.0f, 1.0f, 1.0f);
	pixelplane[2] = Vertex(0.0f, 1.0f, -1.0f, 1.0f);
	pixelplane[3] = Vertex(0.0f, -1.0f, -1.0f, 1.0f);
	Vertex diff10(pixelplane[1].getcoords().x - pixelplane[0].getcoords().x,
		pixelplane[1].getcoords().y - pixelplane[0].getcoords().y,
		pixelplane[1].getcoords().z - pixelplane[0].getcoords().z,
		pixelplane[1].getw() - pixelplane[0].getw());
	Vertex diff20(pixelplane[2].getcoords().x - pixelplane[0].getcoords().x,
		pixelplane[2].getcoords().y - pixelplane[0].getcoords().y,
		pixelplane[2].getcoords().z - pixelplane[0].getcoords().z,
		pixelplane[2].getw() - pixelplane[0].getw());

	planeWidthAxis = glm::vec4(diff10.getcoords(),diff10.getw());
	planeHeigthAxis = glm::vec4(diff20.getcoords(), diff20.getw());

	pixelStep = glm::length(planeHeigthAxis) / (float)HEIGHT;

	planeWidthAxis = glm::normalize(planeWidthAxis);
	planeHeigthAxis = glm::normalize(planeHeigthAxis);

	eye1 = Vertex(-1.0, 0.0, 0.0, 1.0);
	eye2 = Vertex(-2.0, 0.0, 0.0, 1.0);

}


Camera2::~Camera2()
{
}

void Camera2::render(Scene & myscene)
{
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::default_random_engine gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, pixelStep);
	for (int h = 0; h < HEIGHT; ++h)
	{
		for (int w = 0; w < WIDTH; ++w)
		{
			for (auto &r : pixels[h][w].getraylist()) {
				r = Ray(eye1, getPixelPos(h + 1, w + 1, dis, rd));
			}
		}
	}
	for (int h = 0; h < HEIGHT; ++h)
	{
		for (int w = 0; w < WIDTH; ++w)
		{
			for (auto &ray : pixels[w][h].getraylist())
			{
			}
				//ray.setraycolor( createRayPath(ray));
		}
	}
}



Vertex Camera2::getPixelPos(int h, int w, std::uniform_real_distribution<> dis, std::random_device & rd)
{
	std::default_random_engine gen(rd());
	auto samplePos = static_cast<float>(dis(rd));
	Vertex tempwidth(planeWidthAxis.x, planeWidthAxis.y, planeWidthAxis.z, planeWidthAxis.w);

	Vertex pixelPos(pixelplane[0].getcoords().x + (tempwidth.getcoords().x * (w * pixelStep - samplePos)),
		pixelplane[0].getcoords().y + (tempwidth.getcoords().y * (w * pixelStep - samplePos)),
		pixelplane[0].getcoords().z + (tempwidth.getcoords().z * (w * pixelStep - samplePos)),
		pixelplane[0].getw()- tempwidth.getw());
	Vertex tempheight(planeHeigthAxis.x*(h * pixelStep - samplePos), planeHeigthAxis.y*(h * pixelStep - samplePos), planeHeigthAxis.z*(h * pixelStep - samplePos), planeHeigthAxis.w*(h * pixelStep - samplePos));

	pixelPos.Set(pixelPos.getcoords().x + tempheight.getcoords().x,
		pixelPos.getcoords().y + tempheight.getcoords().y,
		pixelPos.getcoords().z + tempheight.getcoords().z,
		pixelPos.getw() + tempheight.getw());
		//planeHeigthAxis * (h * pixelStep - samplePos);
	return pixelPos;
	
}
