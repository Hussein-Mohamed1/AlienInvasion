//
// Created by youss on 3/31/2024.
//

#ifndef ALIENINVASION_ARMY_H
#define ALIENINVASION_ARMY_H

#include "unit.h"

class Army {
public:
    virtual bool addUnit(unit *) = 0;

    virtual unit *Attack(unit *) = 0;

    virtual unit *getUnit(Type type) = 0;
};


#endif //ALIENINVASION_ARMY_H
