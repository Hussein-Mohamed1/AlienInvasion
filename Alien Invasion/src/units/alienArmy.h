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
    Monster **MonsterUnits;
    static int alienMonsterCount;
    int aleinSoldierCount{0};
    int alienDroneCount{0};
public:
    int getAlienMonsterCount() const;

    int getAleinSoldierCount() const;

    int getAlienDroneCount() const;

    ///@todo all member functions for alienUnits must be implemented
    unit *Attack(unit *enemy);

    bool addUnit(unit *);

    void removeUnit(unit *);

    void print();

    unit *getRandomUnit();

    unit *getUnit(Type type);
};


#endif //ALIENINVASION_ALIENARMY_H
