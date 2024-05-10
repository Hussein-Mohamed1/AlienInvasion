#pragma once
#include "unit.h"
class SaverUnit : public unit
{
public:
	SaverUnit(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	void print() const;
	bool damageEnemy(unit*);
};

