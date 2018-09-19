#include "stdafx.h"
#ifndef CHARS
#define CHARS
#include <string>

class Player {

public:
	std::string name;
	int level;
	int currentxp;
	int requiredxp;
	double health;
	int strength;
	int intelligence;
	int dexterity;
};

#endif