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
    int unitCount;
    LinkedQueue<Esoldier *> ESlist;
    priQueue<Egunnery *> EGlist;
    ArrayStack<unit *> TankList;
    alienArmy *alienArmyPtr;
public:

    unit * EnemyDamage(unit *enemy);

    bool addUnit(unit *);

    void removeUnit(unit *);

    void print() const;

    int getUnitCount() const;
};


