//
// Created by youss on 4/3/2024.
//

#ifndef ALIENINVASION_ALIENARMY_H
#define ALIENINVASION_ALIENARMY_H

#include"../ds/LinkedQueue.h"
#include"../ds/DoublyLinkedQueue.h"
#include"../units/ASolider.h"
#include"../units/Drone.h"
#include"../units/Monster.h"

#include "Army.h"

class alienArmy : public Army {

    LinkedQueue<ASolider *> SoliderUnits;
    DoublyLinkedQueue<Drone *> DroneUnits;
    Monster *MonsterUnits[1000]{nullptr};
    int currentMonstersIndex{-1};
    int alienSoldierCount{0};
    int alienDroneCount{0};
    int alienDestructedSoldierCount{0};
    int alienDestructedMonsterCount{0};
    int alienDestructedDroneCount{0};
public:

    int getAliendestructedMonsterCount() const;

    int getAliendestructedSoldierCount() const;

    int getAliendestructedDroneCount() const;

    ///@todo all member functions for alienUnits must be implemented
    unit *Attack(unit *enemy);

    bool addUnit(unit *);

    void print();

    unit *getUnit(Type type);

    int getAlienDroneCount();

    int getAlienSoldierCount();

    int getCurrentMonstersIndex() const;

    unit *getRandomUnit();

    unit* getDronePair();

};


#endif //ALIENINVASION_ALIENARMY_H
