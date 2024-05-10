//
// Created by youss on 3/31/2024.
//

#include "Tank.h"
#include "../simulationManager.h"

bool Tank::keepAttackingEarthSoldiers = false;

bool Tank::damageEnemy(unit *enemy) {

    if (enemy)
        if ((enemy->getType() == alienSoldier && simPtr->getEarthSoldiersCount() &&
             simPtr->getEarthSoldiersCount() <= 0.3 * (simPtr->getAlienSoldiersCount() + 1)) ||
            (enemy->getType() == alienSoldier && keepAttackingEarthSoldiers) || enemy->getType() == MonsterType) {

            if (enemy->getType() == alienSoldier) {
                if (keepAttackingEarthSoldiers && simPtr->getEarthSoldiersCount() &&
                    simPtr->getEarthSoldiersCount() >= 0.8 * (simPtr->getAlienSoldiersCount() + 1))
                    keepAttackingEarthSoldiers = false;
                if (!keepAttackingEarthSoldiers && simPtr->getEarthSoldiersCount() &&
                    simPtr->getEarthSoldiersCount() <= 0.3 * (simPtr->getAlienSoldiersCount() + 1))
                    keepAttackingEarthSoldiers = true;
            }

            unit::damageEnemy(enemy);
            return true;
        }
    return false;
}