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
    randGen randGenObj;
    randGen* RandomGenerator;
public:
    simulationManager(operationMode); //initializes the simulation

    void updateSimulation();

    void addNewUnit(unit *);

    int getAlienUnitCount();
	void manageadding();

    int getEarthUnitCount();

    void showStats(unit *, unit *) const;
};
