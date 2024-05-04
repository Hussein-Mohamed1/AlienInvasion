#pragma once
#include "unit.h"
class Esoldier :public unit
{
public:
	Esoldier(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	void print() const;
	bool damageEnemy(unit*);
};

