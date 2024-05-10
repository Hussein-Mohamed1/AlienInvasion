//
// Created by youss on 3/30/2024.
//
#pragma once

#include <string>
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

//    ManageHealing();

    if (operationModeVal == Interactive) {
        cout << "TimeStep: " << timestep << endl;
        cout << "Earth Army Units: " << getEarthArmyUnitsCount() << endl;
        cout << "Alien Army Units: " << getAlienArmyUnitsCount() << endl;
    }

    unit *earthUnit = earthArmyPtr->getRandomUnit();
    unit *alienUnit = alienArmyPtr->getRandomUnit();

    handleUnit(earthUnit);
    handleUnit(alienUnit);

    if (operationModeVal == Interactive) {
        earthArmyPtr->print();
        alienArmyPtr->print();
        printKilledList();
    }
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
                        return "Earth Soldier ";
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
                    case Healer:
                        return "Healer";
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
    return alienArmyPtr->getCurrentAlienSoldierCount() + alienArmyPtr->getCurrentAlienDroneCount() +
           alienArmyPtr->getCurrentMonstersIndex() + 1;
}


int simulationManager::getAlienSoldiersCount() const {
    return alienArmyPtr->getCurrentAlienSoldierCount();
}

int simulationManager::getEarthSoldiersCount() const {
    return earthArmyPtr->getEarthSoldierCount();
}

int simulationManager::getEarthArmyUnitsCount() const {
    return earthArmyPtr->getEarthGunneryCount() + earthArmyPtr->getEarthSoldierCount() +
           earthArmyPtr->getEarthTankCount();
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
        addToKilledList(killedUnit);
    }

}

///@todo move this to randgen
void simulationManager::loadtoOutputFile() {

    int sumOfEDf{0}, EDfcount{0}, sumOfEDd{0}, EDdcount{0}, sumOfEDb{0}, EDbcount{0}, sumOfADf{0}, ADfcount{
            0}, sumOfADd{0}, ADdcount{0}, sumOfADb{0}, ADbcount{
            0}, numofHealedunits = UnitMaintenanceList.getCount(), alienDestructedSoldierCount{0},
            alienDestructedMonsterCount{0},
            alienDestructedDroneCount{0},
            earthdestructedGunneryCount{0},
            earthdestructedSoldierCount{0},
            earthdestructedTankCount{0};
    unit *killedU;
    while (killedList.dequeue(killedU)) {
        if (killedU->getType() == EarthSoldier || killedU->getType() == Gunnery ||
            killedU->getType() == EarthTank) {
            switch (killedU->getType()) {
                case EarthSoldier:
                    earthdestructedSoldierCount++;
                    break;
                case Gunnery:
                    earthdestructedGunneryCount++;
                    break;
                case EarthTank:
                    earthdestructedTankCount++;
                    break;
                default:
                    break;
            }
            OutputFile << killedU->getDestructionTime() << "     " << killedU->getId() << "     "
                       << killedU->getJoinTime() << "     " << killedU->getDf() << "     " << killedU->getDd()
                    << "     " << killedU->getDb() << "     " << killedU->typeToString() << endl;
            EDfcount++;
            EDdcount++;
            EDbcount++;
            sumOfEDf += killedU->getDf();
            sumOfEDd += killedU->getDd();
            sumOfEDb += killedU->getDb();
        } else {
            switch (killedU->getType()) {
                case alienSoldier:
                    alienDestructedSoldierCount++;
                    break;
                case DronePair:
                    alienDestructedDroneCount++;
                    break;
                case MonsterType:
                    alienDestructedMonsterCount++;
                    break;
                default:
                    break;
            }
            OutputFile << killedU->getDestructionTime() << "     " << killedU->getId() << "     "
                    << killedU->getJoinTime() << "     " << killedU->getDf() << "     " << killedU->getDd()
                    << "     " << killedU->getDb() << "     " << killedU->typeToString() << endl;
            ADfcount++;
            ADdcount++;
            ADbcount++;
            sumOfADf += killedU->getDf();
            sumOfADd += killedU->getDd();
            sumOfADb += killedU->getDb();

        }
    }

    switch (assertWinner()) {
        case earthArmyType :
            OutputFile << "========================= Earth Win =========================\n";
            break;
        case alienArmyType:
            OutputFile << "========================= Alien Win =========================\n";
            break;
        case Nan:
            OutputFile << "========================= Draw =========================\n";
            break;
        default:
            break;
    }
    OutputFile << "======================================== For Earth Army ===========================" << endl;
    OutputFile << "total number of ES---> " << earthArmyPtr->getEarthSoldierCount() + earthdestructedSoldierCount
               << endl;
    OutputFile << "total number of ET---> " << earthArmyPtr->getEarthTankCount() + earthdestructedTankCount << endl;
    OutputFile << "total number of EG---> " << earthArmyPtr->getEarthGunneryCount() + earthdestructedGunneryCount
               << endl;
    if ((earthdestructedSoldierCount + earthArmyPtr->getEarthSoldierCount()) != 0)
        OutputFile << "percentage of destructed ES----> "
                << (double(earthdestructedSoldierCount) /
                    (earthdestructedSoldierCount + earthArmyPtr->getEarthSoldierCount())) *
                   100 << endl;
    if ((earthdestructedTankCount + earthArmyPtr->getEarthTankCount()) != 0)
        OutputFile << "percentage of destructed ET----> "
                <<
                (double(earthdestructedTankCount) / (earthdestructedTankCount + earthArmyPtr->getEarthTankCount())) *
                100
                << endl;
    if ((earthdestructedGunneryCount + earthArmyPtr->getEarthGunneryCount()) != 0)
        OutputFile << "percentage of destructed EG----> "
                << (double(earthdestructedGunneryCount) /
                    (earthdestructedGunneryCount + earthArmyPtr->getEarthGunneryCount())) *
                   100 << endl;
    int totaldestructedEarthArmy = earthdestructedGunneryCount + earthdestructedSoldierCount + earthdestructedTankCount;
    int totalEarthArmy = earthArmyPtr->getEarthSoldierCount() + earthArmyPtr->getEarthTankCount() +
            earthArmyPtr->getEarthGunneryCount() + totaldestructedEarthArmy;
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
    OutputFile << "total number of AS---> " << alienArmyPtr->getCurrentAlienSoldierCount() + alienDestructedSoldierCount
               << endl;
    OutputFile << "total number of AD---> " << alienArmyPtr->getCurrentAlienDroneCount() + alienDestructedDroneCount
               << endl;
    OutputFile << "total number of AM---> " << alienArmyPtr->getCurrentMonstersIndex() + alienDestructedMonsterCount + 1
               << endl;
    if ((alienArmyPtr->getCurrentAlienSoldierCount() + alienDestructedSoldierCount) != 0)
        OutputFile << "percentage of destructed AS----> "
                << (double(alienDestructedSoldierCount) /
                    (alienArmyPtr->getCurrentAlienSoldierCount() + alienDestructedSoldierCount)) *
                   100 << endl;
    if ((alienArmyPtr->getCurrentAlienDroneCount() + alienDestructedDroneCount) != 0)
        OutputFile << "percentage of destructed AD----> "
                << (double(alienDestructedDroneCount) /
                    (alienArmyPtr->getCurrentAlienDroneCount() + alienDestructedDroneCount)) * 100
                << endl;
    if ((alienArmyPtr->getCurrentMonstersIndex() +
            alienDestructedMonsterCount + 1) != 0)
        OutputFile << "percentage of destructed AM----> " <<
                                                          (double(alienDestructedMonsterCount) /
                                                           (alienArmyPtr->getCurrentMonstersIndex() +
                                                            alienDestructedMonsterCount + 1)) *
                                                          100 << endl;
    int totaldestructedAlienArmy =
            alienDestructedDroneCount + alienDestructedMonsterCount + alienDestructedSoldierCount;
    int totalAlienArmy = alienArmyPtr->getCurrentAlienSoldierCount() + alienArmyPtr->getCurrentAlienDroneCount() +
            alienArmyPtr->getCurrentMonstersIndex() + totaldestructedAlienArmy;
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
            addToKilledList(InjSol);

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
            addToKilledList(InjTank);

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


    if (!attackingUnit) { return; }
    else {
        unit *secondAttackingDrone{nullptr};
        unit *defendingUnit1{nullptr};
        unit *defendingUnit2{nullptr};

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
                                                     : attackingUnit->getAttackCapacity()) / 2; ++i) {
            ///@note if the attacking unit is from the alien army, it will attack an earth unit else pick an alien unit
            if ((*getArmyType)(attackingUnit) == alienArmyType) {
                defendingUnit1 = earthArmyPtr->getAnEnemyFor(attackingUnit->getType());
                defendingUnit2 = earthArmyPtr->getAnEnemyFor(attackingUnit->getType(), 1);
            } else {
                defendingUnit1 = alienArmyPtr->getAnEnemyFor(attackingUnit->getType());
                defendingUnit2 = alienArmyPtr->getAnEnemyFor(attackingUnit->getType(), 1);
            }

            if (defendingUnit1) {
                ///@details makes the attacker attack defendingUnit1 and if there is a drone pair then make both attack
                attackingUnit->damageEnemy(defendingUnit1);
                if (secondAttackingDrone)
                    secondAttackingDrone->damageEnemy(defendingUnit1);


                if (operationModeVal == Interactive) {
                    showStats(attackingUnit, defendingUnit1);
                    if (secondAttackingDrone)
                        showStats(secondAttackingDrone, defendingUnit1);
                }

                ///@details used to handle the adding of the attacking unit to templist only once
                if (!enqueuedOnce) {
                    enqueuedOnce = true;
                    tempList.enqueue(attackingUnit);
                    if (secondAttackingDrone)
                        tempList.enqueue(secondAttackingDrone);
                }

                tempList.enqueue(defendingUnit1);
            }

            if (defendingUnit2) {
                attackingUnit->damageEnemy(defendingUnit2);
                if (secondAttackingDrone)
                    secondAttackingDrone->damageEnemy(defendingUnit2);


                if (operationModeVal == Interactive) {
                    showStats(attackingUnit, defendingUnit2);
                    if (secondAttackingDrone)
                        showStats(secondAttackingDrone, defendingUnit2);
                }


                ///@details used to handle the adding of the attacking unit to templist only once
                if (!enqueuedOnce) {
                    enqueuedOnce = true;
                    tempList.enqueue(attackingUnit);
                    if (secondAttackingDrone)
                        tempList.enqueue(secondAttackingDrone);
                }

                tempList.enqueue(defendingUnit2);
            }
        }
    }

    if (!enqueuedOnce) {
        returnUnitToArmy(attackingUnit);
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
            addToKilledList(unitPtr);
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
    unit *unitShot{nullptr}, *secondDrone{nullptr}, *attackedUnit{nullptr};

    while (tempList.dequeue(unitShot)) {
        if (unitShot->getType() == DronePair) {
            tempList.dequeue(secondDrone);
            tempList2.enqueue(secondDrone);
        }
        tempList2.enqueue(unitShot);
        cout << unitShot->typeToString() << "  "
             << unitShot->getId() << (secondDrone ? ", " + to_string(secondDrone->getId()) : "")
             << " [ ";
        while (tempList.dequeue(attackedUnit)) {
            tempList2.enqueue(attackedUnit);
            cout << attackedUnit->getId() << (tempList.isEmpty() ? "" : "  , ");
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
        auto clearScreen = []() {
            std::cout << "\033[2J\033[1;1H";
        };

        // Function to draw the Alien Spaceship
        auto drawAlienSpaceship = []() {
            std::cout << "           /\\     /\\             \n";
            std::cout << "      ____/__\\___/__\\____        \n";
            std::cout << "     /         \\ /         \\      \n";
            std::cout << "     | _________V_________ |      \n";
            std::cout << "     |* * * * * | * * * * *|      \n";
            std::cout << "     \\* * * * *|* * * * * */      \n";
            std::cout << "      \\_________|_________/       \n";
            std::cout << "     /          |          \\      \n";
            std::cout << "     \\         / \\         /      \n";
            std::cout << "      \\_______/   \\_______/       \n";
        };

        // Function to draw the Alien Planet
        auto drawAlienPlanet = []() {
            std::cout << "                             \n";
            std::cout << "           _   _   _          \n";
            std::cout << "         / / / / / /\\         \n";
            std::cout << "        / / / / / /  \\        \n";
            std::cout << "       / / / / / /    \\       \n";
            std::cout << "      / / / / / /      \\      \n";
            std::cout << "     / / / / / /        \\     \n";
            std::cout << "     \\ \\ \\ \\ \\ \\        /     \n";
            std::cout << "      \\ \\ \\ \\ \\ \\      /      \n";
            std::cout << "       \\ \\ \\ \\ \\ \\    /       \n";
            std::cout << "        \\_\\_\\_\\_\\_\\__/        \n";
            std::cout << "                             \n";
        };

        // Function to display the defeat message
        auto displayDefeatMessage = []() {
            std::cout << "\nAlien army wins the battle!\n";
        };

        // Animation loop
        for (int i = 0; i < 10; ++i) {
            clearScreen(); // Clear screen before drawing
            drawAlienSpaceship(); // Draw the Alien Spaceship
            drawAlienPlanet(); // Draw the Alien Planet
            Sleep(80); // Pause for 1 second
            clearScreen(); // Clear screen again
            Sleep(80); // Pause for 1 second
        }

        // Display defeat message
        displayDefeatMessage();
        return;

    } else if (type == earthArmyType) {
        // Function to clear the console screen
        auto clearScreen = []() {
            std::cout << "\033[2J\033[1;1H";
        };

        // Function to draw the Earth
        auto drawEarth = []() {
            std::cout << "          .--.              .--.          \n";
            std::cout << "        /  .__\\            /__.__\\.        \n";
            std::cout << "    \\    \\     /          \\      /    /    \n";
            std::cout << "   .-'    |\\_/|    _    |\\_/|    '-.      \n";
            std::cout << "  |       /|   |\\   \\    /|   |\\       |   \n";
            std::cout << "  |      /_|   | \\   |  | |   |_\\      |   \n";
            std::cout << "  |       ||___|  \\_\\ | /_/  |___||      | \n";
            std::cout << "   '-._             \\_/             _.-'  \n";
            std::cout << "       '-._________________________.-'      \n";
        };

        // Function to draw the Earth planet
        auto drawEarthPlanet = []() {
            std::cout << "                  _________    \n";
            std::cout << "             ,-'',  _______\\   \n";
            std::cout << "           ,'      `'-/      `  \n";
            std::cout << "         ,'           (         \n";
            std::cout << "        ;            ___`-.      \n";
            std::cout << "        \\  ______.-'`     `-.   \n";
            std::cout << "         \\                  ;  \\ \n";
            std::cout << "         |                  |   ;\n";
            std::cout << "         |                  |   |\n";
            std::cout << "         |                  |   |\n";
            std::cout << "          \\                /   /\n";
            std::cout << "           `-.__________.-'   / \n";
            std::cout << "                             \n";
        };

        // Function to display the victory message
        auto displayVictoryMessage = []() {
            std::cout << "\nEarth army wins the battle!\n";
        };

        // Animation loop
        for (int i = 0; i < 10; ++i) {
            clearScreen(); // Clear screen before drawing
            drawEarth(); // Draw the Earth
            drawEarthPlanet(); // Draw the Earth planet
            Sleep(80); // Pause for 1 second
            clearScreen(); // Clear screen again
            Sleep(80); // Pause for 1 second
        }

        // Display victory message
        displayVictoryMessage();

    }
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

void simulationManager::addToKilledList(unit *pUnit) {
    killedList.enqueue(pUnit);
}
