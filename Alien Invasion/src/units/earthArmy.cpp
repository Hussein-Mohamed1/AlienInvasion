#pragma once

#include "earthArmy.h"
#include "Esoldier.h"
#include "Egunnery.h"
#include "alienArmy.h"

unit *earthArmy::Attack(unit *enemy) {

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

    if (earthUnit) {
        switch (earthUnit->getType()) {
            case EarthSoldier:
                ESlist.enqueue(dynamic_cast<Esoldier *>(earthUnit));
                unitCount++;
                return true;
            case Gunnery: {
                Egunnery *Egunn = dynamic_cast<Egunnery *>(earthUnit);
                EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
                unitCount++;
                return true;
            }
            case EarthTank: {
                Tank *newTank = dynamic_cast<Tank *>(earthUnit);
                unitCount++;
                if (!TankList.push(newTank))
                    return false;
            }
        }
        return true;
    } else
        return false;

}

// used to remove
void earthArmy::removeUnit(unit *) {

}

void earthArmy::print()  {
    LinkedQueue<Esoldier*> TempESlist;
    Esoldier* soldier;
    cout << "======================== Eartht Army Alive units ==================================\n";
    cout << "ES [ ";
    while (ESlist.dequeue(soldier))
    {
        cout << soldier->getId() << ", ";
        TempESlist.enqueue(soldier);
    }
    cout << "]";
    while (TempESlist.dequeue(soldier))
    {
        ESlist.enqueue(soldier);
    }
}

/// @details returns a randomUnit and removes it from its adt.
unit *earthArmy::getRandomUnit() {
    auto random_number = rand() % 3;
    switch (random_number) {
        case EarthTank: {
            Tank *removedTank;
            if (TankList.pop(removedTank)) {
                unitCount--;
                return removedTank;
            } else return nullptr;
        }
        case EarthSoldier: {
            Esoldier *removedSoldier;
            if (ESlist.dequeue(removedSoldier)) {
                unitCount--;
                return removedSoldier;
            } else return nullptr;
        }
        case Gunnery: {
            Egunnery *removedGunnery;
            int priority{0};
            if (EGlist.dequeue(removedGunnery, priority)) {
                unitCount--;
                return removedGunnery;
            } else return nullptr;
        }
    }
}

unit *earthArmy::getUnit(Type type) {
    switch (type) {
        case EarthSoldier: {
            Esoldier *temp{nullptr};
            if (ESlist.dequeue(temp)) {
                unitCount--;
                return temp;
            }
            return nullptr;
        }
        case EarthTank: {
            Tank *temp{nullptr};
            if (TankList.pop(temp)) {
                unitCount--;
                return temp;
            }
            return nullptr;
        }
        case Gunnery: {
            Egunnery *temp{nullptr};
            int garbage;
            if (EGlist.dequeue(temp, garbage)) {
                unitCount--;
                return temp;
            }
            return nullptr;

        }
    };
    return nullptr;
}
