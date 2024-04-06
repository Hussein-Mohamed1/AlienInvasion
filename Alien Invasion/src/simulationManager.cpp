//
// Created by youss on 3/30/2024.
//
#pragma once

#include "simulationManager.h"
#include "alienArmy.h"
#include "earthArmy.h"
#include "unit.h"


simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy();
    earthArmyPtr = new earthArmy();
    srand(time(0));

}

void simulationManager::updateSimulation() {

    /**
       @code
       int totalNumOfUnits{1};
       for(int i =0;i<totalNumOfUnits;i++)
          addNewUnit(randGenObj(totalNumOfUnits));
       @endcode
     */
/// @note totalNumOfUnits is passed by reference
    unit *earthUnit = earthArmyPtr->getRandomUnit();
    unit *alienUnit{nullptr};
    bool enqueuedOnce = false;
    if (earthUnit)
        /// @notice If there getRandomUnit returns a nullptr then no fighting occurs
        for (int i = 0; i < earthUnit->getAttackCapacity(); ++i) {
            alienUnit = alienArmyPtr->getRandomUnit();
            if (earthUnit->damageEnemy(alienUnit)) {
                showStats(earthUnit, alienUnit); // note this executes only in interactive mode
                /// @note this order should be maintained as the earthUnit must added to the queue first
                if (!enqueuedOnce) {
                    enqueuedOnce = true;
                    tempList.enqueue(earthUnit);
                }
                tempList.enqueue(alienUnit);
            }
        }
    earthUnit = nullptr;
    alienUnit = alienArmyPtr->getRandomUnit();
    enqueuedOnce = false;

    if (alienUnit)
        /// @notice If there getRandomUnit returns a nullptr then no fighting occurs
        for (int i = 0; i < alienUnit->getAttackCapacity(); ++i) {
            earthUnit = earthArmyPtr->getRandomUnit();
            if (alienUnit->damageEnemy(earthUnit)) {
                showStats(alienUnit, earthUnit); // note this executes only in interactive mode
                /// @note this order should be maintained as the earthUnit must added to the queue first
                if (!enqueuedOnce) {
                    enqueuedOnce = true;
                    tempList.enqueue(alienUnit);
                }
                tempList.enqueue(earthUnit);
            }
        }

}

void simulationManager::addNewUnit(unit *newUnit) {

    ///@details adds the unit to the earth army
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
void simulationManager::manageadding(fstream* infile)
{
	RandomGenerator = new randGen();
	{
		for (int i{}; i <RandomGenerator->getnumofES() ; i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(Es)
		}
		for (int i{}; i < RandomGenerator->getnumofET(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(ET)
		}
		for (int i{}; i < RandomGenerator->getnumofEG(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(EG)
		}
		for (int i{}; i < RandomGenerator->getnumofAS(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AS)
		}
		for (int i{}; i < RandomGenerator->getnumofAM(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AM)
		}
		for (int i{}; i < RandomGenerator->getnumofAD(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AD)
		}
	}

}
