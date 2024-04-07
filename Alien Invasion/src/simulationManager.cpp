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
    RandomGenerator = new randGen;
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
            alienArmyPtr->addUnit(newUnit);
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
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(Earthunit, timestep));
        }
    }
    if (RandomGenerator->creatAunits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(Alienunit, timestep));
        }
    }
}


void simulationManager::phase12TestFunction(int x) {
    earthArmyPtr->print();
    alienArmyPtr->print();
    cout << endl;
    if (x >= 0 & x <= 10) {
        cout << "🌍 Picking an 💂 Earth Soldier.\n";
        unit *soldier = earthArmyPtr->getUnit(EarthSoldier);
        if (soldier) {
            soldier->print();
            cout << "\n🌍 Earth Soldier Count after removing soldier is " << earthArmyPtr->getEarthSoldierCount();
            earthArmyPtr->addUnit(soldier);
            cout << "\n➕ And requeuing it. New count is: " << earthArmyPtr->getEarthSoldierCount();
        } else {
            cout << "⚠️ No soldiers.";
        }
    } else if (x > 10 & x <= 20) {
        cout << "🌍 Picking an 🚛 Earth Tank.\n";
        unit *tank = earthArmyPtr->getUnit(EarthTank);
        cout << "🌍 Current Earth Tank units is: " << earthArmyPtr->getEarthTankCount() << endl;
        if (tank) {
            tank->print();
            cout << "\n💉 Setting its health to 50%\n";
            tank->setHealth(0.5 * tank->getHealth());
            tank->print();
            cout << "🌍 New count after re-inserting the tank is: " << earthArmyPtr->getEarthTankCount()
                 << endl;
            ///@todo move it to the killed list
        } else {
            cout << "⚠️ No tanks.";
        }
    } else if (x > 20 & x <= 30) {
        cout << "🌍 Picking an 💣 Earth Gunnery.\n";
        unit *gunnery = earthArmyPtr->getUnit(Gunnery);
        if (gunnery) {
            gunnery->print();
            gunnery->setHealth(gunnery->getHealth() - gunnery->getHealth() / 2);
        } else {
            cout << "⚠️ No gunnerys.";
        }
    } else if (x > 30 & x <= 40) {
        for (int i = 0; i < 5; i++) {
            cout << "👽 Picking an 👾 Alien Soldier.\n";
            unit *soldier = alienArmyPtr->getUnit(alienSoldier);
            if (soldier) {
                soldier->print();
                cout << "\n👽 Alien Soldiers Count after removing soldier is "
                     << alienArmyPtr->getAleinSoldierCount() + i;
                soldier->setHealth(soldier->getHealth() - soldier->getHealth() / 2);
                cout << "\n➕ And requeuing it. New count is: " << alienArmyPtr->getAleinSoldierCount() + i + 1;
                ///@todo add it to temp list
            } else {
                cout << "⚠️ No soldiers.";
                break;
            }
        }
    } else if (x > 40 & x <= 50) {
        for (int i = 0; i < 5; i++) {
            cout << "👽 Picking an 👹 Alien Monster.\n";
            unit *monster = alienArmyPtr->getUnit(MonsterType);
            if (monster) {
                monster->print();
                cout << "\n👽 Alien Monsters Count after removing monster is " << alienArmyPtr->getAlienMonsterCount();
                earthArmyPtr->addUnit(monster);
                cout << "\n➕ And re-queuing it. New count is: " << alienArmyPtr->getAlienMonsterCount();
            } else {
                cout << "⚠️ No monsters.";
                break;
            }
        }
    } else if (x > 50 & x <= 60) {
        for (int i = 0; i < 6; i++) {
            cout << "👽 Picking an 🛸 Alien Drone.\n";
            unit *drone = alienArmyPtr->getUnit(DronePair);
            if (drone) {
                drone->print();
                cout << "\n👽 Alien Drones Count after removing drone is " << alienArmyPtr->getAlienDroneCount() + i;
                ///@todo  add to killed list
                cout << "\n➕ And requeuing it. New count is: " << alienArmyPtr->getAlienDroneCount() + i + 1;
            } else {
                cout << "⚠️ No drones.";
                break;
            }
        }
    }
}

