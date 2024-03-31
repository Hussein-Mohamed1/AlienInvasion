#pragma once
#include "Egunnery.h"
bool Egunnery::attack(unit* AD1 , unit* AD2)
{
	double damagedH1;
	double damagedH2;
		damagedH1= AD1->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AD1->getHealth()));
		damagedH2= AD2->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AD2->getHealth()));
		if (damagedH1 <= 0 || damagedH2 <= 0)
			return true;
		else
		{
			AD1->setHealth(damagedH1);
			AD2->setHealth(damagedH2);
		}
		return true;
}
bool Egunnery::attack(unit* AM )
{
	double damagedH = AM->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AM->getHealth()));
	if (damagedH > 0)
	{
		AM->setHealth(damagedH);
		return false;
	}
	return true;
}
void Egunnery::print() const
{
	cout << "Earth Gunnery----> ";
	unit::print();
}