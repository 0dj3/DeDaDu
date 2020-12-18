#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Item.h"
#include "ContactListener.h"

class Weapon : public Item
{
public:
    typedef enum WeaponType
    {
        MELEE,
        RANGE
    };

    WeaponType weaponType;
    std::string projectileFilename;
    std::string soundFilename;
    int damage;
    int attackRange;
    double speed;

    Weapon();

    static Weapon* create(WeaponType weaponType, std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed);

    static Weapon* create(Weapon* weapon);

    static Weapon* createMelee(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay);

    static Weapon* createRange(std::string filename, std::string projectileFilename, std::string soundFilename, int damage, double delay, int attackRange, double speed);

    void StartAttack(cocos2d::Vec2 position, cocos2d::Vec2 localTarget, ContactListener::BodyTag userTag);

private:

};

#endif // __WEAPON_H__
