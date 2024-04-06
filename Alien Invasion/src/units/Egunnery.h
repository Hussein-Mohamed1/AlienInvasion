#pragma once

#include "earthArmy.h"

class Egunnery : public unit {
public:
    Egunnery(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr);
//	bool damageEnemy(unit*);
    //bool damageEnemy(unit* , unit* );
    void print() const;
};

