//
// Created by youss on 3/30/2024.
//
#pragma once

#include "../simulationManager.h"
#include "unit.h"

unit::unit() {};

void unit::setDestructionTime(int t) {
    TimeDeath = t;
}

int unit::getDestructionTime() const {
    return TimeDeath;
}

void unit::setfirstAttackedTime(int t) {
    TimeFirstAttacked = t;
}

int unit::getfirstAttackedTime() const {
    return TimeFirstAttacked;
}

int unit::getDf() const {
    return TimeFirstAttacked - this->joinTime;
}

int unit::getDd() const {
    return TimeDeath - TimeFirstAttacked;
}

int unit::getDb() const {
    return TimeDeath - this->joinTime;
}

void unit::print() const {
    cout << "ID: " << ID << " type: " << [this]() -> string {
        switch (type) {
            case Gunnery:
                return "Gunnery";
            case EarthSoldier:
                return "Earth Soldier";
            case EarthTank:
                return "Earth Tank";
            case alienSoldier:
                return "alien Soldier";
            case DronePair:
                return "Drone";
            case MonsterType:
                return "Monster";
        }
    }();
    cout << " join Time: " << joinTime << " health: "
         << health
         << " power: " << power << " attack Capacity: " << attackCapacity;
}

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

unit::unit(int id, Type type, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr)
        : ID(id), type(type), joinTime(joinTime), health(health), power(power), attackCapacity(attackCapacity),
          simPtr(simPtr), StillInHealingList(false), OriginalHealth(health) {}

bool unit::damageEnemy(unit *Enemy) {
    if (floor(health) == 0) {
        power = 0;
        return false;
    }
    if (Enemy) {
        double Damage = (getPower() * (getHealth() / 100)) / sqrt(Enemy->getHealth());
        double NewHealth = Enemy->getHealth() - Damage;
        if (floor(NewHealth) > 0)
            Enemy->setHealth(NewHealth);
        else {
            Enemy->setHealth(0);
        }
        if (Enemy->getfirstAttackedTime() == 0)
            Enemy->setfirstAttackedTime(simPtr->getCurrentTimeStep());
        return true;
    }
    return false;
}

void unit::UpdateStillHealing() {
    StillInHealingList++;
}

int unit::GetStillHealing() const {
    return StillInHealingList;
}

double unit::GetOriginalHealth() const {
    return OriginalHealth;
}

armyType unit::getArmyType() {
    if (this->getType() == EarthSoldier || this->getType() == EarthTank || this->getType() == Gunnery)
        return earthArmyType;
    else
        return alienArmyType;
}

string unit::typeToString() {
    switch (type) {
        case Gunnery:
            return "EG";
        case EarthSoldier:
            return "ES";
        case EarthTank:
            return "ET";
        case alienSoldier:
            return "AS";
        case DronePair:
            return "AD";
        case MonsterType:
            return "AM";
        case Healer:
            return "EH";
        case Saver:
            return "SV";
        default:
            break;
    }
}