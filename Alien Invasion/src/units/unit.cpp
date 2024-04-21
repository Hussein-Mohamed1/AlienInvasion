//
// Created by youss on 3/30/2024.
//
#pragma once

#include "../simulationManager.h"
#include "unit.h"
unit::unit() {}
void unit::setDestructionTime(int t)
{
    Td = t;
}
int unit::getDestructionTime() const
{
    return Td;
}
void unit::setfirstAttackedTime(int t)
{
    Ta = t;
}
int unit::getfirstAttackedTime() const
{
    return Ta;
}
int unit::getDf() const
{
    return Ta - Tj;
}
int unit::getDd() const
{
    return Td - Ta;
}
int unit::getDb() const
{
    return Td - Tj;
}
void unit::print() const {
    cout << "ID: " << ID << " type: " << type << " joinTime: " << Tj << " health: "
         << health
            << " power: " << power << " attackCapacity: " << attackCapacity;
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
    return Tj;
}

void unit::setJoinTime(int nJoinTime) {
    unit::Tj = nJoinTime;
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
        : ID(id), type(type), Tj(joinTime), health(health), power(power), attackCapacity(attackCapacity),
          simPtr(simPtr) {}

bool unit::damageEnemy(unit *Enemy) {
    if (Enemy) {

        double Damage = (getPower() * (getHealth() / 100)) / sqrt(Enemy->getHealth());
        double NewHealth = Enemy->getHealth() - Damage;
        Enemy->setHealth(NewHealth);

        return true;
    }
    return false;
}
