//
// Created by youss on 3/30/2024.
#pragma once

#include <iostream>

class simulationManager;

using namespace std;
enum Type {
    Gunnery, EarthSoldier, EarthTank, alienSoldier, DronePair, MonsterType
};

enum armyType {
    earthUnit, alienUnit
};

class unit {
protected:
    int ID;
    Type type;
    int Tj;
    double health;
    double power;
    int attackCapacity;
    simulationManager *simPtr;
    int Ta;
    int Td;
public:
    unit();
    unit(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr);

    virtual bool damageEnemy(unit *);

    virtual void print() const;

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
    int getDestructionTime() const;

    void setDestructionTime(int t);
    int getfirstAttackedTime() const;

    void setfirstAttackedTime(int t);
    int getDf() const;
    int getDd() const;
    int getDb() const;
};

