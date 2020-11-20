#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include "Unit.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"

class Enemy : public Unit
{
public:
    cocos2d::PhysicsBody* body;
    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;
    UnitStats* stats;

    Enemy();

    void Damage(int value);

    void Dead();


private:
    int hp = 50;

};

#endif // __ENEMY_H__
