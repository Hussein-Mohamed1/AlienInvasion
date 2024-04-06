//
// Created by youss on 3/30/2024.
//
#pragma once

#include "simulationManager.h"
#include "./units/alienArmy.h"
#include "./units/earthArmy.h"
#include "./units/unit.h"


simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy();
    earthArmyPtr = new earthArmy();
    srand(time(0));

}

void simulationManager::updateSimulation(int timestep) {

    manageadding(timestep);

    ///@details From here the fighting logic starts
/// @note totalNumOfUnits is passed by reference
//    unit *earthUnit = earthArmyPtr->getRandomUnit();
//    unit *alienUnit{nullptr};
//    bool enqueuedOnce = false;
//    if (earthUnit)
//        /// @notice If there getRandomUnit returns a nullptr then no fighting occurs
//        for (int i = 0; i < earthUnit->getAttackCapacity(); ++i) {
//            alienUnit = alienArmyPtr->getRandomUnit();
//            if (earthUnit->damageEnemy(alienUnit)) {
//                showStats(earthUnit, alienUnit); // note this executes only in interactive mode
//                /// @note this order should be maintained as the earthUnit must added to the queue first
//                if (!enqueuedOnce) {
//                    enqueuedOnce = true;
//                    tempList.enqueue(earthUnit);
//                }
//                tempList.enqueue(alienUnit);
//            }
//        }
//    earthUnit = nullptr;
//    alienUnit = alienArmyPtr->getRandomUnit();
//    enqueuedOnce = false;
//
//    if (alienUnit)
//        /// @notice If there getRandomUnit returns a nullptr then no fighting occurs
//        for (int i = 0; i < alienUnit->getAttackCapacity(); ++i) {
//            earthUnit = earthArmyPtr->getRandomUnit();
//            if (alienUnit->damageEnemy(earthUnit)) {
//                showStats(alienUnit, earthUnit); // note this executes only in interactive mode
//                /// @note this order should be maintained as the earthUnit must added to the queue first
//                if (!enqueuedOnce) {
//                    enqueuedOnce = true;
//                    tempList.enqueue(alienUnit);
//                }
//                tempList.enqueue(earthUnit);
//            }
//        }

}

///@details adds the unit to the earth army
void simulationManager::addNewUnit(unit *newUnit) {

    if (newUnit) {
        if (newUnit->getType() == EarthSoldier) {
            earthArmyPtr->addUnit(newUnit);
            return;
        }
        if (newUnit->getType() == EarthTank) {
            earthArmyPtr->addUnit(newUnit);
            return;
        };
        if (newUnit->getType() == Gunnery) {
            earthArmyPtr->addUnit(newUnit);
            return;
        }

        ///@details adds the unit to the alien army
        if (newUnit->getType() == alienSoldier) {
            alienArmyPtr->addUnit(newUnit);
            return;
        }
        if (newUnit->getType() == MonsterType) {
            alienArmyPtr->addUnit(newUnit);
            return;
        }

        if (newUnit->getType() == DronePair) {
            alienArmyPtr->
                    addUnit(newUnit);
            return;
        }
    }
}

int simulationManager::getAlienUnitCount() {
    return alienArmyPtr->getUnitCount();
}

int simulationManager::getEarthUnitCount() {
    return earthArmyPtr->getUnitCount();
}

///@param AttackingUnit: The unit attacking.
///@param DamagedUnit: The unit being attacked.
void simulationManager::showStats(unit *AttackingUnit, unit *DamagedUnit) const {
    if (operationModeVal == Interactive)
        if (AttackingUnit && DamagedUnit)
            cout << AttackingUnit->getId() << " " << AttackingUnit->getType() << " has attacked" << DamagedUnit->getId()
                 << " " << DamagedUnit->getType() << endl;
}

void simulationManager::manageadding(int timestep) {
    if (RandomGenerator->creatEunits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++)
        {
            addNewUnit(RandomGenerator->generatUnit(Earthunit , timestep));
        }
    }
    if (RandomGenerator->creatAunits())
    {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++)
        {
            addNewUnit(RandomGenerator->generatUnit(Alienunit, timestep));
        }
    }
}


void simulationManager::phase12TestFunction(int x) 
{
    if (x >= 0 & x <= 10)
    {
        cout << "Picking an earth Soldier.\n";
        unit *Soldier = earthArmyPtr->getUnit(EarthSoldier);
        if (Soldier)
        {
            Soldier->print();
            cout << "\nEarth Units Count after removing soldier is " << earthArmyPtr->getUnitCount();
            earthArmyPtr->addUnit(Soldier);
            cout << "And requeuing it. New count is:" << earthArmyPtr->getUnitCount();
        }
        else cout << "No soldiers.";
    }
    else if (x > 10 & x <= 20)
    {
        cout << "Picking an earth tank.\n";
        unit* tank = earthArmyPtr->getUnit(EarthTank);
        if (tank)
        {
            tank->print();
            // move it to killed list
        }
        else cout << "No tanks.";
    }
    else if (x > 20 & x <= 30)
    {

        cout << "Picking an earth gunnery.\n";
        unit* gunnery = earthArmyPtr->getUnit(Gunnery);
        if (gunnery)
        {
            gunnery->print();
            gunnery->setHealth(gunnery->getHealth() - gunnery->getHealth() / 2);
        }
        else cout << "No gunnerys.";
    }
    else if (x > 30 & x <= 40)
    {

        for (int i = 0; i < 5; i++)
        {
            cout << "Picking an alien soldier.\n";
            unit* soldier = earthArmyPtr->getUnit(alienSoldier);
            if (soldier)
            {
                soldier->print();
                cout << "\nAlien Units Count after removing soldier is " << alienArmyPtr->getUnitCount();
                soldier->setHealth(soldier->getHealth() - soldier->getHealth() / 2);
                //add it to temp list
                cout << "And requeuing it. New count is:" << alienArmyPtr->getUnitCount();
            }
            else
            {
                cout << "No soldiers.";
                break;
            }

        }
    }
    else if (x > 40 & x <= 50)
    {
        for (int i = 0 ; i < 5; i++)
        {
            cout << "Picking an alien monster.\n";
            unit* monster = earthArmyPtr->getUnit(MonsterType);
            if (monster)
            {
                monster->print();
                cout << "\nAlien Units Count after removing monster is " << alienArmyPtr->getUnitCount();
                earthArmyPtr->addUnit(monster);
                cout << "And requeuing it. New count is:" << alienArmyPtr->getUnitCount();
            }
            else
            {
                cout << "No monsters.";
                break;
            }
                
        }
    }
    else if (x > 50 & x <= 60)
    {

        for (int i = 0; i < 6; i++)
        {
            cout << "Picking an alien Drone.\n";
            unit* drone = earthArmyPtr->getUnit(DronePair);
            if (drone)
            {
                drone->print();
                cout << "\nAlien Units Count after removing drone is " << alienArmyPtr->getUnitCount();
                // add to killed list
                cout << "And requeuing it. New count is:" << alienArmyPtr->getUnitCount();
            }
            else
            {
                cout << "No drones.";
                break;
            }

        }
    }

                        
}

