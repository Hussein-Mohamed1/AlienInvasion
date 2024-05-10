#pragma once

#include "earthArmy.h"
#include "Esoldier.h"
#include "Egunnery.h"
#include "alienArmy.h"

unit *earthArmy::Attack(unit *enemy) {
    return nullptr;
    /// @todo add the reset of unit
}

bool earthArmy::addUnit(unit *earthUnit) {

    if (earthUnit) {
        switch (earthUnit->getType()) {
            case EarthSoldier:
                ESlist.enqueue(dynamic_cast<Esoldier *>(earthUnit));
                return true;
            case Gunnery: {
                Egunnery *Egunn = dynamic_cast<Egunnery *>(earthUnit);
                EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
                return true;
            }
            case EarthTank: {
                Tank *newTank = dynamic_cast<Tank *>(earthUnit);
                if (!TankList.push(newTank))
                    return false;
            }
        }
        return true;
    } else
        return false;

}


void earthArmy::print() {
    LinkedQueue<Esoldier *> TempESlist;
    Esoldier *soldier{nullptr};
    cout << "======================== Earth Army Alive units ==================================\n";
    cout << "🌍 Earth Soldiers Count is: " << ESlist.getCount() << endl;
    cout << "ES [ ";
    while (ESlist.dequeue(soldier)) {
        {
            cout << soldier->getId() << (ESlist.isEmpty() ? "" : ", ");
            TempESlist.enqueue(soldier);
        }
    }
    cout << "]\n";
    while (TempESlist.dequeue(soldier))
        if (soldier)
            ESlist.enqueue(soldier);


    cout << "🌍 Earth Gunnery Count is: " << EGlist.getCount() << endl;
    cout << "EG [ ";
    Egunnery *tempGunnery{nullptr};
    int garbage;
    priQueue<Egunnery *> tempEgunnery;
    while (EGlist.dequeue(tempGunnery, garbage)) {
        {
            cout << tempGunnery->getId() << (EGlist.isEmpty() ? "" : ", ");
            tempEgunnery.enqueue(tempGunnery, garbage);
        }
    }
    cout << "]\n";
    while (tempEgunnery.dequeue(tempGunnery, garbage))
        if (tempGunnery)
            EGlist.enqueue(tempGunnery, tempGunnery->getHealth() + tempGunnery->getPower());

    cout << "🌍 Earth Tanks Count is: " << TankList.getCount() << endl;
    cout << "ET [ ";
    ArrayStack<Tank *> tempTankList;
    Tank *tempTank{nullptr};
    while (TankList.pop(tempTank)) {
        {
            cout << tempTank->getId() << (TankList.isEmpty() ? "" : ", ");
            tempTankList.push(tempTank);
        }

    }
    cout << "]\n";
    while (tempTankList.pop(tempTank))
        if (tempTank)
            TankList.push(tempTank);

}

unit *earthArmy::getUnit(Type type) {
    switch (type) {
        case EarthSoldier: {
            Esoldier *temp{nullptr};
            if (ESlist.dequeue(temp)) {
                return temp;
            }
            return nullptr;
        }
        case EarthTank: {
            Tank *temp{nullptr};
            if (TankList.pop(temp)) {
                return temp;
            }
            return nullptr;
        }
        case Gunnery: {
            Egunnery *temp{nullptr};
            int garbage;
            if (EGlist.dequeue(temp, garbage)) {
                return temp;
            }
            return nullptr;

        }
    };
    return nullptr;
}

unit *earthArmy::getAnEnemyFor(Type attackersType, int enemyType) {
    switch (attackersType) {
        case alienSoldier:
            return getUnit(EarthSoldier);
        case MonsterType:;
            if (!enemyType)
                return getUnit(EarthTank);
            else
                return getUnit(EarthSoldier);
        case DronePair:
            if (!enemyType)
                return getUnit(EarthTank);
            else
                return getUnit(Gunnery);
    }
    return nullptr;
}

int earthArmy::getEarthSoldierCount() {
    return ESlist.getCount();
}

int earthArmy::getEarthTankCount() {
    return TankList.getCount();
}

int earthArmy::getEarthGunneryCount() {
    return EGlist.getCount();
}


/// @details returns a randomUnit and removes it from its adt.
unit *earthArmy::getRandomUnit() {
    auto random_number = rand() % 3;
    return getUnit(static_cast<Type>(random_number));
}