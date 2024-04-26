#pragma once

#include "unit.h"

class HealUnit : public unit {
public:
    HealUnit(int id, Type type, int joinTime, double health, double power, int attackCapacity,
             simulationManager *simPtr) : unit(id, type, joinTime, health, power, attackCapacity, simPtr) {};

    void Heal(unit *);
};

