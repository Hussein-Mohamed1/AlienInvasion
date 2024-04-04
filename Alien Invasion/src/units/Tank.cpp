//
// Created by youss on 3/31/2024.
//

#include "Tank.h"
#include "../simulationManager.h"

bool Tank::damageEnemy(unit *enemy) {
    if (enemy)
        if (enemy->getType() == alienSoldier || enemy->getType() == MonsterType
                                                && simPtr->getEarthUnitCount() <= 0.3 * simPtr->getAlienUnitCount()) {
            unit::damageEnemy(enemy);
            return true;
        }
    return false;
}
