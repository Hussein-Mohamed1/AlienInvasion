#pragma once

#include "Esoldier.h"
#include <cmath>
#include "..\simulationManager.h"

Esoldier::Esoldier(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr)
        : unit(id, EarthSoldier, joinTime, health, power, attackCapacity, simPtr) {}

void Esoldier::print() const {
    cout << "Earth Soldier --->";
    unit::print();
}

bool Esoldier::damageEnemy(unit *attackedUnit) {
    if (attackedUnit->getType() == alienSoldier && !Infected) {
        return unit::damageEnemy(attackedUnit);
    }
    return false;
}

bool Esoldier::setInfected() {
    if (!Immune && !Infected) {
        Infected = true;
        simPtr->setEarthInfectedSoldierCount(simPtr->getEarthInfectedSoldierCount() + 1);
        simPtr->incTotalInfectCount();
        return true;
    } else return false;
}

bool Esoldier::is_Infected() const {
    return Infected;
}

bool Esoldier::makeImmune() {
    if (Infected && !Immune) {
        Immune = true;
        Infected = false;
        return true;
    }
    return false;
}

bool Esoldier::isImmune() {
    return Immune;
}

