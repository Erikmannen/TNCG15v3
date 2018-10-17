#include "Camera.h"

Camera::Camera()
{
	Ep1 = Vertex(-2, 0, 0,1);
	Ep2 = Vertex(-1, 0, 0,1);
}


Camera::~Camera()
{
}

void Camera::render(Scene& myscene)
{
	std::cout << std::endl << " nr of tri in cam : " << myscene.trilistsize() << std::endl; 
	std::cout << std::endl << " nr of sph in cam : " << myscene.sphlistsize() << std::endl;

	double maximage = 0.0;
	// we want to cast 1 ray  per pixel 
	// for each pixel we need to add a ray as reference 
	for (int h = 0; h < HEIGHT; ++h) {
		for (int w = 0; w < WIDTH; ++w)
		{
			Pixel p(0.0);
			Ray* tempray = pixeltoray(w, h);
			//std::cout << tempray->getstart() << " -> " << tempray->getend() << std::endl;
			p.addray(*tempray);
			// borde göras i en egen loop så man kan dela upp den // todo
			//int depth = 0; // depth motsvarar reflektioner
			ColorDbl tempcolor(0.0);
			std::vector<Ray> rays = p.getraylist();
			int count = 0;
			for (Ray r : rays)
			{
			
				tempcolor = tempcolor + Castray(r, myscene);
			}
			//std::cout <<"tempcolor is : "<< tempcolor << std::endl;
			p.setPixelColor(tempcolor);
			Img[w][h] = p;
			maximage = glm::max(maximage, glm::max(tempcolor.Red, glm::max(tempcolor.Green, tempcolor.Blue)));


			/*
			Img[w][h].addray(*ray);

			ColorDbl def(200);
			Pixel myPixel(def);

			Img[h][w] = def;
			*/
		}
		
	}
	
	createImageFile("img.ppm", maximage);
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
				(int)(color.Red*255/max),
				(int)(color.Green*255/max),
				(int)(color.Blue)*255/max);

		}
	}
	(void)fclose(fp);

}
/*
Ray* Camera::pixeltoray2(int w, int h) {
	Vertex c(0,2.5,2.5);
	double aspectRatio = (double)HEIGHT / (double)WIDTH;
	double pw = w / WIDTH, ph = h / HEIGHT;
	double fovH = fov * aspectRatio;
	double radW = pw * fov - fov / 2, radH = ph * fovH - fovH / 2;
	double diffW = -sin(radW), diffH = -sin(radH);
	glm::vec3 diff(diffW, diffH, 0.0f);
	glm::vec3 lookAt = glm::normalize(glm::vec3(-0.3,-0.3,0.3) + diff);
	Vertex lookattemp(lookAt.x, lookAt.y, lookAt.z);
	Ray* ray = new Ray(c, lookattemp);
	return ray;
}
*/
Ray* Camera::pixeltoray(int w, int h)
{
	//std::cout << w << " , " << h << std::endl; 
	//send out one ray for each pixel into the scene
	// need to convert to float othervise all deltas are 0
	float deltax = 1 / (float)WIDTH;
	float deltay = 1 / (float)HEIGHT;
	//camera plane goes between (0,-1, -1) and (0,1,1) which gives
	// point of intersection through the center of pixels[r][c]

	Vertex px = Vertex(0.0f, -1.0f + (0.5f + w)*deltax, -1.0f + (0.5f + h)*deltay);
	//std::cout << "("<< px.y <<"," <<px.z << ") in camera plane ";
	//std::cout << std::endl << px.getcoords().y << ", "<<px.getcoords().z << std::endl;
	Vertex ps(-1,0,0); //user chooses wich eye to use with variable eye

	glm::vec3 D = glm::normalize(px.getcoords() - ps.getcoords()) * 1000.0f; //a vector D with length 30, intersecting pixel on its way to the eye
   // std::cout << "D: " << D.x << D.y << D.z << " ";

	Vertex pe (ps.getcoords().x+ D.x, ps.getcoords().y + D.y, ps.getcoords().z + D.z); //endpoint   //Vertex(pe.x-*D.x, pe.y-*D.y, pe.z-*D.z, 0);
	//std::cout << "ps: " << ps.x << "," << ps.y << ","<< ps.z << " \n";
	//We create a white ray with end point somewhere far in the direction D from eye point
	Ray * ray = new Ray(ps, pe, ColorDbl(1, 1, 1)); //NOTE: ray could be deallocated after function render is done
	return ray;
}

ColorDbl Camera::Castray(Ray & myray, Scene myscene, int depth)
{
	
	std::vector<triangleintersection> triintersections = myscene.rayIntersectionfortri(myray);
	std::vector<sphereintersection> sphintersections = myscene.rayIntersectionforsph(myray);
	ColorDbl returncolor(0);
	float disttotri = MAXVALUE;
	float disttosph = MAXVALUE;

	// check if empty
	if (triintersections.size()) {
		disttotri = glm::distance(triintersections.front().point.getcoords(), myray.getstart().getcoords());
		std::cout << std::endl << "disttotri : " << disttotri << std::endl;

	}
	if (sphintersections.size()) {
		disttosph = glm::distance(sphintersections.front().point.getcoords(), myray.getstart().getcoords());
		std::cout << std::endl << "disttosph : " << disttosph << std::endl;
		

	}
	else if (!triintersections.size() && !sphintersections.size())
	{
		std::cout << "miss Ray origin : " << myray.getstart()
			<< "Ray end: " << myray.getend() << std::endl;

	}
		
	if (disttotri < disttosph) {
		for (triangleintersection &intersection : triintersections) {
			Triangle t = intersection.object;
			Surface surface = t.getsurf();
			//std::cout<<std::endl << "surfcolor : " << surface.getsurfcolor();

			//terminate if hit a lightsource
			if (surface.modelcheck(Lightsource))
			{
				returncolor = surface.getsurfcolor();
				break; // no nned to continue for loop 
			}

			Direction normal = t.getnormal();
			Vertex temppoint(intersection.point.getcoords().x, intersection.point.getcoords().y, intersection.point.getcoords().z);

			Ray out = surface.rayreflection(myray, temppoint, normal);
			double angle = glm::angle(out.getend().getcoords() - out.getstart().getcoords(), normal.getDir());
			
			// se fö? 
			ColorDbl emittance = surface.Surfacereflect(myray,out,normal)* cos(angle);
			//std::cout << std::endl << "emittance : " << emittance;

			returncolor = returncolor + emittance;
			
			
			// terminate using russian roulett
			// randnrgenerator
			// uniform brdf 
			std::default_random_engine generator;
			std::uniform_real_distribution<float> distribution(0.0, 255);
			float uniformrand = distribution(generator);
			float rrTop = glm::max(glm::max(emittance.Red, emittance.Green), emittance.Blue);
			
			if (depth < MAXDEPTH || uniformrand < rrTop) {
				//perfect specular = perfect
				int nextDepth = surface.modelcheck(Perfect) ? depth : depth + 1;
				// affect probabillity
				returncolor =returncolor+(Castray(out, myscene, nextDepth) * surface.getcoeff());
				returncolor = surface.getsurfcolor();
			}
			
			break;
		}
	}
	else {
		for (sphereintersection &sphereIntersection : sphintersections) {
			Sphere s = sphereIntersection.object;
			Surface surface = s.getsurf();
			Vertex temppoint(sphereIntersection.point.getcoords().x, sphereIntersection.point.getcoords().y, sphereIntersection.point.getcoords().z);
			Direction normal = s.getnormal(temppoint);


			Ray out = surface.rayreflection(myray, temppoint, normal);
			double angle = glm::angle(out.getend().getcoords()- out.getstart().getcoords(), normal.getDir());

			ColorDbl emittance = surface.Surfacereflect(out, myray, normal);// * cos(angle);
			//ColorDbl lightContribution = scene.getLightContribution(sphereIntersection.point, normal);
			
			returncolor = returncolor + emittance;
			
		
			// terminate using russian roulett
			// randnrgenerator
			// uniform brdf 
			std::default_random_engine generator;
			std::uniform_real_distribution<float> distribution(0.0, 1.0);
			float uniformrand = distribution(generator);
			double rrTop = glm::max(glm::max(emittance.Red, emittance.Green), emittance.Blue);
			
			if (depth < MAXDEPTH || uniformrand < rrTop) {
				//perfect specular = perfect
				int nextDepth = surface.modelcheck(Perfect) ? depth : depth + 1;
				// affect probabillity
				returncolor = returncolor + (Castray(out, myscene, nextDepth) * surface.getcoeff());
			}
			break;


		}
	}
	
	return returncolor;

}
