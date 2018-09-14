#include <iostream> 
#include <glm.hpp>
using namespace std;

int main()
{
	cout << "hello world" << endl;
	glm::vec4 Position = glm::vec4(glm::vec3(0.0), 1.0);
	cout << Position.x << endl;
	return 0;
}