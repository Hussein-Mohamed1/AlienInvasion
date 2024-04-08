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
                earthSoldierCount++;
                return true;
            case Gunnery: {
                Egunnery *Egunn = dynamic_cast<Egunnery *>(earthUnit);
                EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
                earthGunneryCount++;
                return true;
            }
            case EarthTank: {
                Tank *newTank = dynamic_cast<Tank *>(earthUnit);
                earthTankCount++;
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

void earthArmy::print() {
    LinkedQueue<Esoldier *> TempESlist;
    Esoldier *soldier{nullptr};
    cout << "======================== Eartht Army Alive units ==================================\n";
    cout << "🌍 Earth Soldiers Count is: " << getEarthSoldierCount() << endl;
    cout << "ES [ ";
    while (ESlist.dequeue(soldier)) {
        {
            cout << soldier->getId() << ", ";
            TempESlist.enqueue(soldier);
        }
    }
    cout << "]\n";
    while (TempESlist.dequeue(soldier))
        if (soldier)
            ESlist.enqueue(soldier);


    cout << "🌍 Earth Gunnery Count is: " << getEarthGunneryCount() << endl;
    cout << "EG [ ";
    Egunnery *tempGunnery{nullptr};
    int garbage;
    priQueue<Egunnery *> tempEgunnery;
    while (EGlist.dequeue(tempGunnery, garbage)) {
        { ///@todo fix these
            cout << tempGunnery->getId() << ", ";
            tempEgunnery.enqueue(tempGunnery, garbage);
        }
    }
    cout << "]\n";
    while (tempEgunnery.dequeue(tempGunnery, garbage))
        if (tempGunnery)
            EGlist.enqueue(tempGunnery, tempGunnery->getHealth() + tempGunnery->getPower());

    cout << "🌍 Earth Tanks Count is: " << getEarthTankCount() << endl;
    cout << "ET [ ";
    ArrayStack<Tank *> tempTankList;
    Tank *tempTank{nullptr};
    while (TankList.pop(tempTank)) {
        {
            cout << tempTank->getId() << ", ";
            tempTankList.push(tempTank);
        }
    }
    cout << "]\n";
    while (tempTankList.pop(tempTank))
        if (tempTank)
            TankList.push(tempTank);

}

/// @details returns a randomUnit and removes it from its adt.
unit *earthArmy::getRandomUnit() {
    auto random_number = rand() % 3;
    switch (random_number) {
        case EarthTank: {
            Tank *removedTank;
            if (TankList.pop(removedTank)) {
                earthTankCount--;
                return removedTank;
            } else return nullptr;
        }
        case EarthSoldier: {
            Esoldier *removedSoldier;
            if (ESlist.dequeue(removedSoldier)) {
                earthSoldierCount--;
                return removedSoldier;
            } else return nullptr;
        }
        case Gunnery: {
            Egunnery *removedGunnery;
            int priority{0};
            if (EGlist.dequeue(removedGunnery, priority)) {
                earthGunneryCount--;
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
                earthSoldierCount--;
                return temp;
            }
            return nullptr;
        }
        case EarthTank: {
            Tank *temp{nullptr};
            if (TankList.pop(temp)) {
                earthTankCount--;
                return temp;
            }
            return nullptr;
        }
        case Gunnery: {
            Egunnery *temp{nullptr};
            int garbage;
            if (EGlist.dequeue(temp, garbage)) {
                earthGunneryCount--;
                return temp;
            }
            return nullptr;

        }
    };
    return nullptr;
}

int earthArmy::getEarthGunneryCount() const {
    return earthGunneryCount;
}

int earthArmy::getEarthSoldierCount() const {
    return earthSoldierCount;
}

int earthArmy::getEarthTankCount() const {
    return earthTankCount;
}
