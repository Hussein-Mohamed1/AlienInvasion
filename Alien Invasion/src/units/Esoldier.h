#pragma once
#include "earthArmy.h"
class Esoldier :public earthArmy
{
	bool attack(unit*);
	void print() const;
};

