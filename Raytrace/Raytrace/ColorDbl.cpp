#include "ColorDbl.h"





void ColorDbl::Setchannels(double Redchannel, double Greenchannel, double Bluechannel)
{
	Red = Redchannel;
	Green = Greenchannel; 
	Blue = Bluechannel;
}


ColorDbl::~ColorDbl()
{
}

ColorDbl ColorDbl::operator+(const ColorDbl b) {
	return ColorDbl(Red + b.Red, Green + b.Green, Blue + b.Blue);
}

ColorDbl ColorDbl::operator*(const ColorDbl b) {
	return ColorDbl(Red * b.Red, Green * b.Green, Blue * b.Blue);
}

ColorDbl ColorDbl::operator*(const float b) {
	return ColorDbl(Red * b, Green * b, Blue * b);
}

ColorDbl ColorDbl::operator/(const float b) {
	return ColorDbl(Red / b, Green / b, Blue / b);
}

std::ostream& operator<<(std::ostream& os, const ColorDbl& c)
{
	os << "(" << c.Red << ", " << c.Green << ", " << c.Blue << ")";
	return os;
}