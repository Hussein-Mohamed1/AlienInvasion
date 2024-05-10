#include "ASolider.h"
#include<iostream>

void ASolider::print() const {
    std::cout << "Alien Solider -->\n";
    unit::print();
}

bool ASolider::damageEnemy(unit *ataackedUnit) {
    if (ataackedUnit->getType() == EarthSoldier || ataackedUnit->getType() == Saver) {
        return unit::damageEnemy(ataackedUnit);
    }
    return false;
}
