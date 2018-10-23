#include "Camera.h"

Camera::Camera()
{
	Ep1 = Vertex(-1, 0, 0,1);
	Ep2 = Vertex(-2, 0, 0,1);

	pixelplane[0] = glm::vec4(0.0f, 1.0f, 1.0f, 1.0f);
	pixelplane[1] = glm::vec4(0.0f, -1.0f, 1.0f, 1.0f);
	pixelplane[2] = glm::vec4(0.0f, 1.0f, -1.0f, 1.0f);
	pixelplane[3] = glm::vec4(0.0f, -1.0f, -1.0f, 1.0f);
	planeWidthAxis = (pixelplane[1] - pixelplane[0]);
	planeHeigthAxis = (pixelplane[2] - pixelplane[0]);

	pixelStep = glm::length(planeHeigthAxis) / HEIGHT;

	planeWidthAxis = glm::normalize(planeWidthAxis);
	planeHeigthAxis = glm::normalize(planeHeigthAxis);
}


Camera::~Camera()
{
}

void Camera::render(Scene& myscene)
{
	std::cout << std::endl << " nr of tri in cam : " << myscene.trilistsize() << std::endl; 
	std::cout << std::endl << " nr of sph in cam : " << myscene.sphlistsize() << std::endl;

	double maximage = 0.0;
	setuppixels();
	maximage = rays(myscene);		

	createImageFile("img.ppm", maximage);
}


void Camera::setuppixels() {
	
	// we want to cast 1 ray  per pixel 
	// for each pixel we need to add a ray as reference 
	for (int h = 0; h < HEIGHT; ++h) {
		for (int w = 0; w < WIDTH; ++w)
		{

			Img[h][w].setPixelColor(ColorDbl());
			Ray* tempray = pixeltoray2(w, h);
			//std::cout << tempray->getstart() << " -> " << tempray->getend() << std::endl;
			Img[h][w].addray(*tempray);
		
		}
	}
}

double Camera::rays(Scene& myscene) {
	double maximage = 0.0; // to check max intensity
	
	for (int h = 0; h < HEIGHT; ++h) {
		for (int w = 0; w < WIDTH; ++w)
		{
	
			ColorDbl tempcolor(0.0);
			std::vector<Ray> rays = Img[h][w].getraylist();
			for (Ray r : rays)
			{
				tempcolor = tempcolor + Castray(r, myscene);
			}
			Img[h][w].setPixelColor(tempcolor);
			maximage = glm::max(maximage, glm::max(tempcolor.Red, glm::max(tempcolor.Green, tempcolor.Blue)));

		}
	}
	return maximage;
}

ColorDbl Camera::shadowrays(Vertex intersection, Direction norm, Scene myscene)
{
	double area = 0; 
	ColorDbl returncolor(0,0,0);
	for (Triangle& light : myscene.getlights())
	{
		std::vector<Vertex> edges = light.getvertex();
		area = area + 0.5 * glm::length(glm::cross(edges[0].getcoords(), edges[1].getcoords()));
		for (int i = 0; i < SHADOWRAYS; i++)
		{


		}

	}

	return returncolor;
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
			ColorDbl color = pixel.getPixelColor();
		std::cout << color << std::endl;

			(void)fprintf(fp, "%d %d %d ",
				(int)(color.Red),
				(int)(color.Green),
				(int)(color.Blue));
			/*
			(void)fprintf(fp, "%d %d %d ",
				(int)(color.Red*255/max),
				(int)(color.Green*255/max),
				(int)(color.Blue)*255/max);
				*/
		}
	}
	
	(void)fclose(fp);

}

Ray* Camera::pixeltoray2(int w, int h) {
	
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, pixelStep);

	
	std::mt19937 gen1(rd());
	auto samplePos = static_cast<float>(dis(rd));
	glm::vec4 pixelPos = pixelplane[0] + (planeWidthAxis * ((w+1) * pixelStep - samplePos));
	pixelPos += planeHeigthAxis * ((h+1) * pixelStep - samplePos);

	Ray* r = new Ray(Ep1,Vertex(pixelPos.x, pixelPos.y, pixelPos.z, pixelPos.w),ColorDbl(1,1,1));
	return r;

}

Ray* Camera::pixeltoray(int w, int h)
{
	//std::cout << w << " , " << h << std::endl; 
	//send out one ray for each pixel into the scene
	// need to convert to float othervise all deltas are 0
	float deltax = w / (float)WIDTH;
	float deltay = h / (float)HEIGHT;
	//camera plane goes between (0,-1, -1) and (0,1,1) which gives
	// point of intersection through the center of pixels[r][c]

	double aspect = (double)WIDTH / (double)HEIGHT;
	double fovH = fov * aspect;
	double radW = deltax * fov - fov / 2, radH = deltay * fovH - fovH / 2;
	double diffW = -sin(radW), diffH = -sin(radH);

	glm::vec3 diff(diffW, diffH, 0.0f);
	glm::vec3 lookAt = glm::normalize(Ep2.getcoords() + diff);

	Vertex End(lookAt.x, lookAt.y, lookAt.z);

	Vertex px = Vertex(0.0f, -1.0f + (0.5f + w)*deltax, -1.0f + (0.5f + h)*deltay);
	//std::cout << "("<< px.y <<"," <<px.z << ") in camera plane ";
	//std::cout << std::endl << px.getcoords().y << ", "<<px.getcoords().z << std::endl;
	Vertex ps(-2,0,0); //user chooses wich eye to use with variable eye

	glm::vec3 D = glm::normalize(px.getcoords() - ps.getcoords()) * 1000.0f; //a vector D with length 30, intersecting pixel on its way to the eye
   // std::cout << "D: " << D.x << D.y << D.z << " ";

	Vertex pe (ps.getcoords().x+ D.x, ps.getcoords().y + D.y, ps.getcoords().z + D.z); //endpoint   //Vertex(pe.x-*D.x, pe.y-*D.y, pe.z-*D.z, 0);
	//std::cout << "ps: " << ps.x << "," << ps.y << ","<< ps.z << " \n";
	//We create a white ray with end point somewhere far in the direction D from eye point
	Ray * ray = new Ray(ps, End, ColorDbl(1, 1, 1)); //NOTE: ray could be deallocated after function render is done
	return ray;
}

ColorDbl Camera::Castray(Ray & myray, Scene myscene, int depth)
{
	
	std::list<triangleintersection> triintersections = myscene.rayIntersectionfortri(myray);
	std::vector<sphereintersection> sphintersections = myscene.rayIntersectionforsph(myray);
	
	ColorDbl returncolor(0);
	float disttotri = MAXVALUE;
	float disttosph = MAXVALUE;

	// check if empty
	if (triintersections.size()) {
		disttotri = glm::distance(triintersections.front().point.getcoords(), myray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttotri : " << disttotri << std::endl;

	}
	if (sphintersections.size()) {
		disttosph = glm::distance(sphintersections.front().point.getcoords(), myray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttosph : " << disttosph << std::endl;
		

	}
	else if (!triintersections.size() && !sphintersections.size())
	{
	//	std::cout << "miss Ray origin : " << myray.getstart()
		//	<< "Ray end: " << myray.getend() << std::endl;

	}
		
	if (disttotri < disttosph) {
		for (triangleintersection &intersection : triintersections) {
			Triangle t = intersection.object;
			Surface surface = t.getsurf();
			Direction normal = t.getnormal();
			glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
			double geometric = double(glm::dot(normal.getDir(), -glm::normalize(dirr)));
			//terminate if hit a lightsource
			if (surface.modelcheck(Lightsource))
			{
				returncolor = surface.getsurfcolor();
				break; // no nned to continue for loop 
			}
			else if (surface.modelcheck(Perfect))
			{
				
				glm::vec4 refdirr = glm::vec4(glm::reflect(dirr, normal.getDir()), 1.0);
				Ray r(intersection.point, Vertex(refdirr.x, refdirr.y, refdirr.z, refdirr.z));
				//returncolor = surface.Perfectreflec() * geometric;
				return Castray(r, myscene, depth);

			}
			else
			{
				if (depth < MAXDEPTH)
				{
				
					returncolor = surface.lamreflec();// *geometric;

				}
			}
				/*


				Ray out = surface.rayreflection(myray, intersection.point, normal);
				double angle = glm::angle(out.getend().getcoords() - out.getstart().getcoords(), normal.getDir());

				// se fö? 
				ColorDbl emittance = surface.Surfacereflect(myray, out, normal)* cos(angle);
				//std::cout << std::endl << "emittance : " << emittance;

				returncolor = returncolor + emittance;


				// terminate using russian roulett
				// randnrgenerator
				// uniform brdf 
				std::default_random_engine generator;
				std::uniform_real_distribution<float> distribution(0.0, 255);
				float uniformrand = distribution(generator);
				float rrTop = glm::max(glm::max(emittance.Red, emittance.Green), emittance.Blue);

				if (depth < MAXDEPTH) {
					//perfect specular = perfect
					int nextDepth = surface.modelcheck(Perfect) ? depth : depth + 1;
					// affect probabillity
					returncolor = returncolor + (Castray(out, myscene, nextDepth) * surface.getcoeff());
					//returncolor = surface.getsurfcolor(); // todo remove once fov fixed
				}
			}
			break;
				*/
		}
	}
	else {
		for (sphereintersection &sphereIntersection : sphintersections) {
			Sphere s = sphereIntersection.object;
			Surface surface = s.getsurf();
			Vertex temppoint(sphereIntersection.point.getcoords().x, sphereIntersection.point.getcoords().y, sphereIntersection.point.getcoords().z);
			Direction normal = s.getnormal(temppoint);

			if (surface.modelcheck(Perfect))
			{
				glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
				glm::vec4 refdirr = glm::vec4(glm::reflect(dirr, normal.getDir()), 1.0);
				Ray r(sphereIntersection.point, Vertex(refdirr.x, refdirr.y, refdirr.z, refdirr.z));
				returncolor = Castray(r, myscene, depth); //  Castray(r,myscene,depth);

			}
			else
			{
				if (depth < MAXDEPTH)
					returncolor = surface.lamreflec();
				/*
				 
				 
				 

				Ray out = surface.rayreflection(myray, temppoint, normal);
				double angle = glm::angle(out.getend().getcoords() - out.getstart().getcoords(), normal.getDir());

				ColorDbl emittance = surface.Surfacereflect(out, myray, normal);// * cos(angle);
				//ColorDbl lightContribution = scene.getLightContribution(sphereIntersection.point, normal);

				returncolor = returncolor + emittance;


				// terminate using russian roulett
				// randnrgenerator
				// uniform brdf 
				std::default_random_engine generator;
				std::uniform_real_distribution<float> distribution(0.0, 255);
				float uniformrand = distribution(generator);
				double rrTop = glm::max(glm::max(emittance.Red, emittance.Green), emittance.Blue);

				if (depth < MAXDEPTH) {
					//perfect specular = perfect
					int nextDepth = surface.modelcheck(Perfect) ? depth : depth + 1;
					// affect probabillity
					returncolor = returncolor + (Castray(out, myscene, nextDepth) * surface.getcoeff());
				}
				break;
				 */
			}

		}
	}
	
	return returncolor;

}
