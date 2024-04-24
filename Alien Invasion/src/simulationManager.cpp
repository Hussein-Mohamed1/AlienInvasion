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
    manageAdding(timestep);

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
            cout << AttackingUnit->getId() << " " << AttackingUnit->getType() << " has attacked"
                 << DamagedUnit->getId()
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

void simulationManager::loadtoOutputFile(LinkedQueue<unit> killedList) {
    OutputFile << "Td" << "     " << "ID" << "     " << "Tj" << "     " << "Df" << "     " << "Dd" << "     "
               << "Db" << endl;
    unit killedU;
    while (killedList.dequeue(killedU)) {
        if (killedU.getType() == EarthSoldier || killedU.getType() == Gunnery || killedU.getType() == EarthTank) {
            void
            simulationManager::ManageHealing()    /// !!!!!!!!!! When Insert in PriQueue observe that the decleartion was changed for UML
            {

                HealUnit *Healer;
                if (!HealList.pop(Healer))
                    return;
                int Cap = Healer->getAttackCapacity();


                LinkedQueue<unit *> T;
                LinkedQueue<unit *> tank;

                priQueue<unit *> Soldiers;

                while (!UnitMaintenceList.isEmpty()) {
                    unit *Inj;
                    UnitMaintenceList.dequeue(Inj);
                    if (Inj->getType() == EarthSoldier) {
                        Soldiers.enqueue(Inj, Inj->getHealth(), 1);
                    } else if (Inj->getType() == EarthTank) {
                        tank.enqueue(Inj);
                    } else
                        T.enqueue(Inj);

                }

                while (0 < Cap && !Soldiers.isEmpty()) {
                    unit *InjSol;
                    int p;
                    Soldiers.dequeue(InjSol, p);

                    if (InjSol->GetStillHealing() == 10)
                        KilledList.enqueue(InjSol);

                    else {
                        Healer->Heal(InjSol);

                        if (InjSol->getHealth() > (0.2 * InjSol->GetOriginalHealth())) {
                            addNewUnit(InjSol);
                        } else {
                            tempList.enqueue(InjSol);
                        }
                        InjSol->UpdateStillHealing();
                        Cap--;
                    }
                }


                while (0 < Cap && !tank.isEmpty()) {
                    unit *InjTank;
                    tank.dequeue(InjTank);


                    if (InjTank->GetStillHealing() == 10)
                        KilledList.enqueue(InjTank);

                    else {
                        Healer->Heal(InjTank);

                        if (InjTank->getHealth() > (0.2 * InjTank->GetOriginalHealth())) {
                            addNewUnit(InjTank);
                        } else {
                            tempList.enqueue(InjTank);
                        }
                        InjTank->UpdateStillHealing();
                        Cap--;
                    }
                }


                while (!Soldiers.isEmpty()) {
                    unit *S;
                    int p;
                    Soldiers.dequeue(S, p);
                    UnitMaintenceList.enqueue(S);
                }
                while (!tank.isEmpty()) {
                    unit *t;
                    tank.dequeue(t);
                    UnitMaintenceList.enqueue(t);
                }
                while (!T.isEmpty()) {
                    unit *t;
                    T.dequeue(t);
                    UnitMaintenceList.enqueue(t);
                }


                while (!tempList.isEmpty()) {
                    unit *T;
                    tempList.dequeue(T);
                    UnitMaintenceList.enqueue(T);
                }

                delete Healer;
            }

            OutputFile << killedU.getDestructionTime() << "     " << killedU.getId() << "     "
                       << killedU.getJoinTime() << "     " << killedU.getDf() << "     " << killedU.getDd()
                       << "     " << killedU.getDb() << endl;
            EDfcount++;
            EDdcount++;
            EDbcount++;
            sumOfEDf += killedU.getDf();
            sumOfEDd += killedU.getDd();
            sumOfEDb += killedU.getDb();
        } else {

            OutputFile << killedU.getDestructionTime() << "     " << killedU.getId() << "     "
                       << killedU.getJoinTime() << "     " << killedU.getDf() << "     " << killedU.getDd()
                       << "     " << killedU.getDb() << endl;
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
    OutputFile << "percentage of destructed ES----> "
               << (double(earthArmyPtr->getEarthdestructedSoldierCount()) / earthArmyPtr->getEarthSoldierCount()) *
                  100 << endl;
    OutputFile << "percentage of destructed ET----> "
               << (double(earthArmyPtr->getEarthdestructedTankCount()) / earthArmyPtr->getEarthTankCount()) * 100
               << endl;
    OutputFile << "percentage of destructed EG----> "
               << (double(earthArmyPtr->getEarthdestructedGunneryCount()) / earthArmyPtr->getEarthGunneryCount()) *
                  100 << endl;
    int totaldestructedEarthArmy =
            earthArmyPtr->getEarthdestructedSoldierCount() + earthArmyPtr->getEarthdestructedTankCount() +
            earthArmyPtr->getEarthdestructedGunneryCount();
    int totalEarthArmy = earthArmyPtr->getEarthSoldierCount() + earthArmyPtr->getEarthTankCount() +
                         earthArmyPtr->getEarthGunneryCount();
    OutputFile << "percentage of total destructed Earth units----> "
               << (double(totaldestructedEarthArmy) / totalEarthArmy) * 100 << endl;
    OutputFile << "percentage of total Healed units----> " << (double(numofHealedunits) / totalEarthArmy) * 100
               << endl;
    OutputFile << "Average of Df---> " << sumOfEDf / EDfcount << endl;
    OutputFile << "Average of Dd---> " << sumOfEDd / EDdcount << endl;
    OutputFile << "Average of Db---> " << sumOfEDb / EDbcount << endl;
    OutputFile << "Df/Db % ----> " << (double(sumOfEDf) / sumOfEDb) * 100 << endl;
    OutputFile << "Dd/Db % ----> " << (double(sumOfEDd) / sumOfEDb) * 100 << endl;


    OutputFile << "======================================== For Alien Army ===========================" << endl;
    OutputFile << "total number of AS---> " << alienArmyPtr->getAlienSoldierCount() << endl;
    OutputFile << "total number of AD---> " << alienArmyPtr->getAlienDroneCount() << endl;
    OutputFile << "total number of AM---> " << alienArmyPtr->getCurrentMonstersIndex() << endl;
    OutputFile << "percentage of destructed AS----> "
               << (double(alienArmyPtr->getAliendestructedSoldierCount()) / alienArmyPtr->getAlienSoldierCount()) *
                  100 << endl;
    OutputFile << "percentage of destructed AD----> "
               << (double(alienArmyPtr->getAliendestructedDroneCount()) / alienArmyPtr->getAlienDroneCount()) * 100
               << endl;
    OutputFile << "percentage of destructed AM----> " <<
               (double(alienArmyPtr->getAliendestructedMonsterCount()) / alienArmyPtr->getCurrentMonstersIndex()) *
               100 << endl;
    int totaldestructedAlienArmy =
            alienArmyPtr->getAliendestructedSoldierCount() + alienArmyPtr->getAliendestructedDroneCount() +
            alienArmyPtr->getAliendestructedMonsterCount();
    int totalAlienArmy = alienArmyPtr->getAlienSoldierCount() + alienArmyPtr->getAlienDroneCount() +
                         alienArmyPtr->getCurrentMonstersIndex();
    OutputFile << "percentage of total destructed Alien units----> "
               << (double(totaldestructedAlienArmy) / totalAlienArmy) * 100 << endl;
    OutputFile << "Average of Df---> " << sumOfADf / ADfcount << endl;
    OutputFile << "Average of Dd---> " << sumOfADd / ADdcount << endl;
    OutputFile << "Average of Db---> " << sumOfADb / ADbcount << endl;
    OutputFile << "Df/Db % ----> " << (double(sumOfADf) / sumOfADb) * 100 << endl;
    OutputFile << "Dd/Db % ----> " << (double(sumOfADd) / sumOfADb) * 100 << endl;


}

simulationManager::~simulationManager() {
    if (OutputFile.is_open()) {
        OutputFile.close();
    }
}
