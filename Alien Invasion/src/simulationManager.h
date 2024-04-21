//
// Created by youss on 3/30/2024.
//
#pragma once

#include "./ds/LinkedQueue.h"
#include "randGen.h"
#include <iostream>
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
    fstream OutputFile;
    int sumOfEDf{ 0 };
    int EDfcount{ 0 };
    int sumOfEDd{ 0 };
    int EDdcount{ 0 };
    int sumOfEDb{ 0 };
    int EDbcount{ 0 };
    int sumOfADf{ 0 };
    int ADfcount{ 0 };
    int sumOfADd{ 0 };
    int ADdcount{ 0 };
    int sumOfADb{ 0 };
    int ADbcount{ 0 };
    int numofHealedunits{ 0 };
public:
    simulationManager(operationMode); //initializes the simulation

    void updateSimulation(int);

    void addNewUnit(unit *);

    void manageAdding(int);
    void loadtoOutputFile(LinkedQueue< unit > KilledList);
    void showStats(unit *, unit *) const;

    void phase12TestFunction(int x);

    int getAlienArmyUnitsCount() const;

    int getEarthArmyUnitsCount() const;
    ~simulationManager();
};
