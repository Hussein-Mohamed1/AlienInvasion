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
public:
    int getEarthGunneryCount() const;

    int getEarthSoldierCount() const;

    int getEarthTankCount() const;

private:
    int earthTankCount{0};

public:

    unit *getRandomUnit();

    unit *Attack(unit *enemy);

    bool addUnit(unit *);

    void removeUnit(unit *);

    void print();

    unit *getUnit(Type type);
};


