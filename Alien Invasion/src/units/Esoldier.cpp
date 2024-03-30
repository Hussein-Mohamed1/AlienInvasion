#include "Esoldier.h"
#include <cmath>
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