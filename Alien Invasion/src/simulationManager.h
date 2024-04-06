//
// Created by youss on 3/30/2024.
//
#pragma once

#include "./ds/LinkedQueue.h"
#include "randGen.h"

#include <fstream>
#include "randGen.h"

class randGen;

enum operationMode {
    Silent, Interactive
};

class randGen;

class earthArmy;

class alienArmy;

class unit;

class simulationManager {
protected:
    operationMode operationModeVal;
    alienArmy *alienArmyPtr;
    earthArmy *earthArmyPtr;
    LinkedQueue<unit *> tempList;
    randGen *RandomGenerator;
public:
    simulationManager(operationMode); //initializes the simulation

    void updateSimulation(int);

    void addNewUnit(unit *);

    int getAlienUnitCount();

    void manageadding(int);

    int getEarthUnitCount();

    void showStats(unit *, unit *) const;

    void phase12TestFunction(int x);

};
