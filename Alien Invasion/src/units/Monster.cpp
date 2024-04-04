#include "Monster.h"
#include<iostream>

void Monster::print()   const
{
	std::cout << "Monster-->\n";
	unit::print();
}
