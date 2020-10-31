#pragma once
#ifndef __UNITSTATS_H__
#define __UNITSTATS_H__

#define DEFAULT_SPEED 3
#define DEFAULT_STR 1
#define DEFAULT_AGI 1
#define DEFAULT_INT 1

class UnitStats
{
public:
    float speed;
    int strength;
    int agility;
    int intellect;

    UnitStats();
    UnitStats(int speed);
    UnitStats(int strength, int agility, int intellect);
    UnitStats(int speed, int strength, int agility, int intellect);

private:

};

#endif // __UNITSTATS_H__
