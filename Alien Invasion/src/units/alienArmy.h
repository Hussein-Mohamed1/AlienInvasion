//
// Created by youss on 4/3/2024.
//

#ifndef ALIENINVASION_ALIENARMY_H
#define ALIENINVASION_ALIENARMY_H

#include "Army.h"

class alienArmy : public Army {

public:

    ///@todo all member functions for alienUnits must be implemented
    unit *damageEnemy(unit *enemy);

    bool addUnit(unit *);

    void removeUnit(unit *);

    void print() const;

    unit *getRandomUnit();

};


#endif //ALIENINVASION_ALIENARMY_H
