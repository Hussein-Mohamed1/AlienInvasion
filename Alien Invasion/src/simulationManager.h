//
// Created by youss on 3/30/2024.
//
#pragma once

#include "./ds/LinkedQueue.h"
#include "randGen.h"
#include "units/alienArmy.h"
#include "units/earthArmy.h"
#include <fstream>
#include "randGen.h"
#include"units/HealUnit.h"

class randGen;

enum operationMode {
    Silent, Interactive
};

class randGen;


class unit;


class simulationManager {
protected:
    operationMode operationModeVal;
    alienArmy *alienArmyPtr;
    earthArmy *earthArmyPtr;
    LinkedQueue<unit *> tempList;
    LinkedQueue<unit *> KilledList;
    randGen *RandomGenerator;
    ArrayStack < HealUnit*> HealList;
    LinkedQueue<unit*> UnitMaintenceList;  
public:
    static void intro();

    simulationManager(operationMode); //initializes the simulation

    void updateSimulation(int);

    void addNewUnit(unit *);

    void manageAdding(int);

    void ManageHealing();

    void showStats(unit *, unit *) const;

    int getAlienArmyUnitsCount() const;

    int getEarthArmyUnitsCount() const;

    void handleUnit(unit *attackingUnit, unit *&defendingUnit, Army *defendingArmy);

    void printKilledList();

    void printTempList();
};
