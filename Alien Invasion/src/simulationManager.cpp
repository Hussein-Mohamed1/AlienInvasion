//
// Created by youss on 3/30/2024.
//
#pragma once

#include "simulationManager.h"
#include "windows.h"
#include "iostream"

simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy();
    earthArmyPtr = new earthArmy();
    srand(time(nullptr));
    RandomGenerator = new randGen;
}

void simulationManager::updateSimulation(int timestep) {
    manageAdding(timestep);
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
            cout << "Killed Tank is ---> ";
            tank->print();
            KilledList.enqueue(tank);
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
                tempList.enqueue(soldier);
                soldier->print();
                cout << "\n👽 Alien Soldiers Count after removing soldier is "
                     << alienArmyPtr->getAlienSoldierCount();
                soldier->setHealth(soldier->getHealth() - soldier->getHealth() / 2);

                printTempList();
                tempList.dequeue(soldier);

                alienArmyPtr->addUnit(soldier);
                cout << "\n➕ And re-queuing it. New count is: " << alienArmyPtr->getAlienSoldierCount() << endl << endl;
            } else {
                cout << "⚠️ No soldiers.\n";
                break;
            }
        }
    } else if (x > 40 & x <= 50) {
        unit *temp[5]{nullptr};
        for (int i = 0; i < 5; i++) {
            cout << "\n👽 Picking an 👹 Alien Monster.\n";
            unit *monster = alienArmyPtr->getUnit(MonsterType);
            if (monster) {
                monster->print();
                cout << "\n👹 Alien Monsters Count after removing monster is "
                     << alienArmyPtr->getCurrentMonstersIndex() + 1 << endl;
                temp[i] = monster;
            } else {
                cout << "⚠️ No monsters.\n";
                break;
            }
        }
        for (int i = 0; i < 5; ++i) {
            if (temp[i] == nullptr)
                break;
            alienArmyPtr->addUnit(temp[i]);
            cout << "➕ Now re-queuing the monster chosen no. " << i + 1 << "\n👹 No. Monsters is: "
                 << alienArmyPtr->getCurrentMonstersIndex() + 1 << endl;
        }

    } else if (x > 50 & x <= 60) {
        unit *drone = nullptr;
        if (alienArmyPtr->getAlienDroneCount() < 2)
            cout << "⚠️ No Enough drones.\n";
        else {
            for (int i = 0; i < 6; i++) {
                cout << "👽 Picking an 🛸 Alien Drone.\n";
                drone = alienArmyPtr->getUnit(DronePair);
                if (drone) {
                    cout << "killed Drone is ---> ";
                    drone->print();
                    KilledList.enqueue(drone);
                    cout << "\n👽 Alien Drones Count after removing drone is " << alienArmyPtr->getAlienDroneCount()
                         << endl;
                    drone = alienArmyPtr->getUnit(DronePair);
                    cout << "killed Drone is ---> ";
                    drone->print();
                    KilledList.enqueue(drone);
                    cout << "\n👽 Alien Drones Count after removing drone is " << alienArmyPtr->getAlienDroneCount()
                         << endl;
                } else {
                    cout << "⚠️ No drones.\n";
                    break;
                }
            }

        }
    }
    printKilledList();
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

