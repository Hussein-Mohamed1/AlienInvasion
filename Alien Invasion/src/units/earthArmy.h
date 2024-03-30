#pragma once
#include "unit.h"
#include "../ds/ArrayStack.h"
#include "../ds/priQueue.h"
#include "../ds/LinkedQueue.h"
class Esoldier;
class Egunnery;
enum earthType
{
	ES , EG, ET
};
class earthArmy : public unit
{
	LinkedQueue< Esoldier*> ESlist;
	priQueue< Egunnery* > EGlist;
public:
	bool attack(unit*);
	bool addUnit( unit*);
	void removeUnit(unit*);
	void print() const;
	earthType Typeof(unit*);
};


