//
// Created by youss on 3/30/2024.
//
#pragma once

#include "simulationManager.h"
#include "./units/alienArmy.h"
#include "./units/earthArmy.h"
#include "./units/unit.h"
#include "windows.h"
#include "iostream"

simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy();
    earthArmyPtr = new earthArmy();
    srand(time(nullptr));
    RandomGenerator = new randGen;
    OutputFile.open("output.txt", std::ios::app | std::ios::out);

    // Check if the file was opened successfully
    if (!OutputFile) {
        cout << "Unable to open file for writing." << endl;
        // Handle the error appropriately, e.g., by throwing an exception
        throw std::runtime_error("Failed to open output file.");
    }

    // Write data to the file in the constructor
    OutputFile << "Td     ID      Tj      Df      Dd      Db" << endl;
}

void simulationManager::updateSimulation(int timestep) {
void simulationManager::handleUnit(unit *attackingUnit, unit *&defendingUnit, Army *defendingArmy) {
    bool enqueuedOnce = false;
    if (attackingUnit) {
        for (int i = 0; i < attackingUnit->getAttackCapacity(); ++i) {
            defendingUnit = defendingArmy->getRandomUnit();
            if (attackingUnit->damageEnemy(defendingUnit)) {
                showStats(attackingUnit, defendingUnit);
                if (!enqueuedOnce) {
                    enqueuedOnce = true;
                    tempList.enqueue(attackingUnit);
                }
                tempList.enqueue(defendingUnit);
            }
        }
    }
}

void simulationManager::updateSimulation(int timestep) {
    manageAdding(timestep);
 
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

    unit *earthUnit = earthArmyPtr->getRandomUnit();
    unit *alienUnit = alienArmyPtr->getRandomUnit();

    handleUnit(earthUnit, alienUnit, alienArmyPtr);
    handleUnit(alienUnit, earthUnit, earthArmyPtr);
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


///@param AttackingUnit: The unit attacking.
///@param DamagedUnit: The unit being attacked.
void simulationManager::showStats(unit *AttackingUnit, unit *DamagedUnit) const {
    if (operationModeVal == Interactive)
        if (AttackingUnit && DamagedUnit)
            cout << AttackingUnit->getId() << " " << AttackingUnit->getType() << " has attacked" << DamagedUnit->getId()
                 << " " << DamagedUnit->getType() << endl;
}

void simulationManager::manageAdding(int timestep) {
    if (RandomGenerator->creatEarthUnits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(earthUnit, timestep));
        }
    }
    if (RandomGenerator->creatAlienUnits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(alienUnit, timestep));
        }
    }
}


void simulationManager::phase12TestFunction(int x) {
    LinkedQueue<unit *> KilledList;
    int numofkilledunit = 0;
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
            cout << "\n➕ And re-queuing it. New count is: " << earthArmyPtr->getEarthSoldierCount() << endl;
        } else {
            cout << "⚠️ No soldiers.\n";
        }
    } else if (x > 10 & x <= 20) {
        cout << "🌍 Picking an 🚛 Earth Tank.\n";
        unit *tank = earthArmyPtr->getUnit(EarthTank);
        cout << "🌍 Current Earth Tank units is: " << earthArmyPtr->getEarthTankCount() << endl;
        if (tank) {
            cout << "☠️ Killed Tank is ---> ";
            tank->print();
            KilledList.enqueue(tank);
            numofkilledunit++;
            cout << "🌍 New count after Killed the tank is: " << earthArmyPtr->getEarthTankCount()
                 << endl;
        } else {
            cout << "⚠️ No tanks.\n";
        }
    } else if (x > 20 & x <= 30) {
        cout << "🌍 Picking an 💣 Earth Gunnery.\n";
        unit *gunnery = earthArmyPtr->getUnit(Gunnery);
        if (gunnery) {
            gunnery->print();
            gunnery->setHealth(gunnery->getHealth() - gunnery->getHealth() / 2);
        } else {
            cout << "⚠️ No gunnerys.\n";
        }
    } else if (x > 30 & x <= 40) {
        for (int i = 0; i < 5; i++) {
            cout << "👽 Picking an 👾 Alien Soldier.\n";
            unit *soldier = alienArmyPtr->getUnit(alienSoldier);
            if (soldier) {
                soldier->print();
                cout << "\n👽 Alien Soldiers Count after removing soldier is "
                        << alienArmyPtr->getAlienSoldierCount() + i;
                soldier->setHealth(soldier->getHealth() - soldier->getHealth() / 2);
                cout << "\n➕ And re-queuing it. New count is: " << alienArmyPtr->getAlienSoldierCount() + i + 1 << endl;
                ///@todo add it to temp list
            } else {
                cout << "⚠️ No soldiers.\n";
                break;
            }
        }
    } else if (x > 40 & x <= 50) {
        for (int i = 0; i < 5; i++) {
            cout << "👽 Picking an 👹 Alien Monster.\n";
            unit *monster = alienArmyPtr->getUnit(MonsterType);
            if (monster) {
                monster->print();
                cout << "\n👽 Alien Monsters Count after removing monster is "
                     << alienArmyPtr->getCurrentMonstersIndex() + 1;
                alienArmyPtr->addUnit(monster);
                cout << "\n➕ And re-queuing it. New count is: " << alienArmyPtr->getCurrentMonstersIndex() + 1 << endl;
            } else {
                cout << "⚠️ No monsters.\n";
                break;
            }
        }
    } else if (x > 50 & x <= 60) {
        unit *drone = nullptr;
        for (int i = 0; i < 6; i++) {
            cout << "👽 Picking an 🛸 Alien Drone.\n";
            drone = alienArmyPtr->getUnit(DronePair);
            if (drone) {
                cout << "☠️ killed Drone is ---> ";
                drone->print();
                KilledList.enqueue(drone);
                numofkilledunit++;
                cout << "\n👽 Alien Drones Count after removing drone is " << alienArmyPtr->getAlienDroneCount() + i
                     << endl;
            } else {
                cout << "⚠️ No drones.\n";
                break;
            }
        }
    }
int simulationManager::getAlienArmyUnitsCount() const {
    return alienArmyPtr->getAlienSoldierCount() + alienArmyPtr->getAlienDroneCount() +
           alienArmyPtr->getCurrentMonstersIndex() + 1;
}

int simulationManager::getEarthArmyUnitsCount() const {
    return earthArmyPtr->getEarthGunneryCount() + earthArmyPtr->getEarthSoldierCount() +
           earthArmyPtr->getEarthTankCount();
}

void simulationManager::intro() {
    std::cout
            << "\033[48;5;0m   \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄▄\033[48;5;0m                   \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄▄▄\033[38;5;15;48;5;232m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;0m                                                                       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m     \033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;0m                     \033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m                                                                       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m     \033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;0m                      \033[38;5;15;48;5;0m▄\033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m         \033[38;5;15;48;5;0m▄▄▄▄▄▄▄▄▄▄▄▄\033[48;5;0m                                                \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                                     \033[48;5;15m \033[48;5;0m     \033[48;5;15m               \033[38;5;0;48;5;15m▄▄▄\033[48;5;0m  \033[38;5;15;48;5;0m▄\033[48;5;0m                         \033[38;5;15;48;5;0m▄\033[48;5;0m                \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m   \033[38;5;15;48;5;0m▄▄▄▄\033[48;5;0m                               \033[38;5;15;48;5;0m▄\033[38;5;15;48;5;235m▄\033[48;5;15m                \033[38;5;0;48;5;15m▄\033[48;5;0m     \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄\033[48;5;0m                       \033[38;5;15;48;5;0m▄▄▄\033[48;5;0m  \033[38;5;15;48;5;0m▄\033[48;5;0m            \033[m\n";
    Sleep(50);
    cout <<
         "\033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;0;48;5;15m▄▄▄\033[48;5;15m    \033[38;5;15;48;5;0m▄▄▄\033[48;5;0m                     \033[38;5;15;48;5;0m▄\033[48;5;15m             \033[38;5;0;48;5;15m▄\033[48;5;15m      \033[38;5;15;48;5;0m▄\033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m \033[48;5;15m  \033[38;5;0;48;5;15m▄▄\033[48;5;0m                     \033[38;5;0;48;5;15m▄\033[48;5;0m                   \033[m\n";
    Sleep(50);
    cout <<
         "\033[38;5;15;48;5;0m▄▄▄\033[38;5;0;48;5;15m▄▄▄▄▄\033[48;5;15m     \033[48;5;0m  \033[48;5;15m \033[38;5;15;48;5;0m▄▄\033[48;5;0m                \033[48;5;15m                 \033[38;5;15;48;5;0m▄\033[48;5;15m       \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m  \033[38;5;15;48;5;0m▄▄\033[48;5;0m                                       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m       \033[38;5;0;48;5;15m▄▄▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m     \033[38;5;15;48;5;0m▄\033[48;5;0m          \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄▄\033[48;5;15m              \033[48;5;0m \033[48;5;15m      \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄▄\033[48;5;0m    \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;0;48;5;15m▄▄\033[48;5;15m  \033[48;5;0m                        \033[38;5;15;48;5;0m▄▄\033[48;5;0m             \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m               \033[38;5;0;48;5;15m▄▄\033[48;5;0m  \033[48;5;15m  \033[38;5;251;48;5;0m▄\033[38;5;15;48;5;0m▄\033[48;5;0m        \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;15m           \033[38;5;15;48;5;0m▄\033[48;5;15m     \033[38;5;0;48;5;15m▄▄\033[38;5;15;48;5;0m▄\033[48;5;0m   \033[38;5;15;48;5;0m▄\033[48;5;15m     \033[38;5;0;48;5;15m▄▄\033[48;5;0m                    \033[38;5;15;48;5;0m▄\033[48;5;0m  \033[38;5;15;48;5;237m▄\033[48;5;15m    \033[48;5;0m            \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m               \033[38;5;0;48;5;15m▄\033[48;5;0m  \033[38;5;15;48;5;0m▄▄\033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m       \033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;0m   \033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m      \033[38;5;15;48;5;0m▄\033[48;5;15m        \033[48;5;0m \033[48;5;15m \033[48;5;0m \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄\033[38;5;253;48;5;0m▄\033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m                \033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m   \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄▄▄▄▄\033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m        \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m          \033[38;5;15;48;5;0m▄▄\033[48;5;0m    \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄▄▄\033[48;5;0m         \033[38;5;15;48;5;0m▄\033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;15m           \033[38;5;253;48;5;15m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;249;48;5;15m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;0m       \033[38;5;15;48;5;0m▄▄▄▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m \033[48;5;0m \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄▄\033[48;5;15m      \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m         \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                            \033[38;5;15;48;5;245m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;15m      \033[48;5;0m \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄▄▄\033[48;5;15m \033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[38;5;233;48;5;0m▄\033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;15m     \033[48;5;0m \033[48;5;15m  \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[48;5;0m \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;15m \033[48;5;0m \033[48;5;15m \033[48;5;0m  \033[48;5;15m \033[48;5;0m \033[48;5;15m     \033[38;5;15;48;5;0m▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m            \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m             \033[38;5;15;48;5;0m▄▄▄\033[48;5;0m           \033[38;5;15;48;5;0m▄\033[38;5;0;48;5;15m▄▄▄▄▄\033[48;5;15m \033[38;5;233;48;5;0m▄\033[38;5;15;48;5;0m▄▄\033[48;5;0m \033[38;5;15;48;5;0m▄▄\033[48;5;0m  \033[48;5;15m   \033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[48;5;0m \033[48;5;15m     \033[48;5;0m  \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;15m   \033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[48;5;15m \033[48;5;0m \033[48;5;15m \033[48;5;0m \033[48;5;15m   \033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m  \033[38;5;15;48;5;0m▄\033[48;5;15m         \033[38;5;0;48;5;15m▄\033[38;5;0;48;5;8m▄\033[48;5;0m        \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m            \033[38;5;15;48;5;0m▄\033[48;5;15m   \033[48;5;0m   \033[38;5;15;48;5;0m▄\033[48;5;0m     \033[38;5;15;48;5;0m▄▄\033[48;5;0m \033[48;5;15m    \033[48;5;0m \033[38;5;0;48;5;254m▄\033[38;5;15;48;5;0m▄\033[48;5;15m  \033[48;5;0m \033[48;5;15m \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m   \033[48;5;0m \033[48;5;15m   \033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;15m   \033[48;5;0m \033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;15;48;5;247m▄\033[48;5;15m \033[48;5;0m \033[48;5;15m   \033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;0m   \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;0m       \033[38;5;0;48;5;15m▄\033[48;5;0m        \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m            \033[48;5;15m    \033[48;5;0m  \033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;0m    \033[48;5;15m  \033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m \033[48;5;15m \033[48;5;0m \033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m \033[48;5;15m \033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[48;5;0m \033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m \033[48;5;15m    \033[38;5;15;48;5;0m▄\033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m    \033[48;5;0m \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m  \033[38;5;0;48;5;15m▄▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;0m  \033[38;5;0;48;5;248m▄\033[48;5;0m \033[48;5;15m   \033[48;5;0m   \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄▄▄\033[48;5;0m         \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m           \033[48;5;15m     \033[48;5;0m  \033[48;5;15m  \033[48;5;0m    \033[38;5;238;48;5;0m▄\033[48;5;15m \033[48;5;0m  \033[48;5;15m  \033[38;5;0;48;5;15m▄▄\033[48;5;0m  \033[48;5;15m \033[48;5;0m \033[48;5;15m   \033[48;5;0m  \033[48;5;15m   \033[48;5;0m \033[38;5;15;48;5;243m▄\033[48;5;15m \033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[38;5;237;48;5;0m▄\033[48;5;15m   \033[48;5;0m \033[48;5;15m  \033[48;5;0m \033[48;5;15m     \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;0m                 \033[38;5;0;48;5;15m▄\033[38;5;252;48;5;0m▄\033[38;5;0;48;5;250m▄\033[38;5;15;48;5;0m▄\033[48;5;0m     \033[48;5;15m     \033[48;5;0m       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m          \033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[48;5;0m  \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m    \033[48;5;15m  \033[48;5;0m  \033[48;5;15m  \033[38;5;15;48;5;0m▄▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m  \033[38;5;0;48;5;15m▄▄\033[48;5;0m  \033[48;5;15m   \033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[48;5;15m  \033[48;5;0m \033[38;5;15;48;5;234m▄\033[38;5;0;48;5;15m▄▄\033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m     \033[38;5;15;48;5;0m▄\033[48;5;0m \033[38;5;237;48;5;0m▄\033[38;5;15;48;5;0m▄\033[48;5;0m \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;0m       \033[38;5;0;48;5;8m▄\033[48;5;0m         \033[48;5;15m    \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m          \033[48;5;15m      \033[48;5;0m  \033[48;5;15m \033[38;5;15;48;5;0m▄▄▄▄\033[48;5;0m \033[48;5;15m  \033[48;5;0m  \033[38;5;0;48;5;15m▄▄▄▄\033[38;5;15;48;5;0m▄▄▄▄\033[48;5;0m \033[38;5;0;48;5;188m▄\033[38;5;0;48;5;15m▄▄\033[48;5;0m \033[38;5;0;48;5;15m▄▄▄\033[48;5;0m \033[38;5;0;48;5;15m▄▄\033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;15m \033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m     \033[38;5;0;48;5;8m▄\033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;0m    \033[38;5;0;48;5;15m▄▄\033[48;5;0m           \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;0m▄▄\033[48;5;15m      \033[48;5;0m     \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m         \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄▄\033[48;5;15m  \033[48;5;0m \033[38;5;0;48;5;15m▄▄▄▄▄\033[48;5;0m   \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄▄\033[48;5;0m \033[48;5;15m \033[48;5;0m       \033[48;5;15m        \033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄\033[48;5;0m   \033[38;5;15;48;5;0m▄▄▄▄▄▄▄\033[48;5;15m \033[48;5;0m  \033[38;5;237;48;5;0m▄\033[48;5;0m              \033[48;5;15m        \033[38;5;15;48;5;0m▄\033[48;5;0m    \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                      \033[38;5;0;48;5;15m▄▄▄▄▄▄\033[48;5;15m   \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄\033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m \033[38;5;0;48;5;15m▄▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m    \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m  \033[38;5;15;48;5;0m▄▄▄▄\033[48;5;15m            \033[38;5;0;48;5;15m▄▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m         \033[48;5;15m       \033[38;5;0;48;5;15m▄▄\033[48;5;0m    \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                             \033[48;5;15m      \033[48;5;0m  \033[48;5;15m     \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;237;48;5;0m▄\033[48;5;0m    \033[38;5;15;48;5;0m▄▄\033[48;5;0m \033[38;5;0;48;5;242m▄\033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄▄\033[48;5;15m    \033[38;5;15;48;5;0m▄\033[48;5;15m      \033[48;5;0m   \033[38;5;0;48;5;15m▄\033[38;5;0;48;5;8m▄\033[48;5;0m \033[38;5;0;48;5;15m▄▄▄▄\033[48;5;0m       \033[38;5;15;48;5;0m▄\033[48;5;15m        \033[48;5;0m  \033[38;5;0;48;5;15m▄\033[48;5;0m   \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                              \033[38;5;0;48;5;15m▄\033[48;5;15m   \033[48;5;0m  \033[38;5;0;48;5;15m▄▄\033[38;5;15;48;5;59m▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄▄▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄\033[38;5;15;48;5;254m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄▄\033[38;5;15;48;5;235m▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄\033[48;5;15m          \033[38;5;0;48;5;15m▄\033[48;5;0m               \033[38;5;15;48;5;0m▄▄\033[48;5;15m  \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m     \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m               \033[38;5;0;48;5;15m▄\033[48;5;15m \033[48;5;0m              \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;15;48;5;0m▄▄▄\033[38;5;253;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄▄▄▄\033[48;5;15m  \033[38;5;15;48;5;0m▄▄\033[48;5;15m    \033[38;5;243;48;5;15m▄\033[48;5;15m        \033[38;5;0;48;5;15m▄▄\033[48;5;0m            \033[38;5;15;48;5;0m▄▄▄\033[48;5;15m   \033[38;5;0;48;5;15m▄\033[48;5;0m  \033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m      \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m               \033[38;5;15;48;5;0m▄\033[38;5;0;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;0m               \033[38;5;0;48;5;15m▄\033[48;5;15m    \033[48;5;0m \033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;0m    \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[48;5;0m \033[48;5;15m  \033[38;5;15;48;5;0m▄▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;15m            \033[38;5;232;48;5;15m▄\033[48;5;0m                \033[38;5;0;48;5;15m▄\033[48;5;0m       \033[48;5;15m        \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m        \033[38;5;15;48;5;0m▄▄\033[48;5;15m          \033[38;5;15;48;5;0m▄\033[48;5;0m             \033[38;5;0;48;5;15m▄▄\033[48;5;15m     \033[38;5;15;48;5;0m▄▄\033[48;5;15m \033[48;5;0m \033[38;5;15;48;5;0m▄\033[48;5;0m   \033[38;5;0;48;5;15m▄\033[48;5;0m \033[38;5;15;48;5;253m▄\033[48;5;15m                  \033[48;5;0m                     \033[38;5;15;48;5;0m▄\033[48;5;15m        \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                                     \033[38;5;0;48;5;15m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;15m  \033[38;5;15;48;5;0m▄\033[38;5;248;48;5;15m▄\033[38;5;15;48;5;0m▄\033[48;5;15m                    \033[38;5;0;48;5;15m▄▄\033[48;5;0m                    \033[38;5;15;48;5;0m▄\033[48;5;15m         \033[38;5;0;48;5;15m▄\033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                               \033[38;5;0;48;5;15m▄\033[48;5;0m        \033[38;5;0;48;5;15m▄\033[38;5;238;48;5;15m▄\033[48;5;15m        \033[38;5;0;48;5;15m▄▄\033[48;5;15m \033[38;5;0;48;5;15m▄\033[48;5;15m          \033[38;5;0;48;5;15m▄▄\033[48;5;0m                      \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[38;5;0;48;5;15m▄▄▄▄\033[48;5;15m   \033[38;5;0;48;5;15m▄\033[48;5;0m       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                            \033[38;5;15;48;5;0m▄\033[48;5;15m   \033[38;5;15;48;5;0m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m         \033[38;5;0;48;5;15m▄▄▄\033[48;5;15m     \033[38;5;15;48;5;0m▄\033[48;5;15m      \033[48;5;0m \033[38;5;0;48;5;15m▄▄\033[48;5;0m                           \033[38;5;0;48;5;15m▄\033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m     \033[48;5;15m \033[38;5;15;48;5;0m▄\033[48;5;0m       \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                           \033[38;5;0;48;5;15m▄▄\033[38;5;8;48;5;15m▄\033[38;5;0;48;5;15m▄▄▄▄\033[48;5;0m                                                        \033[48;5;15m  \033[48;5;0m     \033[38;5;0;48;5;15m▄\033[48;5;15m  \033[48;5;0m      \033[m\n";
    Sleep(50);
    cout <<
         "\033[48;5;0m                                                                                           \033[48;5;15m \033[48;5;0m      \033[38;5;0;48;5;15m▄\033[48;5;15m \033[48;5;0m      \033[m";
    cout << "\n"
            "▄▀█ █░░ █ █▀▀ █▄░█   █ █▄░█ █░█ ▄▀█ █▀ █ █▀█ █▄░█   █▀ █ █▀▄▀█ █░█ █░░ ▄▀█ ▀█▀ █▀█ █▀█ ░   █▀█ █▀█ █▀▀ █▀ █▀\n";
    Sleep(50);
    cout <<
         "█▀█ █▄▄ █ ██▄ █░▀█   █ █░▀█ ▀▄▀ █▀█ ▄█ █ █▄█ █░▀█   ▄█ █ █░▀░█ █▄█ █▄▄ █▀█ ░█░ █▄█ █▀▄ █   █▀▀ █▀▄ ██▄ ▄█ ▄█\n";
    Sleep(50);
    cout <<
         "\n"
         "█▀▀ █▄░█ ▀█▀ █▀▀ █▀█   ▀█▀ █▀█   █▀█ █░░ ▄▀█ █▄█ █\n";
    Sleep(50);
    cout <<
         "██▄ █░▀█ ░█░ ██▄ █▀▄   ░█░ █▄█   █▀▀ █▄▄ █▀█ ░█░ ▄";
    Sleep(500);
    cin.get();
    for (int i = 0; i < 30; ++i) {
        cout << "\x1b[1F"; // Move to the beginning of the previous line
        cout << "\x1b[2K"; // Clear the entire line
        Sleep(50);
    }
}

void simulationManager::printKilledList() {
    unit *killedUnit = nullptr;
    LinkedQueue<unit *> temp;
    cout << "================ Killed Units ====================\n";
    cout << "💀 " << KilledList.getCount() << " Units killed [ ";
    while (!KilledList.isEmpty()) {
        KilledList.dequeue(killedUnit);
        temp.enqueue(killedUnit);
        if (killedUnit) {
            cout << killedUnit->getId() << " , ";
        }
    }
    cout << " ]\n";
    while (!temp.isEmpty()) {
        temp.dequeue(killedUnit);
        KilledList.enqueue(killedUnit);
    }

}

void simulationManager::printTempList() {
    unit *tempUnit = nullptr;
    LinkedQueue<unit *> temp;
    cout << "================ Temp Units ====================\n";
    cout << "🕒 " << tempList.getCount() << " Units in Temp [ ";
    while (!tempList.isEmpty()) {
        tempList.dequeue(tempUnit);
        temp.enqueue(tempUnit);
        if (tempUnit) {
            cout << tempUnit->getId() << " , ";
        }
    }
    cout << " ]\n";
    while (!temp.isEmpty()) {
        temp.dequeue(tempUnit);
        tempList.enqueue(tempUnit);
    }
}
void simulationManager::loadtoOutputFile(LinkedQueue<unit> killedList)
{
    OutputFile << "Td" << "     " << "ID" << "     " << "Tj" << "     " << "Df" << "     " << "Dd" << "     " << "Db" << endl;
    unit killedU;
    while (killedList.dequeue(killedU))
    {
        if (killedU.getType() == EarthSoldier || killedU.getType() == Gunnery || killedU.getType() == EarthTank)
        {

            OutputFile << killedU.getDestructionTime() << "     " << killedU.getId() << "     " << killedU.getJoinTime() << "     " << killedU.getDf() << "     " << killedU.getDd() << "     " << killedU.getDb() << endl;
            EDfcount++;
            EDdcount++;
            EDbcount++;
            sumOfEDf += killedU.getDf();
            sumOfEDd += killedU.getDd();
            sumOfEDb += killedU.getDb();
        }
        else
        {

            OutputFile << killedU.getDestructionTime() << "     " << killedU.getId() << "     " << killedU.getJoinTime() << "     " << killedU.getDf() << "     " << killedU.getDd() << "     " << killedU.getDb() << endl;
            ADfcount++;
            ADdcount++;
            ADbcount++;
            sumOfADf += killedU.getDf();
            sumOfADd += killedU.getDd();
            sumOfADb += killedU.getDb();
        }
    }

    // todo knowing result of fight
    // cout<<"win" or cout<<"drawn" or cout<<"loss"
    OutputFile << "========================= Battle result =========================";
    OutputFile << "======================================== For Earth Army ===========================" << endl;
    OutputFile << "total number of ES---> " << earthArmyPtr->getEarthSoldierCount() << endl;
    OutputFile << "total number of ET---> " << earthArmyPtr->getEarthTankCount() << endl;
    OutputFile << "total number of EG---> " << earthArmyPtr->getEarthGunneryCount() << endl;
    OutputFile << "percentage of destructed ES----> " << (double(earthArmyPtr->getEarthdestructedSoldierCount()) / earthArmyPtr->getEarthSoldierCount()) * 100 << endl;
    OutputFile << "percentage of destructed ET----> " << (double(earthArmyPtr->getEarthdestructedTankCount()) / earthArmyPtr->getEarthTankCount()) * 100 << endl;
    OutputFile << "percentage of destructed EG----> " << (double(earthArmyPtr->getEarthdestructedGunneryCount()) / earthArmyPtr->getEarthGunneryCount()) * 100 << endl;
    int totaldestructedEarthArmy = earthArmyPtr->getEarthdestructedSoldierCount() + earthArmyPtr->getEarthdestructedTankCount() + earthArmyPtr->getEarthdestructedGunneryCount();
    int totalEarthArmy = earthArmyPtr->getEarthSoldierCount() + earthArmyPtr->getEarthTankCount() + earthArmyPtr->getEarthGunneryCount();
    OutputFile << "percentage of total destructed Earth units----> " << (double(totaldestructedEarthArmy) / totalEarthArmy) * 100 << endl;
    OutputFile << "percentage of total Healed units----> " << (double(numofHealedunits) / totalEarthArmy) * 100 << endl;
    OutputFile << "Average of Df---> " << sumOfEDf / EDfcount << endl;
    OutputFile << "Average of Dd---> " << sumOfEDd / EDdcount << endl;
    OutputFile << "Average of Db---> " << sumOfEDb / EDbcount << endl;
    OutputFile << "Df/Db % ----> " << (double(sumOfEDf) / sumOfEDb) * 100 << endl;
    OutputFile << "Dd/Db % ----> " << (double(sumOfEDd) / sumOfEDb) * 100 << endl;
    

    OutputFile << "======================================== For Alien Army ===========================" << endl;
    OutputFile << "total number of AS---> " << alienArmyPtr->getAlienSoldierCount() << endl;
    OutputFile << "total number of AD---> " << alienArmyPtr->getAlienDroneCount() << endl;
    OutputFile << "total number of AM---> " << alienArmyPtr->getCurrentMonstersIndex() << endl;
    OutputFile << "percentage of destructed AS----> " << (double(alienArmyPtr->getAliendestructedSoldierCount()) / alienArmyPtr->getAlienSoldierCount()) * 100 << endl;
    OutputFile << "percentage of destructed AD----> " << (double(alienArmyPtr->getAliendestructedDroneCount()) / alienArmyPtr->getAlienDroneCount()) * 100 << endl;
    OutputFile << "percentage of destructed AM----> " << (double(alienArmyPtr->getAliendestructedMonsterCount()) / alienArmyPtr->getCurrentMonstersIndex()) * 100 << endl;
    int totaldestructedAlienArmy = alienArmyPtr->getAliendestructedSoldierCount() + alienArmyPtr->getAliendestructedDroneCount() + alienArmyPtr->getAliendestructedMonsterCount();
    int totalAlienArmy = alienArmyPtr->getAlienSoldierCount() + alienArmyPtr->getAlienDroneCount() + alienArmyPtr->getCurrentMonstersIndex();
    OutputFile << "percentage of total destructed Alien units----> " << (double(totaldestructedAlienArmy) / totalAlienArmy) * 100 << endl;
    OutputFile << "Average of Df---> " << sumOfADf / ADfcount << endl;
    OutputFile << "Average of Dd---> " << sumOfADd / ADdcount << endl;
    OutputFile << "Average of Db---> " << sumOfADb / ADbcount << endl;
    OutputFile << "Df/Db % ----> " << (double(sumOfADf) / sumOfADb) * 100 << endl;
    OutputFile << "Dd/Db % ----> " << (double(sumOfADd) / sumOfADb) * 100 << endl;


}

simulationManager::~simulationManager()
{
    if (OutputFile.is_open()) {
        OutputFile.close();
    }
}
