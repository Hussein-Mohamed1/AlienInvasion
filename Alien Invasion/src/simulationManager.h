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
    LinkedQueue<unit *> killedList;
    randGen *RandomGenerator;
    int currentTimeStep{0};

    ArrayStack<unit *> HealList;
    LinkedQueue<unit *> UnitMaintenanceList;
public:
    static void intro();

    simulationManager(operationMode); //initializes the simulation

    winner updateSimulation(int);
    void chooseScenario();
    void addNewUnit(unit *);

    void manageAdding(int);

    void ManageHealing();

    void loadToOutputFile();

//    void showStats(unit *, unit *) const;

    int getAlienArmyUnitsCount() const;

    int getEarthArmyUnitsCount() const;

    bool handleUnit(unit *attackingUnit);

    void printKilledList();

    void printHealandUnitMaintenanceLists();

    void returnUnitToArmy(unit *);

    int getCurrentTimeStep() const;

    void printCurrentFightInfo(LinkedQueue<unit *> &tempList);

    winner assertWinner() const;

    static void printWinner(winner type);

    int getAlienSoldiersCount() const;

    int getEarthSoldiersCount() const;

    void addToKilledList(unit *pUnit);

    int canInfect() const;

    int getEarthInfectedSoldierCount() const;

    void setEarthInfectedSoldierCount(const int earthInfectedSoldierCount);

    int getTotalInfectedCount() const;

    void incTotalInfectCount();

    void infectUnits();

    int getCallSAVPer() const;

    virtual ~simulationManager();

    string getCurrentScenario();

    operationMode getOperationMode();
    void choose_Mood();
};
