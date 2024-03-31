#pragma once
#include "./units/unit.h"
#include"simulationManager.h"
class randGen
{
	simulationManager* simM;
public:
	void manageGeneration(fstream*);
	double handelPer(double per, int num);
	void generatUnits(double per, double RH1, double RH2, double RP1, double RP2, int RC1, int RC2, Type unit);
};

