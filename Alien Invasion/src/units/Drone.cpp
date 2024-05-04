//
// Created by youss on 4/4/2024.
//

#include<iostream>
#include "Drone.h"

void Drone::print() const
{
	std::cout << "Drone -->> \n";
	unit::print();
}
bool Drone::damageEnemy(unit* attackedUnit)
{
	if (attackedUnit->getType() == EarthTank || attackedUnit->getType() == Gunnery)
	{
		return unit::damageEnemy(attackedUnit);
	}
	return false;
}
