#include "HealUnit.h"

void HealUnit::Heal(unit* injuredUnit)
{
	// Given Equation 
	double ImprovemntHealth = (power * (health / 100)) / sqrt(injuredUnit->getHealth());

	injuredUnit->setHealth(injuredUnit->getHealth()+ImprovemntHealth);
}