#pragma once

#include "earthArmy.h"
#include "Esoldier.h"
#include "Egunnery.h"
#include "alienArmy.h"

unit *earthArmy::damageEnemy(unit *enemy) {

    if (enemy->getType() == alienSoldier || enemy->getType() == MonsterType
                                            && unitCount <= 0.3 * alienArmyPtr->getUnitCount()) {
        Tank *ETank;
        TankList.pop(ETank);
        return ETank;
    }
    return nullptr;
    /// @todo add the reset of unit
}

bool earthArmy::addUnit(unit *earthUnit) {


    if (earthUnit->getType() == EarthSoldier)
        ESlist.enqueue(dynamic_cast<Esoldier *>(earthUnit));

    if (earthUnit->getType() == Gunnery) {
        Egunnery *Egunn = dynamic_cast<Egunnery *>(earthUnit);
        EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
    }
    if (earthUnit->getType() == EarthTank) {
        Tank *newTank = dynamic_cast<Tank *>(earthUnit);
        if (!TankList.push(newTank))
            return false;
    }
    return true;

}

// used to remove
void earthArmy::removeUnit(unit *) {

}

void earthArmy::print() const {

}

/// @details returns a randomUnit and removes it from its adt.
unit *earthArmy::getRandomUnit() {
    auto random_number = rand() % 3;
    switch (random_number) {
        case EarthTank: {
            Tank *removedTank;
            if (TankList.pop(removedTank))
                return removedTank;
            else return nullptr;
        }
        case EarthSoldier: {
            Esoldier *removedSoldier;
            if (ESlist.dequeue(removedSoldier))
                return removedSoldier;
            else return nullptr;
        }
        case Gunnery: {
            Egunnery *removedGunnery;
            int priority{0};
            if (EGlist.dequeue(removedGunnery, priority))
                return removedGunnery;
            else return nullptr;
        }
    }
}
