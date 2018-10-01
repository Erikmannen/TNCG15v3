#include <iostream> 
#include <glm.hpp>
#include "Ray.h"
#include "Triangle.h"
#include "Scene.h"
#include "Camera.h"

using namespace std;

void dispintersection(Triangle & tri, Ray& ray)
{
	glm::vec3 t = glm::vec3(0.0);
	bool intersection = tri.rayIntersection(ray, t);
	if (intersection == true)
		cout << "ray intersected" << endl;
	else
		cout << "did not interesect" << endl;
	cout << "(" << t.x << "," << t.y << "," << t.z << ")" << endl;
}
Ray createray(Vertex v1,Vertex v2);


int main()
{
	cout << "hello world" << endl;
	glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);

	Ray myray;
	cout << Position.x << endl;
	cout << myray << endl;
	cout << "break" << endl;
	cout << myray.getstart().getcoords()[1] << endl;
	Ray ri = createray(Vertex(0.0f, 0.0f, 0.0f), Vertex(0.0f, 1.0f, 0.0f));
	Ray rj = createray(Vertex(0.0f, 0.0f, 0.0f), Vertex(0.0f, 1.0f, 0.0f));
	
	
	Ray r(Vertex(0.0f, 0.0f, 0.0f),Vertex(0.0f, 1.0f, 0.0f));
	cout << r 
		<<"riktiga start :  (0.0f, 0.0f, 0.0f) " <<"\n"<<
		 "riktiga end : (0.0f, 1.0f, 0.0f)" << endl;

	Ray r1(Vertex(0.0f, 0.0f, 0.0f), Vertex(4.0f, 0.0f, 2.0f));
	cout << r1
		<< "riktiga start :  (0.0f, 0.0f, 0.0f) " << "\n" <<
		"riktiga end : (4.0f, 0.0f, 2.0f)" << endl;
	//wont intersect with r but with r1
	Triangle mytri(Vertex(2.0f, 5.0f, 2.0f),
				   Vertex(2.0f, -5.0f, 2.0f),
				   Vertex(4.0f, 0.0f, 2.0f));
	
	//testraytriangleintersection();
	
	dispintersection(mytri, r);
	cout << "\n\n";
	dispintersection(mytri, r1);

	Scene scene;

	Camera cam;
	cam.render();
	
	while (true)
	{

	}
	return 0;
}


using namespace std;
Ray createray(Vertex v1, Vertex v2)
{
	Ray r(v1, v2);
	return r;
}


