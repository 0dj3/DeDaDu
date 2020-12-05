#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>
#include "Item.h"

class Weapon : public cocos2d::Sprite
{
public:
    bool isActive;
    Weapon(cocos2d::Layer* layer, Item* weapon);

    void Attack(cocos2d::Vec2 position);

    void ChangeWeapon(Item* weapon);

    int GetDamage() { return itemWeapon->stats.find("damage")->second; };

    int GetSpeed() { return itemWeapon->stats.find("speed")->second; };

private:
    Item* itemWeapon;
    b2Body* body;
    cocos2d::Layer* _layer;
    /*int _damage = 0;
    int _speed = 0;*/

    void CreatePhysicBody(cocos2d::Vec2 position);
};

#endif // __WEAPON_H__
