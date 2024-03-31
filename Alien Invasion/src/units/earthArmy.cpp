#include "earthArmy.h"
#include "Esoldier.h"
#include "Egunnery.h"

// #include "alienArmy.h" @TODO include alien army - Youssef Noser
unit *earthArmy::attack(unit *enemy) {

//    if (enemy->getType() == alienSoldier || enemy->getType() == Monster
//                                            && unitCount <= 0.3 *
//                                                            alienArmy->getCount()) // @TODO use the get count Here - Youssef Noser
//    {
//        unit *ETank;
//        TankList.pop(ETank);
//        return ETank;
//    }
    return nullptr;
}

bool earthArmy::addUnit(unit *earthUnit) {


    if (earthUnit->getType() == EarthSoldier)
        ESlist.enqueue(dynamic_cast<Esoldier *>(earthUnit));

    if (earthUnit->getType() == Gunnery) {
        Egunnery *Egunn = dynamic_cast<Egunnery *>(earthUnit);
        EGlist.enqueue(Egunn, Egunn->getPower() + Egunn->getHealth());
    }
    if (earthUnit->getType() == EarthTank) {
        TankList.push(earthUnit);
    }
    return true;

}

// used to remove
void earthArmy::removeUnit(unit *) {

}

void earthArmy::print() const {

}

int earthArmy::getUnitCount() const {
    return unitCount;
}
