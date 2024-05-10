#pragma once
#include "unit.h"
class Esoldier :public unit
{
	bool Infected = false;
	bool Immuned = false;
public:
	Esoldier(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	void print() const;
	bool damageEnemy(unit*);
	void setInfected();
	bool is_Infected();
	void setImmuned();
	bool is_Immuned();
};

