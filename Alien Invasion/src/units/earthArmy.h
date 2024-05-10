#pragma once

#include "unit.h"
#include "../ds/ArrayStack.h"
#include "../ds/priQueue.h"
#include "../ds/LinkedQueue.h"
#include "../ds/ArrayStack.h"
#include "Army.h"
#include "Tank.h"

class Esoldier;

class Egunnery;

class alienArmy;

enum earthType {
    ES, EG, ET
};

class earthArmy : public Army {

    LinkedQueue<Esoldier *> ESlist;
    priQueue<Egunnery *> EGlist;
    ArrayStack<Tank *> TankList;
    alienArmy *alienArmyPtr{nullptr};
    int earthGunneryCount{0};
    int earthSoldierCount{0};
    int earthTankCount{0};
    int infectedSoldierCount{0};
public:
    int getEarthInfectedSoldierCount() const;

    void setEarthInfectedSoldierCount(const int earthInfectedSoldierCount);

public:
    earthArmy();


    unit *getRandomUnit();


    bool addUnit(unit *);


    void print();

    unit *getUnit(Type type);

    int getEarthSoldierCount();

    int getEarthTankCount();

    int getEarthGunneryCount();

    unit *getAnEnemyFor(Type attackersType, int enemyType = 0);
};


