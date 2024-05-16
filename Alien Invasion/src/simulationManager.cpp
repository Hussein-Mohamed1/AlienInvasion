//
// Created by youss on 3/30/2024.
//
#pragma once

#include <string>
#include <mutex>
#include "simulationManager.h"
#include "./units/alienArmy.h"
#include "./units/earthArmy.h"
#include "./units/unit.h"
#include "windows.h"
#include "iostream"
#include "./units/Esoldier.h"

armyType (*getArmyType)(unit *armyUnit) =[](
        unit *armyUnit) -> armyType { ///@details just a utility method to get the type of the army
    if (armyUnit->getType() == EarthSoldier || armyUnit->getType() == Saver || armyUnit->getType() == EarthTank ||
        armyUnit->getType() == Gunnery)
        return earthArmyType;
    else
        return alienArmyType;
};

simulationManager::simulationManager(operationMode operationModeVal) : operationModeVal(operationModeVal) {
    alienArmyPtr = new alienArmy(this);
    earthArmyPtr = new earthArmy(this);
    srand(time(nullptr));
    RandomGenerator = new randGen(this);
}

winner simulationManager::assertWinner() const {
    if (currentTimeStep >= 40)
        if (getAlienArmyUnitsCount() == 0 && getEarthArmyUnitsCount() >= 1)
            return earthWon;
        else if (getEarthArmyUnitsCount() == 0 && getAlienArmyUnitsCount() >= 1)
            return aliensWon;
        else return Nan;
    return Nan;
}

winner simulationManager::updateSimulation(int timestep) {
    if (getEarthArmyUnitsCount() != 0 &&
            earthArmyPtr->getSAVstatus() != SAVBeingUsed)
        infectUnits();

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
        cout << "Total Infected Units: " << getTotalInfectedCount() << endl;
    }

    unit *earthUnit1 = earthArmyPtr->getUnit(EarthSoldier);
    unit *earthUnit2 = earthArmyPtr->getUnit(EarthTank);
    unit *earthUnit3 = earthArmyPtr->getUnit(Gunnery);
    bool b1 = handleUnit(earthUnit1);
    bool b2 = handleUnit(earthUnit2);
    bool b3 = handleUnit(earthUnit3);

    unit *alienUnit1 = alienArmyPtr->getUnit(alienSoldier);
    unit *alienUnit2 = alienArmyPtr->getUnit(MonsterType);
    unit *alienUnit3 = alienArmyPtr->getDronePair();
    bool b4 = handleUnit(alienUnit1);
    bool b5 = handleUnit(alienUnit2);
    bool b6 = handleUnit(alienUnit3);

    if (operationModeVal == Interactive) {
        earthArmyPtr->print();
        alienArmyPtr->print();
        printKilledList();
    }

    if (!(b1 || b2 || b3 || b4 || b5 || b6) && currentTimeStep >= 300 && getEarthArmyUnitsCount() &&
            getAlienArmyUnitsCount()) {
        printWinner(draw);
        return draw;
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
        if (newUnit->getType() == Saver) {
            earthArmyPtr->addUnit(newUnit);
        }
    }
}


/////@param AttackingUnit: The unit attacking.
/////@param DamagedUnit: The unit being attacked.
//void simulationManager::showStats(unit *AttackingUnit, unit *DamagedUnit) const {
//    if (operationModeVal == Interactive)
//        if (AttackingUnit && DamagedUnit && AttackingUnit->getType() == DronePair &&
//            DamagedUnit->getType() == EarthTank)
//            cout << "ID:" << AttackingUnit->getId() << ":" << [&AttackingUnit]() -> string {
//                switch (AttackingUnit->getType()) {
//                    case EarthSoldier:
//                        return "Earth Soldier ";
//                    case EarthTank:
//                        return "Earth Tank";
//                    case Gunnery:
//                        return "Gunnery";
//                    case alienSoldier:
//                        return "Alien Soldier";
//                    case DronePair:
//                        return "Drone";
//                    case MonsterType:
//                        return "Monster";
//                    case Saver:
//                        return "Support Unit";
//                }
//            }()
//                 << " has attacked unit of ID:"
//                 << DamagedUnit->getId()
//                 << " " << [&DamagedUnit]() -> string {
//                switch (DamagedUnit->getType()) {
//                    case EarthSoldier:
//                        return "Earth Soldier";
//                    case EarthTank:
//                        return "Earth Tank";
//                    case Gunnery:
//                        return "Gunnery";
//                    case alienSoldier:
//                        return "Alien Soldier";
//                    case DronePair:
//                        return "Drone";
//                    case MonsterType:
//                        return "Monster";
//                    case Healer:
//                        return "Healer";
//                    case Saver:
//                        return "Support Unit";
//                }
//            }() << endl;
//}

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
    if (RandomGenerator->creatSaverUnit() && earthArmyPtr->getSAVstatus() == hasntCallSAV) {
        for (int i{}; i < RandomGenerator->getnumofSaver(); i++) {
            addNewUnit(RandomGenerator->generatSaver(timestep));
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

void simulationManager::loadToOutputFile() {
    unit *temp{nullptr};

    while (UnitMaintenanceList.dequeue(temp)) {
        temp->setDestructionTime(currentTimeStep);
        killedList.enqueue(temp);
    }

    ofstream OutputFile("output-" + to_string((time(0) % 3600) / 60) + ".txt", ios::in | ios::out | ios::app);
    int sumOfEDf{0}, EDfcount{0}, sumOfEDd{0}, EDdcount{0}, sumOfEDb{0}, EDbcount{0}, sumOfADf{0}, ADfcount{
            0}, sumOfADd{0}, ADdcount{0}, sumOfADb{0}, ADbcount{
            0},
            alienDestructedSoldierCount{0},
            alienDestructedMonsterCount{0},
            alienDestructedDroneCount{0},
            earthdestructedGunneryCount{0},
            earthdestructedSoldierCount{0},
            earthdestructedTankCount{0};
    unit *killedU{nullptr};

    // Check if the file was opened successfully
    if (!OutputFile.is_open()) {
        cout << "Unable to open file for writing." << endl;
        // Handle the error appropriately, e.g., by throwing an exception
        throw std::runtime_error("Failed to open output file.");
    }

    // Write data to the file in the constructor
    OutputFile << "TimeDeath     ID      Tj      Df      Dd      Db" << endl;

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

        delete killedU;
    }

    switch (assertWinner()) {
        case earthWon :
            OutputFile << "========================= Earth Win =========================\n";
            break;
        case aliensWon:
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

    OutputFile << "Percentage of Total Infected Units---> "
               << (earthArmyPtr->getEarthSoldierCount() + earthdestructedSoldierCount ?
                   (to_string(double(getTotalInfectedCount()) /
                              (earthArmyPtr->getEarthSoldierCount() +
                               earthdestructedSoldierCount) * 100)) : "0") << "%" << endl;
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
        OutputFile << "percentage of total Healed units----> "
                   << (double(earthArmyPtr->getTotalNumOfHealedUnits()) / totalEarthArmy) * 100
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
                                                            alienDestructedMonsterCount + 1)) * 100 << endl;
    int totaldestructedAlienArmy =
            alienDestructedDroneCount + alienDestructedMonsterCount + alienDestructedSoldierCount;
    int totalAlienArmy = alienArmyPtr->getCurrentAlienSoldierCount() + alienArmyPtr->getCurrentAlienDroneCount() +
            alienArmyPtr->getCurrentMonstersIndex() + totaldestructedAlienArmy + 1;
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

    OutputFile << "======================================== For Bonus =============================\n";

    OutputFile.close();
}

/// ! When Insert in PriQueue observe that the decleartion was changed for UML
void simulationManager::ManageHealing() {

    unit *Healer;
    if (!HealList.pop(Healer))
        return;
    int Cap = Healer->getAttackCapacity();


    LinkedQueue<unit *> tank;

    priQueue<unit *> Soldiers;

    while (!UnitMaintenanceList.isEmpty()) {
        unit *Inj{nullptr};
        UnitMaintenanceList.dequeue(Inj);
        if (Inj->getType() == EarthSoldier) {
            Soldiers.enqueue(Inj, Inj->getHealth(), 1);
        } else if (Inj->getType() == EarthTank) {
            tank.enqueue(Inj);
        }

    }

    while (0 < Cap && !Soldiers.isEmpty()) {
        unit *InjSol{nullptr};
        int p;
        Soldiers.dequeue(InjSol, p);

        if (InjSol->GetStillHealing() == 10)
            addToKilledList(InjSol);

        else {
            if (dynamic_cast<Esoldier *>(InjSol)->is_Infected() && Cap >= 2 ||
                !dynamic_cast<Esoldier *>(InjSol)->is_Infected()) {
                Healer->damageEnemy(InjSol);
                earthArmyPtr->incNumOfHealedUnits();
                InjSol->UpdateStillHealing();
                Esoldier *tempSoldier = dynamic_cast<Esoldier *>(InjSol);

                if (tempSoldier->is_Infected()) {
                    Cap--;
                    tempSoldier->makeImmune();
                }
                Cap--;

                returnUnitToArmy(InjSol);
            } else UnitMaintenanceList.enqueue(InjSol);

        }
    }


    while (0 < Cap && !tank.isEmpty()) {
        unit *InjTank;
        tank.dequeue(InjTank);


        if (InjTank->GetStillHealing() == 10)
            addToKilledList(InjTank);

        else {
            Healer->damageEnemy(InjTank);
            earthArmyPtr->incNumOfHealedUnits();
            InjTank->UpdateStillHealing();
            returnUnitToArmy(InjTank);
            Cap--;
        }
    }


    while (!Soldiers.isEmpty()) {
        unit *S{nullptr};
        int p;
        Soldiers.dequeue(S, p);
        UnitMaintenanceList.enqueue(S);
    }
    while (!tank.isEmpty()) {
        unit *t;
        tank.dequeue(t);
        UnitMaintenanceList.enqueue(t);
    }


    if (Cap != Healer->getAttackCapacity())
        delete Healer;
    else HealList.push(Healer);
}

simulationManager::~simulationManager() {
    alienArmyPtr->~alienArmy();
    earthArmyPtr->~earthArmy();
    delete RandomGenerator;
}

bool simulationManager::handleUnit(unit *attackingUnit) {
    LinkedQueue<unit *> tempList;

    bool enqueuedOnce = false;

    unit *secondAttackingDrone{nullptr};

    if (!attackingUnit) { return false; }
    else {
        unit *defendingUnit1{nullptr};
        unit *defendingUnit2{nullptr};

        ///@note if the attacking unit is a drone , pick another drone to attack. if no other drone exists then return the attacking drone to its army;
        if (attackingUnit->getType() == DronePair) {
            secondAttackingDrone = alienArmyPtr->getDronePair();
            if (!secondAttackingDrone) {
                alienArmyPtr->addUnit(attackingUnit);
                return false;
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
                if (attackingUnit->damageEnemy(defendingUnit1)) {
                    if (secondAttackingDrone)
                        secondAttackingDrone->damageEnemy(defendingUnit1);

                    ///@details used to handle the adding of the attacking unit to templist only once
                    if (!enqueuedOnce) {
                        enqueuedOnce = true;
                        tempList.enqueue(attackingUnit);
                        if (secondAttackingDrone)
                            tempList.enqueue(secondAttackingDrone);
                    }

                    tempList.enqueue(defendingUnit1);
                }
            }

            if (defendingUnit2) {
                if (attackingUnit->damageEnemy(defendingUnit2)) {
                    if (secondAttackingDrone)
                        secondAttackingDrone->damageEnemy(defendingUnit2);


                    ///@details used to handle the adding of the attacking unit to templist only once
                    if (!enqueuedOnce) {
                        enqueuedOnce = true;
                        tempList.enqueue(attackingUnit);
                        if (secondAttackingDrone)
                            tempList.enqueue(secondAttackingDrone);
                    }

                    tempList.enqueue(defendingUnit2);
                } else returnUnitToArmy(defendingUnit2);
            }
        }
    }

    if (!enqueuedOnce) {
        returnUnitToArmy(attackingUnit);
        if (secondAttackingDrone)
            returnUnitToArmy(secondAttackingDrone);
        return false;
    }
    if (operationModeVal == Interactive)
        printCurrentFightInfo(tempList);
    unit *temp{nullptr};
    while (tempList.dequeue(temp))
        returnUnitToArmy(temp);
    return true;
}


void simulationManager::returnUnitToArmy(unit *unitPtr) {
    if (unitPtr) {
        if (floor(unitPtr->getHealth()) <= 0) {
            if (unitPtr->getType() == EarthSoldier && dynamic_cast<Esoldier *>(unitPtr)->is_Infected())
                earthArmyPtr->setEarthInfectedSoldierCount(earthArmyPtr->getEarthInfectedSoldierCount() - 1);
            unitPtr->setDestructionTime(getCurrentTimeStep());
            addToKilledList(unitPtr);
            return;
        }

        if (unitPtr->typeToString() != "EG" && unitPtr->getArmyType() == earthArmyType &&
            unitPtr->getHealth() <= 0.2 * unitPtr->GetOriginalHealth()) {
            if (unitPtr->getType() == EarthSoldier && dynamic_cast<Esoldier *>(unitPtr)->is_Infected())
                earthArmyPtr->setEarthInfectedSoldierCount(earthArmyPtr->getEarthInfectedSoldierCount() - 1);
            UnitMaintenanceList.enqueue(unitPtr);
            return;
        }

        unitPtr->resetStillHealing();

        if ((*getArmyType)(unitPtr) == alienArmyType)
            alienArmyPtr->addUnit(unitPtr);
        else earthArmyPtr->addUnit(unitPtr);
    }
}


int simulationManager::getCurrentTimeStep() const {
    return currentTimeStep;
}

void simulationManager::printCurrentFightInfo(LinkedQueue<unit *> &tempList) {
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
    while (tempList2.dequeue(unitShot))
        tempList.enqueue(unitShot);

}

void simulationManager::printWinner(winner type) {
    system("cls");
    //create an ascii art for the winner
    if (type == aliensWon) {
        string alienWinMessage1 = "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "████████████████████████████████████████████▓█████████▓███████████████████████████████████\n"
                                  "██████████████████████████████████████████▓████████▓▓███▓█████████████████████████████████\n"
                                  "██████████████████████████████████████▓▓██████▓█▓█▓███████████████████████████████████████\n"
                                  "██████████████████████████████████████████▓████▓▓███▓███▓▓████████████████████████████████\n"
                                  "███████████████████████████████████████████▒░▒▒▓▓▓████████████████████████████████████████\n"
                                  "██████████████████████████████████████████▒░░░░░░░▓███████████████████████████████████████\n"
                                  "█████████████████████████████████████████░░░░░░░░░░███████████████████████████████████████\n"
                                  "████████████████████████████████████████░░░░░░░░░░░▒██████████████████████████████████████\n"
                                  "██████████████████████████████████████▓░░░░░░░░░░█▒░▓█████████████████████████████████████\n"
                                  "█████████████████████████████████████▒░░░░░░░░░░▓██▒░█████████████████████████████████████\n"
                                  "████████████████████████████████████░░░░░░░░░░░░▓▒▓░░▓████████████████████████████████████\n"
                                  "███████████████████████████████████▒░░░░░░░░░░░░░░░░░▒████████████████████████████████████\n"
                                  "████████████████████████████████████▓▒▒░░░░░░░░░░░░░░░████████████████████████████████████\n"
                                  "███████████████████████████████████████████▓▓▒▒▒▒▒▒▓▓█████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████▒▓▒█▒▒█▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████▒▓▒██▓█▒████████████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▒▓███▓██████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████";

        string alienWinMessage2 = "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "████████████████████████████████████████████▓█████████▓███████████████████████████████████\n"
                                  "██████████████████████████████████████████▓████▓████▓███▓█████████████████████████████████\n"
                                  "██████████████████████████████████████▓▓██████▓█▓█▓███████████████████████████████████████\n"
                                  "██████████████████████████████████████████▓▓███▓████▓████▓████████████████████████████████\n"
                                  "███████████████████████████████████████████████▓▓▓▓▓▓▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████▓░░░▒░░░▓███████████████████████████████████\n"
                                  "██████████████████████████████████████████████░░░▒█▓░░░▒██████████████████████████████████\n"
                                  "█████████████████████████████████████████████░░░░████░░░░█████████████████████████████████\n"
                                  "████████████████████████████████████████████▓░░░░▒██░░░░░░████████████████████████████████\n"
                                  "████████████████████████████████████████████▒░░░░░░░░░░░░░░███████████████████████████████\n"
                                  "███████████████████████████████████████████▓░░░░░░░░░░░░░░░░▓█████████████████████████████\n"
                                  "███████████████████████████████████████████░░░░░░░░░░░░░░░░░░▓████████████████████████████\n"
                                  "██████████████████████████████████████████▓░░░░░░░░░░░░░░░▒▓██████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▓▓▒▒▒▓▓▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████▒▓▒▓▓▒▓▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████░▓▒█▓▓█▓████████████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▒▓██▓███████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████";

        string alienWinMessage3 = "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "████████████████████████████████████████████▓█████████▓███████████████████████████████████\n"
                                  "██████████████████████████████████████████▓█████████▓███▓█████████████████████████████████\n"
                                  "██████████████████████████████████████▓▓██████▓█▓█▓███████████████████████████████████████\n"
                                  "██████████████████████████████████████████▓▓███▓████▓████▓████████████████████████████████\n"
                                  "███████████████████████████████████████████████▓▓███▓▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████▓░░▒█▓░░▓███████████████████████████████████\n"
                                  "██████████████████████████████████████████████░░░▓██▓░░▒██████████████████████████████████\n"
                                  "█████████████████████████████████████████████░░░░░█▓▒░░░░█████████████████████████████████\n"
                                  "████████████████████████████████████████████▓░░░░░▒░▒░░░░░████████████████████████████████\n"
                                  "████████████████████████████████████████████▒░░░░░░░░░░░░░░███████████████████████████████\n"
                                  "███████████████████████████████████████████▓░░░░░░░░░░░░░░░░▓█████████████████████████████\n"
                                  "███████████████████████████████████████████░░░░░░░░░░░░░░░░░░▓████████████████████████████\n"
                                  "██████████████████████████████████████████▓░░░░░░░░░░░░░░░▒▓▓█████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▓▓▒▒▒▓▓▓████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▒█░▓▓▒▓▓████████████████████████████████████\n"
                                  "█████████████████████████████████████████████▓▒▓▒▓▓▓█▒████████████████████████████████████\n"
                                  "█████████████████████████████████████████████▒░▓██▓███████████████████████████████████████\n"
                                  "██████████████████████████████████████████████████████████████████████████████████████████";
        string alienWinMessage4;
        auto displayDefeatMessage = [alienWinMessage1, alienWinMessage2, alienWinMessage3, alienWinMessage4]() {
            system("cls");
            cout << alienWinMessage1;
            Sleep(500);
            system("cls");

            cout << alienWinMessage2;
            Sleep(500);
            system("cls");

            cout << alienWinMessage3;
            Sleep(500);
            system("cls");

            cout << alienWinMessage4;
            Sleep(500);
            system("cls");

            cout
                    << "\n   _____  .__  .__                                                     .__                  __  .__             ___.           __    __  .__        ._.\n"
                       "  /  _  \\ |  | |__| ____   ____   _____ _______  _____ ___.__. __  _  _|__| ____   ______ _/  |_|  |__   ____   \\_ |__ _____ _/  |__/  |_|  |   ____| |\n"
                       " /  /_\\  \\|  | |  |/ __ \\ /    \\  \\__  \\\\_  __ \\/     <   |  | \\ \\/ \\/ /  |/    \\ /  ___/ \\   __\\  |  \\_/ __ \\   | __ \\\\__  \\\\   __\\   __\\  | _/ __ \\ |\n"
                       "/    |    \\  |_|  \\  ___/|   |  \\  / __ \\|  | \\/  Y Y  \\___  |  \\     /|  |   |  \\\\___ \\   |  | |   Y  \\  ___/   | \\_\\ \\/ __ \\|  |  |  | |  |_\\  ___/\\|\n"
                       "\\____|__  /____/__|\\___  >___|  / (____  /__|  |__|_|  / ____|   \\/\\_/ |__|___|  /____  >  |__| |___|  /\\___  >  |___  (____  /__|  |__| |____/\\___  >_\n"
                       "        \\/             \\/     \\/       \\/            \\/\\/                      \\/     \\/             \\/     \\/       \\/     \\/                     \\/\\/\n";
        };
        Sleep(1000);

        displayDefeatMessage();
        return;

    } else if (type == earthWon) {
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

    } else if (type == draw) {

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
    cin.ignore();
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

int simulationManager::canInfect() const {
    return RandomGenerator->canInfected();
}

int simulationManager::getEarthInfectedSoldierCount() const {
    return earthArmyPtr->getEarthInfectedSoldierCount();
}

void simulationManager::setEarthInfectedSoldierCount(const int earthInfectedSoldierCount) {
    earthArmyPtr->setEarthInfectedSoldierCount(earthInfectedSoldierCount);
}

void simulationManager::infectUnits() {

    int crtInfectCount = this->getEarthInfectedSoldierCount();
    for (int i = 0; i < crtInfectCount; ++i) {
        int random = rand() % 100;

        if (random <= 2) {
            int idxOfRandomSoldier = rand() % this->getEarthSoldiersCount();
            unit *tempSoldier{nullptr};
            LinkedQueue<unit *> temp;
            int j{1};

            ///@details if sav is being used, getUnit will return one from the sav instead of normal soldiers
            for (; j < idxOfRandomSoldier; ++j) {
                tempSoldier = this->earthArmyPtr->getUnit(EarthSoldier);
                if (tempSoldier)
                    temp.enqueue(tempSoldier);
            }

            Esoldier *soldierToBeInfected{nullptr};
            unit *tempEarthSoldier = this->earthArmyPtr->getUnit(EarthSoldier);
            soldierToBeInfected = dynamic_cast<Esoldier *>(tempEarthSoldier);
            if (soldierToBeInfected)
                soldierToBeInfected->setInfected();
            else
                throw runtime_error("soldierToBeInfected is null");

            this->returnUnitToArmy(soldierToBeInfected);

            while (temp.dequeue(tempSoldier))
                this->returnUnitToArmy(tempSoldier);
        }
    }

}


int simulationManager::getCallSAVPer() const {
    return RandomGenerator->get_probofcallSaver();
}

void simulationManager::chooseScenario() {


    int choice{0};
    cout << "please choose A scenario of fight : \n1- strong Earth & Weak Alien \n"
            << "2- Weak Earth & strong Alien \n3- Weak Earth & Weak Alien \n4- strong Earth & strong Alien \n";
    cin >> choice;
    switch (choice) {
        case 1:
            RandomGenerator->set_Scenario("S&W");
            break;
        case 2:
            RandomGenerator->set_Scenario("W&S");
            break;
        case 3:
            RandomGenerator->set_Scenario("W&W");
            break;
        case 4:
            RandomGenerator->set_Scenario("S&S");
            break;
        default:
            cout << "\nPlease choose one of the options\n";
            Sleep(1000);
            system("cls");
            chooseScenario();
    }

    system("CLS");
    RandomGenerator->loadInputFile();
}

string simulationManager::getCurrentScenario() {
    return RandomGenerator->get_Scenario();
}

void simulationManager::printUnitMaintenanceList() {
    cout << "Maintenance List: [";
    unit *temp{nullptr};
    LinkedQueue<unit *> tempQueue;
    while (UnitMaintenanceList.dequeue(temp)) {
        cout << to_string(temp->getId()) + " " + temp->typeToString() << (UnitMaintenanceList.isEmpty() ? "" : ", ");
        tempQueue.enqueue(temp);
    }
    cout << "]\n";
    while (tempQueue.dequeue(temp))
        UnitMaintenanceList.enqueue(temp);
}

void simulationManager::incTotalInfectCount() {
    earthArmyPtr->incTotalInfectedSoldiersCount();
}

int simulationManager::getTotalInfectedCount() const {
    return earthArmyPtr->getTotalInfectedSoldiers();
}

operationMode simulationManager::getOperationMode() {
    return operationModeVal;
}
