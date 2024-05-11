#include "Monster.h"
#include<iostream>
#include "..\simulationManager.h"
#include "Esoldier.h"

void Monster::print() const {
    std::cout << "Monster-->\n";
    unit::print();
}

bool Monster::damageEnemy(unit *attackedUnit) {
    if (attackedUnit->getType() == EarthSoldier || attackedUnit->getType() == Saver ||
        attackedUnit->getType() == EarthTank) {
        if (attackedUnit->getType() == EarthSoldier)
            if (simPtr->canInfect()) {
                dynamic_cast<Esoldier *>(attackedUnit)->setInfected();

            }
        return unit::damageEnemy(attackedUnit);
    }
    return false;
}
