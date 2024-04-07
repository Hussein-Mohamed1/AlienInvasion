//
// Created by youss on 4/3/2024.
//

#include "alienArmy.h"
#include "Monster.h"
#include "ASolider.h"
#include "Drone.h"

unit *alienArmy::Attack(unit *enemy) {
    return nullptr;
}

bool alienArmy::addUnit(unit *AlienUnit) {

    if (AlienUnit) {
        Type UnitType = AlienUnit->getType();
        switch (UnitType) {
            case alienSoldier :
                SoliderUnits.enqueue(dynamic_cast<ASolider *>(AlienUnit));
                aleinSoldierCount++;
                return true;
            case DronePair:
                DroneUnits.enqueue(dynamic_cast<Drone *> (AlienUnit));
                alienDroneCount++;
                return true;
            case MonsterType :
                Monster *MonsterUnit = dynamic_cast<Monster *>(AlienUnit);
                MonsterUnits[alienMonsterCount++] = MonsterUnit;
                return true;
        }
        return false;
    }
}

void alienArmy::removeUnit(unit *AlienUnit) {

}

void alienArmy::print() {
    LinkedQueue<ASolider *> TempASlist;
    ASolider *soldier;
    cout << "======================== Alien Army Alive units ==================================\n";
    cout << "👽 Alien Soldier Count is: " << getAleinSoldierCount() << endl;
    cout << "AS [ ";
    while (SoliderUnits.dequeue(soldier)) {
        cout << soldier->getId() << ", ";
        TempASlist.enqueue(soldier);
    }
    cout << "]\n";
    while (TempASlist.dequeue(soldier))
        SoliderUnits.enqueue(soldier);


    cout << "👽 Alien Drone Count is: " << getAlienDroneCount() << endl;
    cout << "AD [ ";
    Drone *tempDrone{nullptr};
    DoublyLinkedQueue<Drone *> tempDroneQueue;
    while (DroneUnits.dequeue(tempDrone)) {
        cout << tempDrone->getId() << ", ";
        tempDroneQueue.enqueue(tempDrone);
    }
    cout << "]\n";
    while (tempDroneQueue.dequeue(tempDrone))
        DroneUnits.enqueue(tempDrone);

    cout << "👽 Alien Monster Count is: " << getAlienMonsterCount() << endl;
    cout << "AM [ ";
    for (int i = 0; i < alienMonsterCount; ++i) {
        cout << MonsterUnits[alienMonsterCount]->getId() << ", ";
    }
    cout << "]\n";

}

unit *alienArmy::getRandomUnit() {
    auto random_number = rand() % 3 + 3;
    /// @todo implement this after alienUnits Have been implemented

    /// @todo Also get the new switch statements from earthArmy->getRandomUnit();
    ///@todo Also decrement the count

    //    switch (random_number) {
//        case MonsterType: {
//            Monster *removedTank;
//            TankList.pop(removedTank);
//            return removedTank;
//        }
//        case DronePair: {
//            Drone *removedSoldier;
//            ESlist.dequeue(removedSoldier);
//            return removedSoldier;
//        }
//        case alienSoldier: {
//            ASolider *removedGunnery;
//            int priority{0};
//            EGlist.dequeue(removedGunnery, priority);
//            return removedGunnery;
//        }
//    }
    return nullptr;
}

int alienArmy::alienMonsterCount = 0;

unit *alienArmy::getUnit(Type type) {
    switch (type) {
        case alienSoldier: {
            ASolider *temp{nullptr};
            if (SoliderUnits.dequeue(temp))
                aleinSoldierCount--;
            return temp;
        }
        case DronePair: {
            Drone *temp{nullptr};
            if (DroneUnits.dequeue(temp))
                alienDroneCount--;
            return temp;
        }
        case MonsterType: {
            if (MonsterUnits) {
                return MonsterUnits[alienMonsterCount--];
            } else return nullptr;
        }
    };
}

int alienArmy::getAlienMonsterCount() const {
    return alienMonsterCount;
}

int alienArmy::getAleinSoldierCount() const {
    return aleinSoldierCount;
}

int alienArmy::getAlienDroneCount() const {
    return alienDroneCount;
}
