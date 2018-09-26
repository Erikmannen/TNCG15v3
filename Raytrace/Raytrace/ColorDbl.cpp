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
	return ColorDbl(this->Red + b.Red, this->Green + b.Green, this->Blue + b.Blue);
}

ColorDbl ColorDbl::operator*(const ColorDbl b) {
	return ColorDbl(this->Red * b.Red, this->Green * b.Green, this->Blue * b.Blue);
}

ColorDbl ColorDbl::operator*(const float b) {
	return ColorDbl(this->Red * b, this->Green * b, this->Blue * Blue);
}

ColorDbl ColorDbl::operator/(const float b) {
	return ColorDbl(this->Red / b, this->Green / b, this->Blue / Blue);
}