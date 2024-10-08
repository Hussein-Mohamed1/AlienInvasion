#pragma once

#include "Esoldier.h"
#include <cmath>

Esoldier::Esoldier(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr)
        : unit(id, EarthSoldier, joinTime, health, power, attackCapacity, simPtr) {}

void Esoldier::print() const {
    cout << "Earth Soldier --->";
    unit::print();
}
bool Esoldier::damageEnemy(unit* attackedUnit)
{
    if (attackedUnit->getType() == alienSoldier)
    {
        return unit::damageEnemy(attackedUnit);
    }
    return false;
}