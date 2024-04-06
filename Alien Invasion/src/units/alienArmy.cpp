//
// Created by youss on 4/3/2024.
//

#include "alienArmy.h"
#include "Monster.h"
#include "ASolider.h"
#include "Drone.h"

unit* alienArmy::Attack(unit* enemy) 
{

}

bool alienArmy::addUnit(unit* AlienUnit) 
{
    Type UnitType = AlienUnit->getType();
    switch (UnitType)
    {
    case alienSoldier : 
        SoliderUnits.enqueue(dynamic_cast<ASolider*>(AlienUnit));
        return true;
    case DronePair:
        DroneUnuits.enqueue(dynamic_cast<Drone*> (AlienUnit));
        return true;
    case MonsterType :
        Monster* MonsterUnit = dynamic_cast<Monster*>(AlienUnit);    // 
        MonsterUnits[Index] = MonsterUnit;
        return true;
    }
    return false;
}

void alienArmy::removeUnit(unit*AlienUnit)
{

}

void alienArmy::print() const
{

}

unit* alienArmy::getRandomUnit() {
    auto random_number = rand() % 3 + 3;
    /// @todo implement this after alienUnits Have been implemented

    /// @todo Also get the new switch statements from earthArmy->getRandomUnit();
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
int alienArmy::Index = 0;
