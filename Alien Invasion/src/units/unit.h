//
// Created by youss on 3/30/2024.
#pragma once

#include <iostream>

class simulationManager;

using namespace std;
enum Type {
    Gunnery, EarthSoldier, EarthTank, alienSoldier, DronePair, MonsterType, Healer
};

enum armyType {
    earthArmyType, alienArmyType, Nan
};

class unit {
protected:

    int ID;
    Type type ;
    int joinTime;
    double health;
    double power;
    int attackCapacity;
    simulationManager *simPtr{nullptr};
    bool StillInHealingList{false};
    double OriginalHealth{0};
    int TimeFirstAttacked{0};
    int TimeDeath{0};
public:
    unit(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr);

    virtual bool damageEnemy(unit *);

    virtual void print() const;

    double GetOriginalHealth() const;

    int getId() const;

    int GetStillHealing() const;

    void UpdateStillHealing();

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
    armyType getArmyType();
    unit();
    string typetostring(Type);
};

