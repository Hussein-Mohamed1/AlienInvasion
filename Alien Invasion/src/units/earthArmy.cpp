#pragma once
#include "earthArmy.h"
#include "Esoldier.h"
#include "Egunnery.h"
bool earthArmy::attack(unit* attacked)
{
	return true;
}
bool earthArmy::addUnit( unit*  EA)
{

	Esoldier* Esol = dynamic_cast<Esoldier*>(EA);
	if (Esol)
		ESlist.enqueue(Esol);
	Egunnery* Egunn = dynamic_cast<Egunnery*>(EA);
	if (Egunn)
		EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
	return true;
	
}
