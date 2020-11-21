#pragma once
#ifndef __UNITSTATS_H__
#define __UNITSTATS_H__

#define DEFAULT_SPEED 10
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
    UnitStats(float speed);
    UnitStats(int strength, int agility, int intellect);
    UnitStats(float speed, int strength, int agility, int intellect);

private:

};

#endif // __UNITSTATS_H__
