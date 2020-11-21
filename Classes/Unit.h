#pragma once
#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"
#include "UnitStats.h"
#include <Box2d/Box2d.h>

class Unit : public cocos2d::Node
{
public:
    b2Body* body;
    cocos2d::Sprite* sprite;
    cocos2d::Layer* layer;
    UnitStats* stats;
    bool IsDead() { return isDead; };

    Unit();

    void Damage(int value);

    void Dead();
   
    char* dmgsound;

private:
    bool isDead = false;
    int hp = 100;

};

#endif // __UNIT_H__
