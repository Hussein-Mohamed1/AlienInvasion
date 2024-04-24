#pragma once

#include "unit.h"

class Monster :
        public unit {
public:
    Monster(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr = nullptr)
            : unit(
            id, MonsterType, joinTime, health, power, attackCapacity, simPtr) {};

    virtual void print() const;
};

