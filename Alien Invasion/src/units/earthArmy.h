#pragma once

#include "unit.h"
#include "../ds/ArrayStack.h"
#include "../ds/priQueue.h"
#include "../ds/LinkedQueue.h"
#include "../ds/ArrayStack.h"
#include "Army.h"
#include "Tank.h"
#include "SaverUnit.h"

class Esoldier;

class Egunnery;

class alienArmy;

class SaverUnit;

enum earthType {
    ES, EG, ET
};

class earthArmy : public Army {

    LinkedQueue<Esoldier *> ESlist;
    LinkedQueue<SaverUnit *> SaverUnitList;
    status SAVStatus{hasntCallSAV};

    priQueue<Egunnery *> EGlist;
    ArrayStack<Tank *> TankList;
    alienArmy *alienArmyPtr{nullptr};
    int infectedSoldierCount{0};
    int totalInfectedSoldiers{0};
    int numOfHealedUnits{0};
public:
    int getTotalInfectedSoldiers() const;

    void incTotalInfectedSoldiersCount();

    void incNumOfHealedUnits();

    int getEarthInfectedSoldierCount() const;

    void setEarthInfectedSoldierCount(int earthInfectedSoldierCount);

    earthArmy(simulationManager *pManager);


    unit *getRandomUnit();


    bool addUnit(unit *);


    void print();

    unit *getUnit(Type type);

    int getEarthSoldierCount();

    int getEarthTankCount();

    int getEarthGunneryCount();

    unit *getAnEnemyFor(Type attackersType, int enemyType = 0);

    status getSAVstatus() const;

    void destroySavArmy();

    virtual ~earthArmy();

    int getTotalNumOfHealedUnits() const;

    void setSAVstatus(status status1);
};


