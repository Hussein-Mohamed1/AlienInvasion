#pragma once
#include "earthArmy.h"
class Egunnery :public unit
{
public:
	Egunnery(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	bool attack(unit*);
	bool attack(unit* , unit* );
	void print() const ;
};

