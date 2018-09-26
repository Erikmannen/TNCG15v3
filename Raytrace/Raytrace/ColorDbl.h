#pragma once
class ColorDbl
{
public:
	ColorDbl() : Red(0), Green(0),Blue (0) {};
	ColorDbl(double Redchannel, double Greenchannel, double Bluechannel)
		:Red(Redchannel), Green(Greenchannel), Blue(Bluechannel) {};
	ColorDbl(ColorDbl & CDbl)
		:Red(CDbl.Red), Green(CDbl.Green), Blue(CDbl.Blue) {};
	~ColorDbl();
	ColorDbl(const ColorDbl& cDbl) :Red(cDbl.Red),Green(cDbl.Green), Blue(cDbl.Blue){};
	// help functions
	void Setchannels(double Redchannel, double Greenchannel, double Bluechannel);
	// math stuffs
	ColorDbl operator+(const ColorDbl b);
	ColorDbl operator*(const ColorDbl b);
	ColorDbl operator*(const float b);
	ColorDbl operator/(const float b);

private: 
	double Red, Green, Blue;
};

