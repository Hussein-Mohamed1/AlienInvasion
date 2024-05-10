#pragma once

#include "iostream"
#include <fstream>
#include "randGen.h"
#include <sstream>
#include <string>
#include "./units/Esoldier.h"
#include "./units/Egunnery.h"
#include "./units/Tank.h"
#include "./units/ASolider.h"
#include "./units/Monster.h"
#include "./units/Drone.h"
#include "./units/HealUnit.h"


using namespace std;


randGen::randGen(simulationManager *simPtr) : simPtr(simPtr) {
    srand(time(nullptr));
    string S, temps, unitrang[4], probabilites[2];
    fstream *infile = new fstream("test.txt", ios::in);
    if (infile->is_open()) {
        getline(*infile, S);
        unitscreated = stoi(S);
        //get ranges of ES / ET / EG /HU
        getline(*infile, S);
        stringstream sE(S);
        for (int i = 0; i < 4; i++)
            sE >> unitrang[i];
        perES = stod(unitrang[0]);
        perET = stod(unitrang[1]);
        perEG = stod(unitrang[2]);
        perHU = stod(unitrang[3]);
        //get ranges of AS / AT / AG
        getline(*infile, S);
        stringstream sA(S);
        for (int i{}; i < 3; i++)
            sA >> unitrang[i];
        perAS = stod(unitrang[0]);
        perAM = stod(unitrang[1]);
        perAD = stod(unitrang[2]);

        getline(*infile, S);
        stringstream sP(S);
        for (int i{}; i < 2; i++)
            sP >> probabilites[i];
        prob = stoi(probabilites[0]);
        InfectedProb = stoi(probabilites[1]);
        //get ranges of health / power / capasity of Earth army
        getline(*infile, S);
        stringstream ranges(S);
        ranges >> temps;
        RangeEP1 = stod(temps.substr(0, temps.find('-')));
        RangeEP2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
        ranges >> temps;
        RangeEH1 = stod(temps.substr(0, temps.find('-')));
        RangeEH2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
        ranges >> temps;
        RangeEC1 = stoi(temps.substr(0, temps.find('-')));
        RangeEC2 = stoi(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
        //get ranges of health / power / capasity of Alien army
        getline(*infile, S);
        stringstream Ranges(S);
        Ranges >> temps;
        RangeAP1 = stod(temps.substr(0, temps.find('-')));
        RangeAP2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
        Ranges >> temps;
        RangeAH1 = stod(temps.substr(0, temps.find('-')));
        RangeAH2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
        Ranges >> temps;
        RangeAC1 = stoi(temps.substr(0, temps.find('-')));
        RangeAC2 = stoi(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
    } else throw runtime_error("Oops No file is found to read data from!");
}



unit *randGen::generatUnit(armyType unitType, int timestep) {
    double healthEunit, healthAunit, powerEunit, powerAunit;
    int Eattackcap, Aattackcap, num;

    healthEunit = rand() % int(RangeEH2 - RangeEH1 + 1) + RangeEH1; //randome Health of earth unit
    powerEunit = rand() % int(RangeEP2 - RangeEP1 + 1) + RangeEP1; //randome power of earth unit
    Eattackcap = rand() % (RangeEC2 - RangeEC1 + 1) + RangeEC1;    //randome attackcap of earth unit

    healthAunit = rand() % int(RangeAH2 - RangeAH1 + 1) + RangeAH1; //randome Health of alien unit
    powerAunit = rand() % int(RangeAP2 - RangeAP1 + 1) + RangeAP1; //randome power of alien unit
    Aattackcap = rand() % (RangeAC2 - RangeAC1 + 1) + RangeAC1;    //randome attackcap of alien unit
    switch (unitType) {
        case earthArmyType: {
            num = rand() % 101;
            if (num <= perES) {
                unit *soldier = new Esoldier(Eid++, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                return soldier;
            } else if (num <= (perES + perET)) {
                Tank *tank = new Tank(Eid++, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                return tank;
            } else if (num <= (perES + perET + perEG)) {
                unit *gunnery = new Egunnery(Eid++, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                return gunnery;
            } else {
                unit *healer = new HealUnit(Eid++, Healer, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                return healer;
            }
            case alienArmyType: {
                num = rand() % 101;
                if (num <= perAS) {
                    unit *soldier = new ASolider(Aid++, timestep, healthAunit, powerAunit, Aattackcap, simPtr);
                    return soldier;
                } else if (num <= (perAS + perAM)) {
                    unit *monster = new Monster(Aid++, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                    return monster;
                } else {
                    unit *drone = new Drone(Aid++, timestep, healthEunit, powerEunit, Eattackcap, simPtr);
                    return drone;
                }
            }
            default:
                break;
        }
            return nullptr;
    }
}

bool randGen::creatEarthUnits() const {
    int num;
    num = rand() % 100;
    if (num <= prob) {
        return true;
    }
    return false;
}

bool randGen::creatAlienUnits() const {
    int num;
    num = rand() % 100;
    if (num <= prob) {
        return true;
    }
    return false;
}

bool randGen::canInfected()  {
    int num;
    num = rand() % 100;
    if (num <= InfectedProb) {
        return true;
    }
    return false;
}
int randGen::getnumofunits() {
    return unitscreated;
}

int randGen::Eid = 1;
int randGen::Aid = 2000;
