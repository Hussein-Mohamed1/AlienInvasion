#pragma once
#include "Egunnery.h"
Egunnery::Egunnery(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr) :unit(id, Gunnery, joinTime, health, power, attackCapacity, simPtr) {}
//bool Egunnery::damageEnemy(unit* AD1 , unit* AD2)
//{
//	double damagedH1;
//	double damagedH2;
//		damagedH1= AD1->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AD1->getHealth()));
//		damagedH2= AD2->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AD2->getHealth()));
//		if (damagedH1 <= 0 || damagedH2 <= 0)
//			return true;
//		else
//		{
//			AD1->setHealth(damagedH1);
//			AD2->setHealth(damagedH2);
//		}
//		return true;
//}
//bool Egunnery::damageEnemy(unit* AM )
//{
//	double damagedH = AM->getHealth() - ((this->getPower() * this->getHealth()) / (100)) / (sqrt(AM->getHealth()));
//	if (damagedH > 0)
//	{
//		AM->setHealth(damagedH);
//		return false;
//	}
//	return true;
//}
void Egunnery::print() const
{
	cout << "Earth Gunnery----> ";
	unit::print();
}