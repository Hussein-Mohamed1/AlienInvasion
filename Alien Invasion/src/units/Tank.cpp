//
// Created by youss on 3/31/2024.
//

#include "Tank.h"
#include "../simulationManager.h"

bool Tank::keepAttackingEarthSoldiers = false;

bool Tank::damageEnemy(unit *enemy) {
    if (enemy)
        if ((enemy->getType() == alienSoldier && simPtr->getEarthArmyUnitsCount() <=
                                                 0.3 * simPtr->getAlienArmyUnitsCount()) ||
            (enemy->getType() == alienSoldier && keepAttackingEarthSoldiers) || enemy->getType() == MonsterType) {

            if (enemy->getType() == alienSoldier) {
                if (keepAttackingEarthSoldiers &&
                    simPtr->getEarthSoldiersCount() >= 0.8 * simPtr->getAlienArmyUnitsCount())
                    keepAttackingEarthSoldiers = false;
                if (simPtr->getEarthArmyUnitsCount() <= 0.3 * simPtr->getAlienArmyUnitsCount())
                    keepAttackingEarthSoldiers = true;
            }

            unit::damageEnemy(enemy);
            return true;
        }
    return false;
}