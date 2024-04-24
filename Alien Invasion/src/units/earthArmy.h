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
    alienArmy *alienArmyPtr;
    int earthGunneryCount{0};
    int earthSoldierCount{0};
    int earthTankCount{ 0 };
    int earthdestructedGunneryCount{ 0 };
    int earthdestructedSoldierCount{ 0 };
    int earthdestructedTankCount{ 0 };
public:

    int getEarthdestructedGunneryCount() const;

    int getEarthdestructedSoldierCount() const;

    int getEarthdestructedTankCount() const;
    unit *getRandomUnit();

    unit *Attack(unit *enemy);

    bool addUnit(unit *);


    void print();

    unit *getUnit(Type type);

    int getEarthSoldierCount();

    int getEarthTankCount();

    int getEarthGunneryCount();
};


