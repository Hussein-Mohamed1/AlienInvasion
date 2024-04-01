#pragma once
#include <fstream>
#include "randGen.h"
#include <sstream>
#include <string>
double randGen::handelPer(double per, int num)
{

	// handel num of units created depening on persentage
	if ((((per * num) / 100) - int((per * num) / 100)) >= 0.5)
		per = ceil(((per * num) / 100));
	else
		per = floor(((per * num) / 100));
	return per;
}
void randGen::generatUnits(double per, double RH1, double RH2, double RP1, double RP2, int RC1, int RC2, Type unit)
{
	double healthunit, powerunit;
	int attackcap;
	for (int i{}; i < per; i++)
	{
		healthunit = rand() % int(RH2 - RH1 + 1) + RH1; //randome Health
		powerunit = rand() % int(RP2 - RP1 + 1) + RP1; //randome power
		attackcap = rand() % (RC2 - RC1 + 1) + RC1;    //randome attackcap
		//add unit according in its type
	}
}
void randGen::manageGeneration(fstream *infile)
{
	int num, unitscreated, perAD, prob, REC1, REC2, RAC1, RAC2;
	double REH1, REH2, REP1, REP2, RAH1, RAH2, RAP1, RAP2, perES, perET, perEG, perAS, perAM;
	string S, temps , unitrang[2];
	infile = new fstream("test.txt", ios::in);
	getline(*infile, S);
	unitscreated = stoi(S);
	//get ranges of ES / ET / EG
	getline(*infile, S);
	stringstream sE(S);
	for (int i{}; i < 3; i++)
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
	stringstream Ranges(S);
	Ranges >> temps;
	REP1 = stod(temps.substr(0, temps.find('-')));
	REP2 = stod(temps.substr(temps.find('-')+1, temps.size()- temps.find('-') - 1));
	Ranges >> temps;
	REH1 = stod(temps.substr(0, temps.find('-')));
	REH2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
	Ranges >> temps;
	REC1 = stoi(temps.substr(0, temps.find('-')));
	REC2 = stoi(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
	//get ranges of health / power / capasity of Alien army
	getline(*infile, S);
	stringstream Ranges(S);
	Ranges >> temps;
	RAP1 = stod(temps.substr(0, temps.find('-')));
	RAP2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
	Ranges >> temps;
	RAH1 = stod(temps.substr(0, temps.find('-')));
	RAH2 = stod(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));
	Ranges >> temps;
	RAC1 = stoi(temps.substr(0, temps.find('-')));
	RAC2 = stoi(temps.substr(temps.find('-') + 1, temps.size() - temps.find('-') - 1));

	num = rand() % 100;
	if (num <= prob) //generate units TODO waiting noser 
	{
		double healthunit, powerunit;
		int attackcap;
		perES = handelPer(perES, unitscreated);// handel num of units created depening on persentage
		generatUnits(perES, REH1, REH2, REP1, REP2, REC1, REC2, EarthSoldier); // add eartht soldier
		perET = handelPer(perET, unitscreated);// handel num of units created depening on persentage
		generatUnits(perET, REH1, REH2, REP1, REP2, REC1, REC2, EarthTank); // add eartht tank
		perEG = handelPer(perEG, unitscreated);// handel num of units created depening on persentage
		generatUnits(perEG, REH1, REH2, REP1, REP2, REC1, REC2, Gunnery); // add eartht gunnery
		perAS = handelPer(perAS, unitscreated);// handel num of units created depening on persentage
		generatUnits(perAS, RAH1, RAH2, RAP1, RAP2, RAC1, RAC2, alienSoldier); // add alien soldier
		perAM = handelPer(perAM, unitscreated);// handel num of units created depening on persentage
		generatUnits(perAM, RAH1, RAH2, RAP1, RAP2, RAC1, RAC2, Monster); // add alien monster
		perAD = handelPer(perAD, unitscreated);// handel num of units created depening on persentage
		generatUnits(perAD, RAH1, RAH2, RAP1, RAP2, RAC1, RAC2, Drone); // add alien Drone
	}
	num = rand() % 100;
	if (num > 0 && num < 10)
	{

	}
	else if (num > 10 && num < 20)
	{

	}
	else if (num > 20 && num < 30)
	{

	}
	else if (num > 30 && num < 40)
	{

	}
	else if (num > 40 && num < 50)
	{

	}
	else if (num > 50 && num < 60)
	{
	
	}
}


