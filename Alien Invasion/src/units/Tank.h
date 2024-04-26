//
// Created by youss on 3/31/2024.
//

#ifndef ALIENINVASION_TANK_H
#define ALIENINVASION_TANK_H

class earthArmy;

#include "unit.h"

class Tank : public unit {
public:
    Tank(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr = nullptr)
            : unit(
            id, EarthTank, joinTime, health, power, attackCapacity, simPtr) {};

    bool Tank::damageEnemy(unit *);
};


#endif //ALIENINVASION_TANK_H
