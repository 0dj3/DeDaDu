#include "UnitStats.h"
#include "Definitions.h"

UnitStats::UnitStats()
{
	speed = DEFAULT_SPEED;
	strength = DEFAULT_STR;
	agility = DEFAULT_AGI;
	intellect = DEFAULT_INT;
}

UnitStats::UnitStats(float speed)
{
	this->speed = speed;
	strength = DEFAULT_STR;
	agility = DEFAULT_AGI;
	intellect = DEFAULT_INT;
}

UnitStats::UnitStats(int strength, int agility, int intellect)
{
	speed = DEFAULT_SPEED;
	this->strength = strength;
	this->agility = agility;
	this->intellect = intellect;
}

UnitStats::UnitStats(float speed, int strength, int agility, int intellect)
{
	this->speed = speed;
	this->strength = strength;
	this->agility = agility;
	this->intellect = intellect;
}