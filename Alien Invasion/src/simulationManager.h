//
// Created by youss on 3/30/2024.
//
#pragma once
#include <fstream>
#include "randGen.h"
class randGen;
class simulationManager {
	randGen *RandomGenerator;
public:
	void manageadding(fstream* infile);
};


