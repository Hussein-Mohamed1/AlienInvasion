//
// Created by youss on 3/30/2024.
//
#pragma once
#include "simulationManager.h"
void simulationManager::manageadding(fstream* infile)
{
	RandomGenerator = new randGen();
	{
		for (int i{}; i <RandomGenerator->getnumofES() ; i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(Es)
		}
		for (int i{}; i < RandomGenerator->getnumofET(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(ET)
		}
		for (int i{}; i < RandomGenerator->getnumofEG(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(EG)
		}
		for (int i{}; i < RandomGenerator->getnumofAS(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AS)
		}
		for (int i{}; i < RandomGenerator->getnumofAM(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AM)
		}
		for (int i{}; i < RandomGenerator->getnumofAD(); i++)
		{
			// adding func of sim ( RandomeGenerator->generateunit(AD)
		}
	}

}
