#pragma once
#include "earthArmy.h"
class Egunnery :public earthArmy
{
public:
	bool attack(unit*);
	bool attack(unit* , unit* );
	void print() const ;
};

