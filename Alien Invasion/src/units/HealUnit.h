#pragma once

#include "unit.h"

class HealUnit : public unit {
public:
    HealUnit() {}

    void Heal(unit *);
};

