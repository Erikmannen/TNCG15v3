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
			float diff = 1.0f / Subpixels;
			for (int subX = 0; subX < Subpixels; ++subX)
				for(int subY = 0; subY < Subpixels; ++subY)
				{
					double xMax =  w + (subX + 1)*diff;
					double xMin = w + subX * diff;

					double yMax = h + (subY + 1)*diff;
					double yMin = h + subY * diff;

					// En punkt på pixeln mellan 0 och 1 i y- och x-led
					double x = (xMax - xMin) * ((double)rand() / (double)RAND_MAX) + xMin;
					double y = (yMax - yMin) * ((double)rand() / (double)RAND_MAX) + yMin;

					Ray* tempray = pixeltoray2(x, y);
					//std::cout << tempray->getstart() << " -> " << tempray->getend() << std::endl;
					Img[h][w].addray(*tempray);
				}
		
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
			tempcolor = tempcolor / Subpixels;
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
				(int)(color.Red*255/max),
				(int)(color.Green * 255 / max),
				(int)(color.Blue * 255 / max));
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
	
	// handler orginal ,handler 2 direkt + diffuse  handler 3 motsvarar förenklade variant med tydlgi struktur
	if (close == 0) {

		for (triangleintersection &intersection : myscene.rayIntersectionfortri(myray)) {
			Triangle t = intersection.object;
			Surface s = t.getsurf();
			Direction normal = t.getnormal();
			returncolor = returncolor + handler3(s,normal, intersection.point, myray, myscene, depth);
			break;
		}
	}
	else if(close == 1) {
		for (sphereintersection &intersection : myscene.rayIntersectionforsph(myray)) {
			Sphere ts = intersection.object;
			Surface s = ts.getsurf();
			Vertex temppoint(intersection.point.getcoords().x, intersection.point.getcoords().y, intersection.point.getcoords().z);
			Direction normal = ts.getnormal(temppoint);
			returncolor = returncolor + handler3(s, normal, intersection.point,myray, myscene, depth);
			break;

		}
	}

	return returncolor;
}

ColorDbl Camera::handler3(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene, int depth)
{
	/*
	glm::vec3 objNormal = normal.getDir();
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
		*/				
	glm::vec3 directIllumination(0.0);
	glm::vec3 indirectIllumination(0.0);

	ColorDbl returncolor(0);
	if (surface.modelcheck(Lightsource))
	{
		returncolor =  surface.getemission();
	}
	else if (surface.modelcheck(Perfect)) // perfekt spegling
	{
		glm::vec3 dirr = glm::normalize(myray.getend().getcoords() - myray.getstart().getcoords());
		glm::vec4 newDir = glm::vec4(glm::reflect(glm::vec3(dirr), normal.getDir()), 1.0);
		//glm::vec3 newDir = point.getcoords() - 2.0f * glm::dot(normal.getDir(), point.getcoords()) * normal.getDir();
		glm::vec4 ppdir = glm::vec4(point.getcoords(), point.getw()) + newDir;
		//ppdir = glm::vec4(ppdir.x * 2.0f, ppdir.y * 2.0f, ppdir.z * 2.0f,ppdir.w);
		Ray r(point, Vertex(ppdir.x, ppdir.y, ppdir.z, ppdir.w));

		//Ray r = myray.reflection(point, normal);
	// r går från intersectionpoint , ut i världen relaterat till hur den speglats i normalen på objectet den träffa

		// fuling men är ok om man utgår från att spegeln bara hämtar en stuts bort
		/*if (closest(r, myscene) == 0) {
			//std::cout << std::endl << "disttotri " << std::endl;

			triangleintersection t = myscene.rayIntersectionfortri(r).front();
			Vertex p = t.point;
			Surface s = t.object.getsurf();
			Direction norm = t.object.getnormal();
			return returncolor + handler3(s, norm, p, r, myscene, depth);
		} // fuling men är ok om man utgår från att spegeln bara hämtar en stuts bort
		else if (closest(r, myscene) == 1) {

			sphereintersection t = myscene.rayIntersectionforsph(r).front();
			Vertex p = t.point;
			Surface s = t.object.getsurf();
			Direction norm = t.object.getnormal(p);
			return returncolor + handler3(s, norm, p, r, myscene, depth);

		}*/
		returncolor = Castray(r, myscene, depth);
		// miss / base case

		//return Castray(r, myscene, depth);

	}

	else if (surface.modelcheck(Lambertian))
	{

		
		/*
		std::uniform_real_distribution<> disAngle(0.0, M_PI);

		double incOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.z)),
			glm::normalize(glm::vec2(0.0, 1.0)));
		double asiOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.y)),
			glm::normalize(glm::vec2(0.0, 1.0)));
		double randAsi = 2.0 * disAngle(rd);
		double randInc = disAngle(rd);
		glm::vec4 reflDir = glm::vec4((randAsi + asiOffset),
			sin(randAsi + asiOffset),
			cos(randInc + incOffset), 1.0);

		glm::vec4 newend = glm::vec4(point.getcoords(),point.getw()) + reflDir;
		Vertex endver(newend.x, newend.y, newend.z, newend.w);
		Ray reflRay(point, endver);
		ColorDbl color(0.0);
		if (dis(gen) > 0.5) {
			color = Castray(reflRay,myscene,depth);
			color = color* 0.3;
		}
		*/
		//ColorDbl emittance = surface.lamreflec();

		Vertex lightpoint = myscene.getlights().getrandpointontri();
		Ray shadowray(point, lightpoint);
		float lightdistance = glm::distance(shadowray.getend().getcoords() , shadowray.getstart().getcoords());
		float shadowdistance = MAXVALUE;
		//glm::distance(shadowray.getend().getcoords() - shadowray.getstart().getcoords());
	
		if (closest(shadowray, myscene) == 0)
		{
			//std::cout << "case 0 " << "\n";
			if (myscene.rayIntersectionfortri(shadowray).front().object.islight)
				shadowdistance = MAXVALUE;
			else
				shadowdistance = glm::distance(myscene.rayIntersectionfortri(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera

		
		}
		else if (closest(shadowray, myscene) == 1) {
			//std::cout << "case 2 " << "\n";
			shadowdistance = glm::distance(myscene.rayIntersectionforsph(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera
		}
	//	std::cout << "shadowdistance : " << shadowdistance << "\n";
		//std::cout << "lightdistaance : " << lightdistance << "\n";
		if (shadowdistance < lightdistance)
		{
			double shadowAngle = glm::angle(glm::normalize(normal.getDir()),
				glm::normalize(glm::vec3(shadowray.getend().getcoords() - shadowray.getstart().getcoords())));
			double lightfraction;
			//float cos_theta = 
			/*glm::vec3 compareer = glm::vec3(surface.getsurfcolor().Red, surface.getsurfcolor().Green, surface.getsurfcolor().Blue);
			if (compareer == glm::vec3(20, 200, 0))
			{
				std::cout << "hit tetra";
				std::cout << surface.getsurfcolor()<<"\n";
				std::cout << shadowAngle;

			}*/
			if (shadowAngle > 1.57f)
				returncolor = ColorDbl(0);
			else {
				lightfraction = cos(shadowAngle);
				returncolor = returncolor +  surface.lamreflec() * lightfraction;
			}
			//return  surface.lamreflec() * lightfraction;// lightfrac ger soft shadows
			
		}
		else
			returncolor =  surface.getsurfcolor();
	}
	
	
	
	return returncolor;
}

// denna är tänkt att ge vilken intersectiontyp som är närmast
int Camera::closest(Ray ray , Scene myscene)
{
	//newRay.direction = CalcRandomPDFRay(intersectionNormal);
	std::list<triangleintersection> triintersections = myscene.rayIntersectionfortri(ray);
	std::list<sphereintersection> sphintersections = myscene.rayIntersectionforsph(ray);
	float disttotri = MAXVALUE;
	float disttosph = MAXVALUE;

	// check if empty
	if (triintersections.size() > 0) {
		
		disttotri = glm::distance(triintersections.front().point.getcoords(), ray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttotri : " << disttotri << std::endl;
	}
	if (sphintersections.size() != 0) {
		disttosph = glm::distance(sphintersections.front().point.getcoords(), ray.getstart().getcoords()); // todo sortera
		//std::cout << std::endl << "disttosph : " << disttosph << std::endl;
	}
	else if (!triintersections.size() && !sphintersections.size())
	{
		/*std::cout <<" size is 0" << "\n";
		std::cout << ray.getstart() << "\n";
		std::cout << ray.getend() << "\n";*/
		return 2;
		//	std::cout << "miss Ray origin : " << myray.getstart()
			//	<< "Ray end: " << myray.getend() << std::endl;
		
	}
	
	if (disttosph > disttotri)
	{
		return 0;
	}
	else 
	{
		return 1;
	}
	
	
}



/*************************************************************************************************************************************************************************************************

all under denna används ej atm

*************************************************************************************************************************************************************************************************/
ColorDbl Camera::indirect(Surface s, Vertex point, Scene myscene, Direction normal, int depth)
{
	ColorDbl color(0);
	ColorDbl c = s.getsurfcolor();
	glm::vec3 intersectionnormal = normal.getDir();
	float absorption = c.Red > c.Green && c.Red > c.Blue ? c.Red : c.Green > c.Blue ? c.Green : c.Blue;

	if (depth < MAXDEPTH)
	{

		glm::vec3 dirr = CalcRandomPDFRay(intersectionnormal);
		Ray newray(point, Vertex(dirr.x, dirr.y, dirr.z));
		if (closest(newray, myscene) != 2) {
			//float brdf = intersection.shape->LambertianBRDF();
			float brdf = s.getcoeff() / M_PI;
			depth++;
			float importance = M_PI * brdf;
			color = color + Castray(newray, myscene, depth) / (absorption);
		}

	}
	return color;

}
ColorDbl Camera::direct2(Vertex point, Scene myscene, Direction normal, glm::vec3 objNormal, ColorDbl color, ColorDbl brdf)
{

	//glm::vec4 shadowIntersect;
	float shadowDistance = 0;
	float lightdistance = 0;
	ColorDbl brdfDummy;

	//std::cout << " brdf 2ond " << brdf << "\n";
	for (int i = 0; i < SHADOWRAYS;i++) {
		//color = surface.lamreflec();

		Ray shadowray = sampleShadowray(point, myscene);

		lightdistance = glm::distance(shadowray.getend().getcoords(), shadowray.getstart().getcoords());

		//glm::distance(shadowray.getend().getcoords() - shadowray.getstart().getcoords());

		if (closest(shadowray, myscene) == 0)
		{
			//std::cout << "case 0 " << "\n";

			shadowDistance = glm::distance(myscene.rayIntersectionfortri(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera

		}
		else if (closest(shadowray, myscene) == 1) {
			//std::cout << "case 1 " << "\n";
			shadowDistance = glm::distance(myscene.rayIntersectionforsph(shadowray).front().point.getcoords(), point.getcoords()); // todo sortera
		}



		//std::cout << " brdf 3 " << brdf << "\n";
		//std::cout <<"pre  color : "<< color<<"\n";
		//std::cout << "shadowDistance : " << shadowDistance << "\n";
		//std::cout << "lightdistance : " << lightdistance << "\n";
		if (shadowDistance > lightdistance) {
			//std::cout << "shadow > light" << "\n";
			double shadowAngle = glm::angle(glm::normalize(objNormal),
				glm::normalize(glm::vec3(shadowray.getend().getcoords() - shadowray.getstart().getcoords())));
			double lightfraction;
			if (shadowAngle > 1.57)
				lightfraction = 0;
			else
				lightfraction = cos(shadowAngle);

			//std::cout << " brdf 3 " << brdf << "\n";
			//	std::cout << "brdf " << brdf << "\n";

			//std::cout << "color " << color << "\n";
			//brdf = surface.getsurfcolor();
			//std::cout << "brdf : " << brdf << "\n";
			std::cout << "lightfrac : " << lightfraction << "\n";
			std::cout << "shadowangle : " << shadowAngle << "\n";
			//std::cout << "lightcolor : " << myscene.getlights().getsurf().getsurfcolor() << "\n";
			glm::vec3 temp = glm::dvec3(brdf.Red * lightfraction * myscene.getlights().getsurf().getsurfcolor().Red,
				brdf.Green * lightfraction * myscene.getlights().getsurf().getsurfcolor().Green,
				brdf.Blue * lightfraction *  myscene.getlights().getsurf().getsurfcolor().Blue);
			color = color + ColorDbl(temp.x, temp.y, temp.z);
			std::cout << color;
		}


	}
	return color;

}
ColorDbl Camera::dirrrad(Vertex point, Surface s, Direction normal, Scene myscene)
{
	ColorDbl color(0);

	for (int i = 0; i < SHADOWRAYS; i++) {
		//select light source k based of lightsource pdf, should probably be a property of lightsource and depend on distance and size
		//int lightIndex = rand() % scene->lights->size(); //currently just select one random lightsource
		//int lightIndex = rand() % scene->lights->size(); //currently just select one random lightsource
		//Shape* currentLight = scene->lights->at(lightIndex);
		Triangle light = myscene.getlights();
		float lightSourcePdf = 1.0f;
		float lightPointPdf = 1.0f;
		//generate shadowray to point y on light source k

		Vertex origin = point;
		Vertex endpoint = light.getrandpointontri();
		Ray shadowRay(origin, endpoint);
		float lightdistance = glm::distance(shadowRay.getend().getcoords(), shadowRay.getstart().getcoords());
		float shadowDistance = 0;
		if (closest(shadowRay, myscene) == 0)
		{
			//std::cout << "case 0 " << "\n";

			shadowDistance = glm::distance(myscene.rayIntersectionfortri(shadowRay).front().point.getcoords(), point.getcoords()); // todo sortera

		}
		else if (closest(shadowRay, myscene) == 1) {
			//std::cout << "case 1 " << "\n";
			shadowDistance = glm::distance(myscene.rayIntersectionforsph(shadowRay).front().point.getcoords(), point.getcoords()); // todo sortera
		}
		//shadowRay.origin = intersection.position;
		//.direction = currentLight->GetRandomDirectionTowardsShape(intersection.position);
		//estimate radiance
		//Intersection possibleLight = Trace(shadowRay, scene);

		if (lightdistance > shadowDistance)
		{//	if (possibleLight.shape == currentLight) {
			float surfaceCos = std::max(0.0f, glm::dot(myscene.rayIntersectionfortri(shadowRay).front().object.getnormal().getDir(), shadowRay.getdirection().getDir()));
			float lightCos = std::max(0.0f, glm::dot(light.getnormal().getDir(), -shadowRay.getdirection().getDir()));

			ColorDbl lightColor = light.getsurf().getsurfcolor();

			float radianceTransfer = surfaceCos * lightCos;

			float brdf = myscene.rayIntersectionfortri(shadowRay).front().object.getsurf().getcoeff() / M_PI;// intersection.shape->OrenNayarBRDF(intersection.ray->direction, shadowRay.direction, intersection.position);

			color = color + (lightColor*lightPointPdf*radianceTransfer*brdf) / (lightSourcePdf);
		}


	}
	return color / SHADOWRAYS;
}
ColorDbl Camera::direct(Vertex point, Scene myscene, Direction normal)
{
	ColorDbl clr(0.0);
	int lightCount = 0;
	double lightArea = 0.0;
	Triangle light = myscene.getlights();
	std::vector<Vertex> vertexlist = light.getvertex();
	lightArea = 0.5 * glm::length(glm::cross(vertexlist[1].getcoords(), vertexlist[2].getcoords()));
	//(std::cout << "lightarea : " << lightArea << "\n";
	for (int i = 0; i < SHADOWRAYS; ++i) {
		++lightCount;
		// create shadowrays point -> light
		Vertex lightPoint = light.getrandpointontri();
		//	std::cout << lightPoint << "\n";
		glm::vec3 directiontolight = glm::normalize(lightPoint.getcoords() - point.getcoords());
		Ray rayTowardsLight(point, Vertex(directiontolight.x, directiontolight.y, directiontolight.z));

		// visibility check
		std::list<sphereintersection> sphereIntersections = myscene.rayIntersectionforsph(rayTowardsLight);
		std::list<triangleintersection> triangleIntersections = myscene.rayIntersectionfortri(rayTowardsLight);
		triangleintersection intersection = triangleIntersections.front();

		double lightDistance = glm::distance(point.getcoords(), lightPoint.getcoords());
		double intersectionDistance = glm::distance(point.getcoords(), intersection.point.getcoords());

		//std::cout << "lightDistance" << lightDistance << std::endl;
		//std::cout << "intersectionDistance" << intersectionDistance << std::endl;

		if (sphereIntersections.size() > 0 || intersectionDistance < lightDistance) {
			// not visible!
			continue;
		}

		// calc geometric term
		glm::vec3 dirrrayTowardsLight = rayTowardsLight.getend().getcoords() - rayTowardsLight.getend().getcoords();

		double alpha = glm::dot(-normal.getDir(), dirrrayTowardsLight);
		double beta = glm::clamp((double)glm::dot(light.getnormal().getDir(), -dirrrayTowardsLight), 0.0, 1.0);

		double geometric = alpha * beta / pow(lightDistance, 2.0);
		Surface lightSurface = light.getsurf();
		clr = clr + lightSurface.getsurfcolor() * lightSurface.getemission() * geometric;
	}



	return clr * lightArea / (double)lightCount;

}
glm::vec3 Camera::CalcRandomPDFRay(glm::vec3 &normal) {
	float u = (float)rand() / RAND_MAX;
	float v = (float)rand() / RAND_MAX;

	//float r1 = 2 * M_PI * u;
	//float r2 = sqrt(v);

	//glm::vec3 rotw = normal;
	//glm::vec3 rotu = glm::cross(abs(rotw.x) > 0.1f ? glm::vec3(0, 1, 0) : glm::vec3(1, 0, 0), normal);
	//glm::vec3 rotv = glm::cross(rotw, rotu);

	//direction = glm::normalize((float)(r2*cos(r1))*rotu + (float)(r2*sin(r1))*rotv + (float)(sqrt(1 - v))*rotw);

	float x = cos(2 * M_PI*u)*sqrt(v);
	float z = sin(2 * M_PI*u)*sqrt(v);
	float y = sqrt(1 - v);

	glm::vec3 randomDirection = glm::normalize(glm::vec3(x, y, z));

	float c = glm::dot(glm::vec3(0, 1, 0), normal);

	glm::vec3 direction;
	if (c == 1.0f) {
		direction = randomDirection;
	}
	else if (c == -1.0f) {
		direction = -randomDirection;
	}
	else {
		glm::vec3 cross = glm::cross(glm::vec3(0, 1, 0), normal);
		float s = glm::length(cross);

		glm::mat3 vx(0, -(cross.z), cross.y,
			cross.z, 0, -cross.x,
			-cross.y, cross.x, 0);

		glm::mat3 rot = glm::mat3(1.0f) + vx + vx * vx*(1 - c) / (s * s);
		direction = glm::normalize(randomDirection*rot);
	}

	return direction;
}
Ray Camera::sampleShadowray(Vertex fromPoint, Scene myscene) {
	glm::vec4 lp = glm::vec4(5.0, 0.0, 4.5, 1.0);
	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);
	glm::vec4 light_sample_point = glm::vec4(dis(rd) * 1 - 1 / 2.0f + lp.x,
		dis(rd) * 1 - 1 / 2.0f + lp.y,
		lp.z,
		lp.w);
	Vertex lightp(light_sample_point.x, light_sample_point.y, light_sample_point.z, light_sample_point.w);
	//	std::cout << lightp << "\n";
	return Ray(fromPoint, lightp);
	/*
		Vertex light_sample_point = myscene.getlights().getrandpointontri();
		std::cout << light_sample_point << std::endl;
		return Ray(fromPoint, light_sample_point);
	*/
}
ColorDbl Camera::shadow(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene, ColorDbl color)
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
		Ray rayTowardsLight(point, Vertex(dirr.x, dirr.y, dirr.z));

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
		color = color + lightSurface.getsurfcolor() * lightSurface.getemission() * geometric;
	}
	return (color / lightcount);
}
// äldsta versionen
ColorDbl Camera::handler(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene, int depth) {

	glm::vec4 intersectpoint = glm::vec4(0.0, 0.0, 0.0, -1.0f);
	float intersectdistance;
	ColorDbl brdf = surface.getsurfcolor(); // type o color
	//std::cout << " brdf first " << brdf << "\n";

	glm::vec3 objNormal = normal.getDir();
	if (surface.modelcheck(Lightsource))
	{
		return ColorDbl(255, 255, 255);
	}

	/*if (closest(myray, myscene) == 2) {
		//std::cout << "firstif";
		return ColorDbl(0);

	}*/

	std::random_device rd;  //Will be used to obtain a seed for the random number engine
	std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
	std::uniform_real_distribution<> dis(0.0, 1.0);

	if (surface.modelcheck(Lambertian)) {
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
		glm::vec4 temp = glm::vec4(point.getcoords(), point.getw()) + reflDir;
		Ray reflRay = Ray(point, Vertex(temp.x, temp.y, temp.z, temp.w));


		Ray shadowray = Ray(point, myscene.getlights().getrandpointontri());


		ColorDbl color = surface.getsurfcolor();

		//ColorDbl color(0); // = surface.lamreflec();
		if (dis(gen) > 0.5) {
			//color = surface.lamreflec();
			color = color + Castray(reflRay, myscene, depth)* 0.3;
			//color = surface.getsurfcolor();// todo ta bort

		}
		color = direct2(point, myscene, normal, objNormal, color, brdf);

		return color;
	}


	if (surface.modelcheck(Perfect)) {

		glm::vec3 dirr = myray.getend().getcoords() - myray.getstart().getcoords();
		glm::vec4 newDir = glm::vec4(glm::reflect(glm::vec3(dirr), objNormal), 1.0);
		glm::vec4 ppdir = glm::vec4(point.getcoords(), point.getw()) + newDir;
		Ray r(point, Vertex(ppdir.x, ppdir.y, ppdir.z, ppdir.w));
		return Castray(r, myscene, depth);

	}


	//std::cout << "basecase" << "\n";
	return ColorDbl(0.0);

}
// handler 2 motsvarar direkt (hårda skuggor ) samt enkel påbyggnad för diffusa men hårda är inte 100
ColorDbl Camera::handler2(Surface surface, Direction normal, Vertex point, Ray myray, Scene myscene, int depth)
{
	ColorDbl color(0);
	if (surface.modelcheck(Lightsource))
	{
		return surface.getsurfcolor();
	}
	if (closest(myray, myscene) == 2)
	{
		return color;
	}


	color = color + dirrrad(point, surface, normal, myscene);
	//color = color + indirect(surface,point,myscene, normal,depth);
	color = color * surface.getsurfcolor();
	return color;

}
// förenklad ide