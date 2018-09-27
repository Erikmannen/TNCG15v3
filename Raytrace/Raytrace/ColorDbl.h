#pragma once
class ColorDbl
{
public:
	ColorDbl() : Red(0), Green(0),Blue (0) {};
	ColorDbl(double Greychannel) :
		Red(Greychannel), Green(Greychannel), Blue(Greychannel) {};
	ColorDbl(double Redchannel, double Greenchannel, double Bluechannel)
		:Red(Redchannel), Green(Greenchannel), Blue(Bluechannel) {};
	ColorDbl(ColorDbl & CDbl)
		:Red(CDbl.Red), Green(CDbl.Green), Blue(CDbl.Blue) {};
	~ColorDbl();

	// help functions
	void Setchannels(double Redchannel, double Greenchannel, double Bluechannel);

private: 
	double Red, Green, Blue;
};

