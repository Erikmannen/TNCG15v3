#include <iostream> 
#include <glm.hpp>
#include "Ray.h";

using namespace std;

int main()
{
	cout << "hello world" << endl;
	glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
	

	Ray myray;
	cout << Position.x << endl;
	cout << myray << endl;
	cout <<"break"  << endl;

	while (true)
	{

	}
	return 0;
}