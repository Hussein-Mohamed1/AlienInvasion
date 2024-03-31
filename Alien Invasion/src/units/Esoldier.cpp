#pragma once
#include "Esoldier.h"
#include <cmath>
Esoldier::Esoldier(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr) :unit( id, type, joinTime,  health,  power,  attackCapacity, simPtr)
{

}
bool Esoldier::attack(unit* AS)
{
	double damagedH = AS->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AS->getHealth()));
	if (damagedH > 0)
	{
		AS->setHealth(damagedH);
		return false;
	}
	return true;
}
void Esoldier::print() const
{
	cout << "Earth Soldier --->";
	unit::print();
}