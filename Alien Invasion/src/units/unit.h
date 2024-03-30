//
// Created by youss on 3/30/2024.
//
#include "../simulationManager.h"

#ifndef ALIENINVASION_UNIT_H
#define ALIENINVASION_UNIT_H
enum Type {
    EarthUnit, AlienUnit
};

class unit {
protected:
    int ID;
    Type type;
    int joinTime;
    double health;
    double power;
    int attackCapacity;
    simulationManager *simPtr;
public:
    virtual bool attack(unit *) = 0;

    virtual void print() const;

    virtual bool addUnit(unit *) = 0;

    virtual void removeUnit(unit *) = 0;

    int getId() const;

    void setId(int id);

    Type getType() const;

    void setType(Type type);

    int getJoinTime() const;

    void setJoinTime(int joinTime);

    double getHealth() const;

    void setHealth(double health);

    double getPower() const;

    void setPower(double power);

    int getAttackCapacity() const;

    void setAttackCapacity(int attackCapacity);

    simulationManager *getSimPtr() const;

    void setSimPtr(simulationManager *simPtr);

};

int unit::getId() const {
    return ID;
}

void unit::setId(int id) {
    ID = id;
}

Type unit::getType() const {
    return type;
}

void unit::setType(Type nType) {
    unit::type = nType;
}

int unit::getJoinTime() const {
    return joinTime;
}

void unit::setJoinTime(int nJoinTime) {
    unit::joinTime = nJoinTime;
}

double unit::getHealth() const {
    return health;
}

void unit::setHealth(double nHealth) {
    unit::health = nHealth;
}

double unit::getPower() const {
    return power;
}

void unit::setPower(double nPower) {
    unit::power = nPower;
}

int unit::getAttackCapacity() const {
    return attackCapacity;
}

void unit::setAttackCapacity(int nAttackCapacity) {
    unit::attackCapacity = nAttackCapacity;
}

simulationManager *unit::getSimPtr() const {
    return simPtr;
}

void unit::setSimPtr(simulationManager *nSimPtr) {
    unit::simPtr = nSimPtr;
}


#endif //ALIENINVASION_UNIT_H
