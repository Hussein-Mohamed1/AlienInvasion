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
        switch (AlienUnit->getType()) {
            case alienSoldier :
                SoliderUnits.enqueue(dynamic_cast<ASolider *>(AlienUnit));
                return true;
            case DronePair:
                DroneUnits.enqueue(dynamic_cast<Drone *> (AlienUnit));
                return true;
            case MonsterType :
                Monster *MonsterUnit = dynamic_cast<Monster *>(AlienUnit);
                MonsterUnits[++currentMonstersIndex] = MonsterUnit;
                return true;
        }
        return false;
    }
}


void alienArmy::print() {
    LinkedQueue<ASolider *> TempASlist;
    ASolider *soldier;
    cout << "======================== Alien Army Alive units ==================================\n";
    cout << "👽 Alien Soldier Count is: " << SoliderUnits.getCount() << endl;
    cout << "AS [ ";
    while (SoliderUnits.dequeue(soldier)) {
        cout << soldier->getId() << (SoliderUnits.isEmpty() ?
                                     "" : ", ");
        TempASlist.enqueue(soldier);
    }
    cout << "]\n";
    while (TempASlist.dequeue(soldier))
        SoliderUnits.enqueue(soldier);


    cout << "👽 Alien Drone Count is: " << DroneUnits.getCount() << endl;
    cout << "AD [ ";
    Drone *tempDrone{nullptr};
    DoublyLinkedQueue<Drone *> tempDroneQueue;
    while (DroneUnits.dequeue(tempDrone)) {
        cout << tempDrone->getId() << (DroneUnits.isEmpty() ? "" : ", ");
        tempDroneQueue.enqueue(tempDrone);
    }
    cout << "]\n";
    while (tempDroneQueue.dequeue(tempDrone))
        DroneUnits.enqueue(tempDrone);

    cout << "👽 Alien Monster Count is: " << currentMonstersIndex + 1 << endl;
    cout << "AM [ ";
    for (int i = 0; i <= currentMonstersIndex; ++i) {
        cout << MonsterUnits[currentMonstersIndex]->getId() << (i == currentMonstersIndex
                                                                ? "" : ", ");
    }
    cout << "]\n";

}


unit *alienArmy::getUnit(Type type) {
    switch (type) {
        case alienSoldier: {
            ASolider *temp{nullptr};
            if (SoliderUnits.dequeue(temp))
                return temp;
            else return nullptr;
        }
        case DronePair: {
            Drone *temp{nullptr};
            if (DroneUnits.dequeue(temp))
                return temp;
            else return nullptr;
        }
        case MonsterType: {
            if (currentMonstersIndex != -1)
                return MonsterUnits[currentMonstersIndex--];
            else return nullptr;
        }
    };
    return nullptr;
}

int alienArmy::getCurrentAlienDroneCount() {
    return DroneUnits.getCount();
}

int alienArmy::getCurrentAlienSoldierCount() {
    return SoliderUnits.getCount();
}

int alienArmy::getCurrentMonstersIndex() const {
    return currentMonstersIndex;
}


/// @details returns a randomUnit and removes it from its adt.
unit *alienArmy::getRandomUnit() {
    auto random_number = rand() % 3 + 3;
    return getUnit(static_cast<Type>(random_number));
}

unit *alienArmy::getDronePair() {
    Drone *drone;
    if (DroneUnits.DoublyDequeue(drone))
        return drone;
    return nullptr;
}

unit *alienArmy::getAnEnemyFor(Type attackersType, int enemyType) {
    switch (attackersType) {
        case EarthTank:
            if (!enemyType)
                return getUnit(MonsterType);
            else
                return getUnit(alienSoldier);
        case EarthSoldier:
            return getUnit(alienSoldier);
        case Gunnery:
            if (!enemyType)
                return getDronePair();
            else
                return getUnit(MonsterType);
    }
    return nullptr;
}
