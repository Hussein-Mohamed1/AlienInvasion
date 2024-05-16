#include "SaverUnit.h"

#pragma once

SaverUnit::SaverUnit(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr)
        : Esoldier(id, joinTime, health, power, attackCapacity, simPtr) {
    setType(Saver);
    Esoldier::Immune = true;
    Esoldier::Infected = false;
}
