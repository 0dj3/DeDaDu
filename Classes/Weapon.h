#pragma once
#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "cocos2d.h"
#include <Box2d/Box2d.h>

class Weapon : public cocos2d::Sprite
{
public:
    bool isActive;
    b2Body* body;
    Weapon(cocos2d::Layer* layer, int damage, float speed);

    void Attack();

private:
    cocos2d::Layer* _layer;
    int _damage = 0;
    int _speed = 0;

    void CreatePhysicBody();
};

#endif // __WEAPON_H__
