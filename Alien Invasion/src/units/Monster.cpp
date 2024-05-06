#include "Monster.h"
#include<iostream>

void Monster::print()   const
{
	std::cout << "Monster-->\n";
	unit::print();
}
bool Monster::damageEnemy(unit* attackedUnit)

{
	if (attackedUnit->getType() == EarthSoldier || attackedUnit->getType() == EarthTank)
	{
		return unit::damageEnemy(attackedUnit);
	}
	return false;
}
