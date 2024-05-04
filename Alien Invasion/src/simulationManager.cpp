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

armyType (*getArmyType)(unit *armyUnit) =[](
        unit *armyUnit) -> armyType { ///@details just a utility method to get the type of the army
    if (armyUnit->getType() == EarthSoldier || armyUnit->getType() == EarthTank ||
        armyUnit->getType() == Gunnery)
        return earthArmyType;
    else
        return alienArmyType;
};

simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy();
    earthArmyPtr = new earthArmy();
    srand(time(nullptr));
    RandomGenerator = new randGen(this);
    OutputFile.open("output.txt", std::ios::in | std::ios::out);
    ofstream outputFile("output.txt", std::ofstream::out | std::ofstream::trunc);
    // Check if the file was opened successfully
    if (!OutputFile) {
        cout << "Unable to open file for writing." << endl;
        // Handle the error appropriately, e.g., by throwing an exception
        throw std::runtime_error("Failed to open output file.");
    }

    // Write data to the file in the constructor
    OutputFile << "TimeDeath     ID      Tj      Df      Dd      Db" << endl;
}

armyType simulationManager::assertWinner() const {
    if (currentTimeStep >= 40)
        if (getAlienArmyUnitsCount() == 0 && getEarthArmyUnitsCount() >= 1)
            return earthArmyType;
        else if (getEarthArmyUnitsCount() == 0 && getAlienArmyUnitsCount() >= 1)
            return alienArmyType;
        else return Nan;
    return Nan;
}

armyType simulationManager::updateSimulation(int timestep) {
    if (assertWinner() != Nan) {
        printWinner(assertWinner());
        return assertWinner();
    }


    currentTimeStep = timestep;
    manageAdding(timestep);

    ManageHealing();

    if (operationModeVal == Interactive) {
        cout << "TimeStep: " << timestep << endl;
        cout << "Earth Army Units: " << getEarthArmyUnitsCount() << endl;
        cout << "Alien Army Units: " << getAlienArmyUnitsCount() << endl;
    }

    unit *earthUnit = earthArmyPtr->getRandomUnit();
    unit *alienUnit = alienArmyPtr->getRandomUnit();

    handleUnit(earthUnit);
    handleUnit(alienUnit);
    earthArmyPtr->print();
    alienArmyPtr->print();
    printKilledList();

    return Nan;

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
        if (newUnit->getType() == Healer) {
            HealList.push(newUnit);
            return;
        }
    }
}


///@param AttackingUnit: The unit attacking.
///@param DamagedUnit: The unit being attacked.
void simulationManager::showStats(unit *AttackingUnit, unit *DamagedUnit) const {
    if (operationModeVal == Interactive)
        if (AttackingUnit && DamagedUnit)
            cout << "ID:" << AttackingUnit->getId() << ":" << [&AttackingUnit]() -> string {
                switch (AttackingUnit->getType()) {
                    case EarthSoldier:
                        return "Earth Soldier";
                    case EarthTank:
                        return "Earth Tank";
                    case Gunnery:
                        return "Gunnery";
                    case alienSoldier:
                        return "Alien Soldier";
                    case DronePair:
                        return "Drone";
                    case MonsterType:
                        return "Monster";
                }
            }()
                 << " has attacked unit of ID:"
                 << DamagedUnit->getId()
                 << " " << [&DamagedUnit]() -> string {
                switch (DamagedUnit->getType()) {
                    case EarthSoldier:
                        return "Earth Soldier";
                    case EarthTank:
                        return "Earth Tank";
                    case Gunnery:
                        return "Gunnery";
                    case alienSoldier:
                        return "Alien Soldier";
                    case DronePair:
                        return "Drone";
                    case MonsterType:
                        return "Monster";
                }
            }() << endl;
}

void simulationManager::manageAdding(int timestep) {
    if (RandomGenerator->creatEarthUnits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(earthArmyType, timestep));
        }
    }
    if (RandomGenerator->creatAlienUnits()) {
        for (int i = 0; i < RandomGenerator->getnumofunits(); i++) {
            addNewUnit(RandomGenerator->generatUnit(alienArmyType, timestep));
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
    cout << "================ ☠️Killed Units☠️ ====================\n";
    cout << "💀 " << killedList.getCount() << " Units killed [ ";
    while (!killedList.isEmpty()) {
        killedList.dequeue(killedUnit);
        temp.enqueue(killedUnit);
        if (killedUnit) {
            cout << killedUnit->getId() << (killedList.isEmpty() ? "" : " , ");
        }
    }
    cout << " ]\n";
    while (!temp.isEmpty()) {
        temp.dequeue(killedUnit);
        killedList.enqueue(killedUnit);
    }

}


void simulationManager::loadtoOutputFile() {

    int sumOfEDf{0}, EDfcount{0}, sumOfEDd{0}, EDdcount{0}, sumOfEDb{0}, EDbcount{0}, sumOfADf{0}, ADfcount{
            0}, sumOfADd{0}, ADdcount{0}, sumOfADb{0}, ADbcount{0}, numofHealedunits{0};
    unit *killedU;
    while (killedList.dequeue(killedU)) {
        if (killedU->getType() == EarthSoldier || killedU->getType() == Gunnery ||
            killedU->getType() == EarthTank) {
            OutputFile << killedU->getDestructionTime() << "     " << killedU->getId() << "     "
                       << killedU->getJoinTime() << "     " << killedU->getDf() << "     " << killedU->getDd()
                       << "     " << killedU->getDb() << endl;
            EDfcount++;
            EDdcount++;
            EDbcount++;
            sumOfEDf += killedU->getDf();
            sumOfEDd += killedU->getDd();
            sumOfEDb += killedU->getDb();
        } else {

            OutputFile << killedU->getDestructionTime() << "     " << killedU->getId() << "     "
                       << killedU->getJoinTime() << "     " << killedU->getDf() << "     " << killedU->getDd()
                       << "     " << killedU->getDb() << endl;
            ADfcount++;
            ADdcount++;
            ADbcount++;
            sumOfADf += killedU->getDf();
            sumOfADd += killedU->getDd();
            sumOfADb += killedU->getDb();
        }
    }

    // cout<<"win" or cout<<"drawn" or cout<<"loss"
    OutputFile << "========================= Battle result =========================\n";
    OutputFile << "======================================== For Earth Army ===========================" << endl;
    OutputFile << "total number of ES---> " << earthArmyPtr->getEarthSoldierCount() << endl;
    OutputFile << "total number of ET---> " << earthArmyPtr->getEarthTankCount() << endl;
    OutputFile << "total number of EG---> " << earthArmyPtr->getEarthGunneryCount() << endl;
    if (earthArmyPtr->getEarthSoldierCount() != 0)
        OutputFile << "percentage of destructed ES----> "
                <<
                (double(earthArmyPtr->getEarthdestructedSoldierCount()) / earthArmyPtr->getEarthSoldierCount()) *
                   100 << endl;
    if (earthArmyPtr->getEarthTankCount() != 0)
        OutputFile << "percentage of destructed ET----> "
                << (double(earthArmyPtr->getEarthdestructedTankCount()) / earthArmyPtr->getEarthTankCount()) *
                   100
                << endl;
    if (earthArmyPtr->getEarthGunneryCount() != 0)
        OutputFile << "percentage of destructed EG----> "
                <<
                (double(earthArmyPtr->getEarthdestructedGunneryCount()) / earthArmyPtr->getEarthGunneryCount()) *
                   100 << endl;
    int totaldestructedEarthArmy =
            earthArmyPtr->getEarthdestructedSoldierCount() + earthArmyPtr->getEarthdestructedTankCount() +
            earthArmyPtr->getEarthdestructedGunneryCount();
    int totalEarthArmy = earthArmyPtr->getEarthSoldierCount() + earthArmyPtr->getEarthTankCount() +
                         earthArmyPtr->getEarthGunneryCount();
    if (totalEarthArmy != 0)
        OutputFile << "percentage of total destructed Earth units----> "
                << (double(totaldestructedEarthArmy) / totalEarthArmy) * 100 << endl;
    if (totalEarthArmy != 0)
        OutputFile << "percentage of total Healed units----> " << (double(numofHealedunits) / totalEarthArmy) * 100
                << endl;
    if (EDfcount != 0)
        OutputFile << "Average of Df---> " << sumOfEDf / EDfcount << endl;
    if (EDdcount != 0)
        OutputFile << "Average of Dd---> " << sumOfEDd / EDdcount << endl;
    if (EDbcount != 0)
        OutputFile << "Average of Db---> " << sumOfEDb / EDbcount << endl;
    if (sumOfEDb != 0)
        OutputFile << "Df/Db % ----> " << (double(sumOfEDf) / sumOfEDb) * 100 << endl;
    if (sumOfEDb != 0)
        OutputFile << "Dd/Db % ----> " << (double(sumOfEDd) / sumOfEDb) * 100 << endl;


    OutputFile << "======================================== For Alien Army ===========================" << endl;
    OutputFile << "total number of AS---> " << alienArmyPtr->getAlienSoldierCount() << endl;
    OutputFile << "total number of AD---> " << alienArmyPtr->getAlienDroneCount() << endl;
    OutputFile << "total number of AM---> " << alienArmyPtr->getCurrentMonstersIndex() + 1 << endl;
    if (alienArmyPtr->getAlienSoldierCount() != 0)
        OutputFile << "percentage of destructed AS----> "
                <<
                (double(alienArmyPtr->getAliendestructedSoldierCount()) / alienArmyPtr->getAlienSoldierCount()) *
                   100 << endl;
    if (alienArmyPtr->getAlienDroneCount() != 0)
        OutputFile << "percentage of destructed AD----> "
                << (double(alienArmyPtr->getAliendestructedDroneCount()) / alienArmyPtr->getAlienDroneCount()) *
                   100
                << endl;
    if (alienArmyPtr->getCurrentMonstersIndex() != 0)
        OutputFile << "percentage of destructed AM----> " <<
                                                          (double(alienArmyPtr->getAliendestructedMonsterCount()) /
                                                           alienArmyPtr->getCurrentMonstersIndex()) *
                                                          100 << endl;
    int totaldestructedAlienArmy =
            alienArmyPtr->getAliendestructedSoldierCount() + alienArmyPtr->getAliendestructedDroneCount() +
            alienArmyPtr->getAliendestructedMonsterCount();
    int totalAlienArmy = alienArmyPtr->getAlienSoldierCount() + alienArmyPtr->getAlienDroneCount() +
                         alienArmyPtr->getCurrentMonstersIndex();
    if (totalAlienArmy != 0)
        OutputFile << "percentage of total destructed Alien units----> "
                << (double(totaldestructedAlienArmy) / totalAlienArmy) * 100 << endl;
    if (ADfcount != 0)
        OutputFile << "Average of Df---> " << sumOfADf / ADfcount << endl;
    if (ADdcount != 0)
        OutputFile << "Average of Dd---> " << sumOfADd / ADdcount << endl;
    if (ADbcount != 0)
        OutputFile << "Average of Db---> " << sumOfADb / ADbcount << endl;
    if (sumOfADb != 0)
        OutputFile << "Df/Db % ----> " << (double(sumOfADf) / sumOfADb) * 100 << endl;
    if (sumOfADb != 0)
        OutputFile << "Dd/Db % ----> " << (double(sumOfADd) / sumOfADb) * 100 << endl;


}

/// ! When Insert in PriQueue observe that the decleartion was changed for UML
void simulationManager::ManageHealing() {

    unit *Healer;
    if (!HealList.pop(Healer))
        return;
    int Cap = Healer->getAttackCapacity();


    LinkedQueue<unit *> T;
    LinkedQueue<unit *> tank;

    priQueue<unit *> Soldiers;

    while (!UnitMaintenanceList.isEmpty()) {
        unit *Inj;
        UnitMaintenanceList.dequeue(Inj);
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
            killedList.enqueue(InjSol);

        else {
            Healer->damageEnemy(InjSol);

            if (InjSol->getHealth() > (0.2 * InjSol->GetOriginalHealth())) {
                addNewUnit(InjSol);
            } else {
                UnitMaintenanceList.enqueue(InjSol);
            }
            InjSol->UpdateStillHealing();
            Cap--;
        }
    }


    while (0 < Cap && !tank.isEmpty()) {
        unit *InjTank;
        tank.dequeue(InjTank);


        if (InjTank->GetStillHealing() == 10)
            killedList.enqueue(InjTank);

        else {
            Healer->damageEnemy(InjTank);

            if (InjTank->getHealth() > (0.2 * InjTank->GetOriginalHealth())) {
                addNewUnit(InjTank);
            } else {
                UnitMaintenanceList.enqueue(InjTank);
            }
            InjTank->UpdateStillHealing();
            Cap--;
        }
    }


    while (!Soldiers.isEmpty()) {
        unit *S;
        int p;
        Soldiers.dequeue(S, p);
        UnitMaintenanceList.enqueue(S);
    }
    while (!tank.isEmpty()) {
        unit *t;
        tank.dequeue(t);
        UnitMaintenanceList.enqueue(t);
    }
    while (!T.isEmpty()) {
        unit *t;
        T.dequeue(t);
        UnitMaintenanceList.enqueue(t);
    }

    unit *Temp{nullptr};
    int UMLlength = UnitMaintenanceList.getCount();
    for (int i = 0; i < UMLlength; ++i) {
        returnUnitToArmy(Temp);
    }

    delete Healer;
}

simulationManager::~simulationManager() {
    if (OutputFile.is_open()) {
        OutputFile.close();
    }
}

void simulationManager::handleUnit(unit *attackingUnit) {
    LinkedQueue<unit *> tempList;

    bool enqueuedOnce = false;
    ///@details makes the two units fight each other, but if one of them is null just return them to their armies
    if (!attackingUnit) { return; }
    else {
        unit *secondAttackingDrone{nullptr};
        unit *defendingUnit{nullptr};

        ///@note if the attacking unit is a drone , pick another drone to attack. if no other drone exists then return the attacking drone to its army;
        if (attackingUnit->getType() == DronePair) {
            secondAttackingDrone = alienArmyPtr->getDronePair();
            if (!secondAttackingDrone) {
                alienArmyPtr->addUnit(attackingUnit);
                return;
            }
        }

        for (int i = 0; i < min(attackingUnit->getAttackCapacity(),
                                secondAttackingDrone ? secondAttackingDrone->getAttackCapacity()
                                                     : attackingUnit->getAttackCapacity()); ++i) {
            ///@note if the attacking unit is from the alien army, it will attack an earth unit else pick an alien unit
            if ((*getArmyType)(attackingUnit) == alienArmyType)
                defendingUnit = earthArmyPtr->getRandomUnit();
            else
                defendingUnit = alienArmyPtr->getRandomUnit();

            if (defendingUnit) {

                if (attackingUnit->damageEnemy(defendingUnit)) {
                    if (operationModeVal == Interactive) {
                        showStats(attackingUnit, defendingUnit);
                        if (secondAttackingDrone) {
                            secondAttackingDrone->damageEnemy(defendingUnit);
                            showStats(secondAttackingDrone, defendingUnit);
                        }
                    }

                    if (!enqueuedOnce) {
                        enqueuedOnce = true;
                        tempList.enqueue(attackingUnit);
                        if (secondAttackingDrone)
                            tempList.enqueue(secondAttackingDrone);
                    }

                    tempList.enqueue(defendingUnit);
                }

            }
        }

    }

    if (!enqueuedOnce) {
        if ((*getArmyType)(attackingUnit) == alienArmyType)
            alienArmyPtr->addUnit(attackingUnit);
        else earthArmyPtr->addUnit(attackingUnit);
        return;
    }

    printinfoCurrentfight(tempList);
    unit *temp{nullptr};
    while (tempList.dequeue(temp))
        returnUnitToArmy(temp);

}


void simulationManager::returnUnitToArmy(unit *unitPtr) {
    if (unitPtr) {
        if (unitPtr->getHealth() <= 0) {
            killedList.enqueue(unitPtr);
            unitPtr->setDestructionTime(getCurrentTimeStep());
            return;
        }

        if (unitPtr->getHealth() <= 0.2 * unitPtr->GetOriginalHealth()) {
            unitPtr->UpdateStillHealing();
            UnitMaintenanceList.enqueue(unitPtr);
            return;
        }

        if ((*getArmyType)(unitPtr) == alienArmyType)
            alienArmyPtr->addUnit(unitPtr);
        else earthArmyPtr->addUnit(unitPtr);
    }
}

int simulationManager::getCurrentTimeStep() const {
    return currentTimeStep;
}

void simulationManager::printinfoCurrentfight(LinkedQueue<unit *> &tempList) {
    cout << "================= ⚔️units fighting at current step⚔️ =======================\n";
    LinkedQueue<unit *> tempList2;
    unit *unitShot, *attackedunit;
    while (tempList.dequeue(unitShot)) {
        tempList2.enqueue(unitShot);
        cout << unitShot->typetostring(unitShot->getType()) << "  " << unitShot->getId() << " [ ";
        while (tempList.dequeue(attackedunit)) {
            tempList2.enqueue(attackedunit);
            cout << attackedunit->getId() << (tempList.isEmpty() ? "" : "  , ");
        }
        cout << " ]" << endl;
    }
    cout << endl;
    while (tempList2.dequeue(unitShot))
        tempList.enqueue(unitShot);
}

void simulationManager::printWinner(armyType type) {
    system("cls");
    //create an ascii art for the winner
    if (type == alienArmyType) {
        cout
                << "Alien Army Wins\n";
        return;

    } else if (type == earthArmyType) {
        cout
                << "Earth Army Wins\n";

    }
}