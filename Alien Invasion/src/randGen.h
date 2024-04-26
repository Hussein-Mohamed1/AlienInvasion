#pragma once

#include "./units/unit.h"
#include <fstream>

class randGen {
    double perES, perET, perEG, perAS, perAM, perAD, perHU;
    double RangeEH1, RangeEH2, RangeAH1, RangeAH2, RangeEP1, RangeEP2, RangeAP1, RangeAP2;
    int unitscreated, RangeEC1, RangeEC2, RangeAC1, RangeAC2, prob;
    static int Eid, Aid;
    simulationManager *simPtr{nullptr};
public:
    randGen(simulationManager *);

    double handelPer(double per, int num);

    unit *generatUnit(armyType, int);

    bool creatEarthUnits() const;

    bool creatAlienUnits() const;

    int getnumofunits();
};

