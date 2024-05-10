#include "SaverUnit.h"
#pragma once
SaverUnit::SaverUnit(int id, int joinTime, double health, double power, int attackCapacity, simulationManager* simPtr)
    : unit(id, Saver, joinTime, health, power, attackCapacity, simPtr) {}
void SaverUnit::print() const {
    cout << "Saver unit --->";
    unit::print();
}
bool SaverUnit::damageEnemy(unit* attackedUnit)
{
    if (attackedUnit->getType() == alienSoldier)
    {
        return unit::damageEnemy(attackedUnit);
    }
    return false;
}