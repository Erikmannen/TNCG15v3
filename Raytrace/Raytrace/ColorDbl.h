#pragma once
#include <iostream> 
#include <string>

class ColorDbl
{
public:
	ColorDbl() : Red(0), Green(0),Blue (0) {};
	ColorDbl(double Greychannel) :
		Red(Greychannel), Green(Greychannel), Blue(Greychannel) {};
	ColorDbl(double Redchannel, double Greenchannel, double Bluechannel)
		:Red(Redchannel), Green(Greenchannel), Blue(Bluechannel) {};
	//ColorDbl(ColorDbl& CDbl)
		//:Red(CDbl.Red), Green(CDbl.Green), Blue(CDbl.Blue) {};
	~ColorDbl();
	ColorDbl(const ColorDbl& cDbl) :Red(cDbl.Red),Green(cDbl.Green), Blue(cDbl.Blue){ std::cout << "colorused"; };
	// help functions
	void Setchannels(double Redchannel, double Greenchannel, double Bluechannel);
	// math stuffs
	ColorDbl operator+(const ColorDbl b);
	ColorDbl operator*(const ColorDbl b);
	ColorDbl operator*(const float b);
	ColorDbl operator/(const float b);

	// get functions
	double getColor(std::string S);

	friend std::ostream& operator<<(std::ostream& os, const ColorDbl& c);

private:
	double Red, Green, Blue;
};