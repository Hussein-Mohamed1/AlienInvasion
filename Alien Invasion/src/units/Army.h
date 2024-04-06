//
// Created by youss on 3/31/2024.
//

#ifndef ALIENINVASION_ARMY_H
#define ALIENINVASION_ARMY_H

#include "unit.h"

class Army {
protected:
    int unitCount{0};
public:
    virtual bool addUnit(unit *) = 0;

    virtual void removeUnit(unit *) = 0;

    int getUnitCount() const;

    void setUnitCount(int unitCount);

    virtual unit *Attack(unit *) = 0;

    virtual unit *getRandomUnit() = 0;
};


#endif //ALIENINVASION_ARMY_H
