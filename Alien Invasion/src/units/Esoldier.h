#pragma once
#include "unit.h"
class Esoldier :public unit
{
	bool Infected = false;
    bool Immune = false;
public:
	static int numofInfectedES;
	Esoldier(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
	void print() const;
	bool damageEnemy(unit*);

    bool setInfected();
	bool is_Infected();

    void makeImmune();

    bool isImmune();
};

