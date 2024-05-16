#pragma once

#include "./units/unit.h"
#include <fstream>

class randGen {
    string scenario{};
    double perES, perET, perEG, perAS, perAM, perAD, perHU;
    double RangeEH1, RangeEH2, RangeAH1, RangeAH2, RangeEP1, RangeEP2, RangeAP1, RangeAP2, RangeSH1, RangeSH2, RangeSP1, RangeSP2;
    int unitscreated, numofSaver, RangeEC1, RangeEC2, RangeAC1, RangeAC2, prob, InfectedProb, Saverprob, probofcallSaver, RangeSC1, RangeSC2;
    static int Eid, Aid, Sid;
    simulationManager *simPtr{nullptr};
    bool hasGeneratedEarthOnce{false};
    bool hasGeneratedAlienOnce{false};
public:
    randGen(simulationManager *);

    void set_Scenario(const string &);

    unit *generatUnit(armyType, int);

    bool creatEarthUnits() const;

    unit *generatSaver(int T);

    bool creatAlienUnits() const;

    bool creatSaverUnit();

    int getnumofunits();

    int getnumofSaver();

    int get_probofcallSaver() const;

    bool canInfected() const;

    void loadInputFile();

    string get_Scenario();

    bool generatedOnceForBothArmies() const;
};

