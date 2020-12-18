#pragma once
#ifndef __UNITSTATS_H__
#define __UNITSTATS_H__

class UnitStats
{
public:
    double hp;
    double damage;
    double attackSpeed;
    double moveSpeed;

    UnitStats(double hp, double damage, double attackSpeed, double moveSpeed);

    void UpHP();
    void DownHP();
    void UpDamage();
    void DownDamage();
    void UpMoveSpeed();
    void DownMoveSpeed();
    void UpAttackSpeed();
    void DownAttackSpeed();

private:

};

#endif // __UNITSTATS_H__
