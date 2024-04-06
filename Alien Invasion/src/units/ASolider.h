#pragma once
#include "unit.h"
#include"../ds/LinkedQueue.h"
class ASolider : public unit
{
public:
	ASolider(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr = nullptr)
		: unit(
			id, alienSoldier, joinTime, health, power, attackCapacity, simPtr) {};
	virtual	void print() const;

};

