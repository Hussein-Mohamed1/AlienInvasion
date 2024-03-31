#pragma once
#include "unit.h"
class Esoldier :public unit
{
public :
	Esoldier(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	bool attack(unit*);
	void print() const;
};

