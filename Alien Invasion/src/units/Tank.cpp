//
// Created by youss on 3/31/2024.
//

#include "Tank.h"

bool Tank::attack(unit *enemy) {
    enemy->setHealth(((power * enemy->getHealth()) / 100) / sqrt(health));

    if (enemy->getHealth() <= 0)
        return true;

    return false;

}
