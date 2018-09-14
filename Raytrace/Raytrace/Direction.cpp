#include "Direction.h"


Direction::~Direction()
{
	delete &x;
	delete &y;
	delete &z;
}
