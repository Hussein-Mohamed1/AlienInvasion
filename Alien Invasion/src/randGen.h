#pragma once
#include "./units/unit.h"
#include <fstream>
class randGen
{
	double perES, perET, perEG, perAS, perAM, perAD;
	double RangeEH1, RangeEH2, RangeAH1, RangeAH2, RangeEP1, RangeEP2, RangeAP1, RangeAP2;
	int unitscreated, RangeEC1, RangeEC2, RangeAC1, RangeAC2, prob;
	static int id;
public:
	randGen();
	double handelPer(double per, int num);
	unit* generatUnits( Type unit);
	double getnumofES();
	double getnumofET();
	double getnumofEG();
	double getnumofAS();
	double getnumofAM();
	double getnumofAD();
};

