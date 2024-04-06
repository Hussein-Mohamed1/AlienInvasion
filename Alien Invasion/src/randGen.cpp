#pragma once

#include "iostream"
#include <filesystem>
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

using namespace std;


randGen::randGen() {
    string S, temps, unitrang[3];
    fstream *infile = new fstream("./src/test.txt",ios::in);
    if (infile->is_open()) {
        getline(*infile, S);
        unitscreated = stoi(S);
        //get ranges of ES / ET / EG
        getline(*infile, S);
        stringstream sE(S);
        for (int i = 0; i < 3; i++)
            sE >> unitrang[i];
        perES = stod(unitrang[0]);
        perET = stod(unitrang[1]);
        perEG = stod(unitrang[2]);
        //get ranges of AS / AT / AG
        getline(*infile, S);
        stringstream sA(S);
        for (int i{}; i < 3; i++)
            sA >> unitrang[i];
        perAS = stod(unitrang[0]);
        perAM = stod(unitrang[1]);
        perAD = stod(unitrang[2]);
        getline(*infile, S);
        prob = stoi(S);

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


double randGen::handelPer(double per, int num) {

    // handel num of units created depening on persentage
    if ((((per * num) / 100) - int((per * num) / 100)) >= 0.5)
        per = ceil(((per * num) / 100));
    else
        per = floor(((per * num) / 100));
    return per;
}

unit *randGen::generatUnit(armytypr unitType , int timestep) {
    double healthEunit, healthAunit, powerEunit, powerAunit;
    int Eattackcap, Aattackcap, num;

    healthEunit = rand() % int(RangeEH2 - RangeEH1 + 1) + RangeEH1; //randome Health of earth unit
    powerEunit = rand() % int(RangeEP2 - RangeEP1 + 1) + RangeEP1; //randome power of earth unit
    Eattackcap = rand() % (RangeEC2 - RangeEC1 + 1) + RangeEC1;    //randome attackcap of earth unit

    healthAunit = rand() % int(RangeAH2 - RangeAH1 + 1) + RangeAH1; //randome Health of alien unit
    powerAunit = rand() % int(RangeAP2 - RangeAP1 + 1) + RangeAP1; //randome power of alien unit
    Aattackcap = rand() % (RangeAC2 - RangeAC1 + 1) + RangeAC1;    //randome attackcap of alien unit
    switch (unitType) {
        case Earthunit:  //@todo
        {
            num = rand() % 101;
            if (num <= perES)
            {
                unit* soldier = new Esoldier(Eid++, timestep, healthEunit, powerEunit, Eattackcap, nullptr);
                return soldier;
            }
            else if (num <= (perES + perET))
            {
                unit* tank = new Tank(Eid++, timestep, healthEunit, powerEunit, Eattackcap, nullptr);
                return tank;
            }
            else
            {
                unit* gunnery = new Egunnery(Eid++, timestep, healthEunit, powerEunit, Eattackcap, nullptr);
                return gunnery;
            }
        }
        case Alienunit:                                
        {
            num = rand() % 101;
            if (num <= perAS)
            {
                unit* soldier = new ASolider(Aid++, timestep, healthAunit, powerAunit, Aattackcap, nullptr);
                return soldier;
            }
            else if (num <= (perAS + perAM))
            {
                unit* monster = new Monster(Aid++, timestep, healthEunit, powerEunit, Eattackcap, nullptr);
                return monster;
            }
            else
            {
                unit* drone = new Drone(Aid++, timestep , healthEunit, powerEunit, Eattackcap, nullptr);
                return drone;
            }
        }
        default:
            break;
    }
}

bool randGen::creatEunits() {
    int num;
    num = rand() % 100;
    if (num <= prob) {
        return true;
    }
    return false;
}
bool randGen::creatAunits() {
    int num;
    num = rand() % 100;
    if (num <= prob) {
        return true;
    }
    return false;
}
int randGen::getnumofunits()
{
    return unitscreated;
}
int randGen::Eid = 1;
int randGen::Aid = 2000;

