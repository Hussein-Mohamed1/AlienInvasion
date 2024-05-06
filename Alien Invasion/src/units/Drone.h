//
// Created by youss on 4/4/2024.
//

#ifndef ALIENINVASION_DRONE_H
#define ALIENINVASION_DRONE_H

#include "unit.h"

class Drone : public unit {
public:

    Drone(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr = nullptr)
            : unit(
            id, DronePair, joinTime, health, power, attackCapacity, simPtr) {};

    virtual void print() const;
    bool damageEnemy(unit*);
};


#endif //ALIENINVASION_DRONE_H
