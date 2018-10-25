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
	int counter = 0;
	for (int h = 0; h < HEIGHT; ++h) {
		counter++;
		std::cout << counter << "\n";
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
				(int)(color.Green ),
				(int)(color.Blue ));
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
	
	glm::vec4 intersectpoint = glm::vec4(0.0, 0.0, 0.0, -1.0f);
	float intersectdistance;
	ColorDbl brdf = surface.getsurfcolor(); // type o color

	glm::vec3 objNormal = normal.getDir();
	if (closest(myray, myscene) == 2) {
		std::cout << "firstif";
		return ColorDbl(0);

	}
		
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);

	if(surface.modelcheck(Lambertian)) {
		

		std::uniform_real_distribution<> disAngle(0.0, M_PI);

		double incOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.z)),
			glm::normalize(glm::vec2(0.0, 1.0)));
		double asiOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.y)),
			glm::normalize(glm::vec2(0.0, 1.0)));
		double randAsi = 2.0 * disAngle(rd);
		double randInc = disAngle(rd);
		glm::vec4 reflDir = glm::vec4(cos(randAsi + asiOffset),
			sin(randAsi + asiOffset),
			cos(randInc + incOffset), 1.0);
		glm::vec4 temp = glm::vec4(point.getcoords(),point.getw() ) + reflDir;
		Ray reflRay = Ray(point, Vertex(temp.x, temp.y, temp.z, temp.w));
		
		ColorDbl color= surface.lamreflec();
	
		if (dis(gen) > 0.5 ) {
			//color = surface.lamreflec();
			color = Castray(reflRay,myscene,depth);
			color = color * 0.3;
			
			//color = surface.getsurfcolor();// todo ta bort
			
		}
		
		glm::vec4 shadowIntersect;
		float shadowDistance = MAXVALUE;
		ColorDbl brdfDummy;
		glm::vec3 dummyNormal;
		for (int i = 0; i < SHADOWRAYS;i++) {
			
			Ray shadowray = sampleShadowray(point, myscene);
			
			float lightdistance = glm::distance(shadowray.getend().getcoords(), shadowray.getstart().getcoords());
				
				//glm::distance(shadowray.getend().getcoords() - shadowray.getstart().getcoords());

			if (closest(shadowray, myscene) == 0)
			{
				//std::cout << "case 0 " << "\n";

				shadowDistance = glm::distance(myscene.rayIntersectionfortri(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera
				
			}
			else {
				//std::cout << "case 1 " << "\n";
				shadowDistance = glm::distance(myscene.rayIntersectionforsph(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera
			}
				
			
		
			if (shadowDistance > lightdistance) {
				
				double shadowAngle = glm::angle(glm::normalize(objNormal),
					glm::normalize(glm::vec3(shadowray.getend().getcoords() - shadowray.getstart().getcoords())));
				double lightfraction;
				if (shadowAngle > 1.57)
					lightfraction = 0;
				else
					lightfraction = cos(shadowAngle);
			//	std::cout << "brdf " << brdf << "\n";
				
				//std::cout << "color " << color << "\n";
				//brdf = surface.getsurfcolor();
				glm::vec3 temp = glm::dvec3(brdf.Red * lightfraction * myscene.getlights().getsurf().getsurfcolor().Red,
					brdf.Green * lightfraction * myscene.getlights().getsurf().getsurfcolor().Green,
					brdf.Blue * lightfraction *  myscene.getlights().getsurf().getsurfcolor().Blue);
				color =  ColorDbl(temp.x, temp.y, temp.z);
				//std::cout << color;
			}
		}
		return color;
	}
		
	 
	if(surface.modelcheck(Perfect)){
	
		glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
		glm::vec4 newDir = glm::vec4(glm::reflect(glm::vec3(dirr), objNormal), 1.0);
		glm::vec4 ppdir = glm::vec4(point.getcoords(),point.getw() )+ newDir;
		Ray r(point, Vertex(ppdir.x, ppdir.y, ppdir.z, ppdir.w));
		return Castray(r,myscene,depth);

	}
	
	
	std::cout << "basecase" << "\n";
	return ColorDbl(0.0);

}
Ray Camera::sampleShadowray(Vertex fromPoint,Scene myscene) {
	glm::vec4 lp = glm::vec4(5.0, 0.0, 4.5, 1.0);
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	glm::vec4 light_sample_point = glm::vec4(dis(rd)*1 - 1 / 2.0f + lp.x,
		dis(rd)*1 - 1 / 2.0f + lp.y,
		lp.z,
		lp.w);
	

	return Ray(fromPoint, Vertex(light_sample_point.x, light_sample_point.y, light_sample_point.z, light_sample_point.w) );
/*
	Vertex light_sample_point = myscene.getlights().getrandpointontri();
	std::cout << light_sample_point << std::endl;
	return Ray(fromPoint, light_sample_point);
*/
}

ColorDbl Camera::shadow(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene,ColorDbl color)
{
	/*
	glm::vec4 shadowIntersect;
	float shadowDistance;
	BRDF brdfDummy;

	glm::vec3 dummyNormal;
						  */
	Triangle lightTriangle = myscene.getlights();
	int lightcount = 0;
	for (int i = 0; i < 0;i++) {
		lightcount++;
		// create shadowrays point -> light
		Vertex lightPoint = myscene.getlights().getrandpointontri();
		glm::vec3 dirr = lightPoint.getcoords() - point.getcoords();
		Ray rayTowardsLight(point, Vertex(dirr.x,dirr.y,dirr.z));

		// visibility check
		std::list<sphereintersection> sphereIntersections = myscene.rayIntersectionforsph(rayTowardsLight);
		std::list<triangleintersection> triangleIntersections = myscene.rayIntersectionfortri(rayTowardsLight);
		triangleintersection intersection = triangleIntersections.front();

		double lightDistance = glm::distance(point.getcoords(), lightPoint.getcoords());
		double intersectionDistance = glm::distance(point.getcoords(), intersection.point.getcoords());

		if (sphereIntersections.size() > 0 || intersectionDistance < lightDistance) {
			// not visible!
			continue;
		}

		// calc geometric term
		double alpha = glm::dot(-normal.getDir(), rayTowardsLight.getend().getcoords());
		double beta = glm::clamp((double)glm::dot(lightTriangle.getnormal().getDir(), -rayTowardsLight.getend().getcoords()), 0.0, 1.0);

		double geometric = alpha * beta / pow(lightDistance, 2.0);
		Surface lightSurface = lightTriangle.getsurf();
		color =color + lightSurface.getsurfcolor() * lightSurface.getemission() * geometric;
		}
	return (color / lightcount);
}



int Camera::closest(Ray ray , Scene myscene)
{
	//newRay.direction = CalcRandomPDFRay(intersectionNormal);
	std::list<triangleintersection> triintersections = myscene.rayIntersectionfortri(ray);
	std::list<sphereintersection> sphintersections = myscene.rayIntersectionforsph(ray);
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
