//
// Created by youss on 3/30/2024.
//
#pragma once

#include "./ds/LinkedQueue.h"
#include "randGen.h"
#include "./units/alienArmy.h"
#include "./units/earthArmy.h"
#include <fstream>
#include "randGen.h"

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
public:
    static void intro();

    simulationManager(operationMode); //initializes the simulation

    void updateSimulation(int);

    void addNewUnit(unit *);

    void manageAdding(int);

    void phase12TestFunction(int x);

    int getAlienArmyUnitsCount() const;

    int getEarthArmyUnitsCount() const;


    void printKilledList();

    void printTempList();
};
