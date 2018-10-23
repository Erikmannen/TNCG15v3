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

ColorDbl Camera::Castray(Ray & myray, Scene myscene, int depth)
{
	int close = closest(myray, myscene);
	ColorDbl returncolor(0, 0, 0);
	
	if (close == 0) {

		for (triangleintersection &intersection : myscene.rayIntersectionfortri(myray)) {
			Triangle t = intersection.object;
			Surface s = t.getsurf();
			Direction normal = t.getnormal();
			returncolor = handler(s,normal, intersection.point, myray, myscene, depth);
		}
	}
	else {
		for (sphereintersection &intersection : myscene.rayIntersectionforsph(myray)) {
			Sphere ts = intersection.object;
			Surface s = ts.getsurf();
			Vertex temppoint(intersection.point.getcoords().x, intersection.point.getcoords().y, intersection.point.getcoords().z);
			Direction normal = ts.getnormal(temppoint);
			returncolor = handler(s, normal, intersection.point,myray, myscene, depth);
		}
	}

	return returncolor;
}


ColorDbl Camera::handler(Surface surface,Direction normal,Vertex point, Ray myray, Scene myscene, int depth) {
	ColorDbl color(0, 0, 0);
	
	
	glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
	
	
	//terminate if hit a lightsource
	if (surface.modelcheck(Lightsource))
	{
		color = ColorDbl(255, 255, 255);//surface.getsurfcolor();
		 // no nned to continue for loop 
	}
	else if (surface.modelcheck(Perfect))
	{

		glm::vec4 refdirr = glm::vec4(point.getcoords(), point.getw()) + glm::vec4(glm::reflect(dirr, normal.getDir()), 1.0);
		Ray r(point, Vertex(refdirr.x, refdirr.y, refdirr.z, refdirr.w));
		//returncolor = surface.Perfectreflec() * geometric;

		color = Castray(r, myscene, depth);

	}
	else
	{

		//Ray out = surface.rayreflection(myray, intersection.point, normal);
		//double angle = glm::angle(out.getend().getcoords() - out.getstart().getcoords(), normal.getDir());
		color = color + surface.lamreflec();//*cos(angle);// *geometric;
		//ColorDbl localmodel = local(intersection.point, normal, myscene);
		//color = color * localmodel;

		if (depth < MAXDEPTH)
		{
			depth++;
			color = color + Castray(myray, myscene, depth) * surface.getcoeff();

		}


	}
	return color;

}
int Camera::closest(Ray ray , Scene myscene)
{
	//newRay.direction = CalcRandomPDFRay(intersectionNormal);
	std::list<triangleintersection> triintersections = myscene.rayIntersectionfortri(ray);
	std::vector<sphereintersection> sphintersections = myscene.rayIntersectionforsph(ray);
	float disttotri = MAXVALUE;
	float disttosph = MAXVALUE;

	// check if empty
	if (triintersections.size()) {
		disttotri = glm::distance(triintersections.front().point.getcoords(), ray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttotri : " << disttotri << std::endl;
	}
	if (sphintersections.size()) {
		disttosph = glm::distance(sphintersections.front().point.getcoords(), ray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttosph : " << disttosph << std::endl;
	}
	else if (!triintersections.size() && !sphintersections.size())
	{
		//	std::cout << "miss Ray origin : " << myray.getstart()
			//	<< "Ray end: " << myray.getend() << std::endl;
		
	}
	if (disttotri < disttosph) {
		return 0;
	}
	else {
		return 1;

		}
	return 2;// something went wrong
}

ColorDbl Camera::trihandler(triangleintersection intersection, Ray myray, Scene myscene, int depth) {
	ColorDbl color(0, 0, 0);
	Triangle t = intersection.object;
	Surface surface = t.getsurf();
	Direction normal = t.getnormal();
	glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
	double geometric = double(glm::dot(normal.getDir(), -glm::normalize(dirr)));
	//terminate if hit a lightsource
	if (surface.modelcheck(Lightsource))
	{
		color = ColorDbl(255, 255, 255);//surface.getsurfcolor();
		 // no nned to continue for loop 
	}
	else if (surface.modelcheck(Perfect))
	{

		glm::vec4 refdirr = glm::vec4(intersection.point.getcoords(), intersection.point.getw()) + glm::vec4(glm::reflect(dirr, normal.getDir()), 1.0);
		Ray r(intersection.point, Vertex(refdirr.x, refdirr.y, refdirr.z, refdirr.w));
		//returncolor = surface.Perfectreflec() * geometric;

		color = Castray(r, myscene, depth);

	}
	else
	{

		//Ray out = surface.rayreflection(myray, intersection.point, normal);
		//double angle = glm::angle(out.getend().getcoords() - out.getstart().getcoords(), normal.getDir());
		color = color + surface.lamreflec();//*cos(angle);// *geometric;
		//ColorDbl localmodel = local(intersection.point, normal, myscene);
		//color = color * localmodel;

		if (depth < MAXDEPTH)
		{
			depth++;
			color = color + Castray(myray, myscene, depth) * surface.getcoeff();

		}


	}
	return color;
}
ColorDbl Camera::spherehandler(sphereintersection sphereIntersection, Ray myray, Scene myscene, int depth) {
	ColorDbl color(0, 0, 0);
	Sphere s = sphereIntersection.object;
	Surface surface = s.getsurf();
	Vertex temppoint(sphereIntersection.point.getcoords().x, sphereIntersection.point.getcoords().y, sphereIntersection.point.getcoords().z);
	Direction normal = s.getnormal(temppoint);

	if (surface.modelcheck(Perfect))
	{
		glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
		glm::vec4 refdirr = glm::vec4(glm::reflect(dirr, normal.getDir()), 1.0);
		Ray r(sphereIntersection.point, Vertex(refdirr.x, refdirr.y, refdirr.z, refdirr.z));
		color = Castray(r, myscene, depth++); //  Castray(r,myscene,depth);

	}
	else
	{
		color = color + surface.lamreflec();
		//ColorDbl localmodel = local(sphereIntersection.point, normal, myscene);
		//color = color * localmodel;
		std::default_random_engine generator;
		std::uniform_real_distribution<float> distribution(0.0, 1);
		float uniformrand = distribution(generator);
		if (depth < MAXDEPTH)
		{
			depth++;
			color = color + Castray(myray, myscene, depth) * surface.getcoeff();

		}

	}
	return color;
}
