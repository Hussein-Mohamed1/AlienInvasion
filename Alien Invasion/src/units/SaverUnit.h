#pragma once

#include "unit.h"
#include "Esoldier.h"

enum status {
    hasntCallSAV, SAVBeingUsed, ConsumedSav
};

class SaverUnit : public Esoldier {
public:
    SaverUnit(int id, int joinTime, double health, double power, int attackCapacity, simulationManager *simPtr);
};

