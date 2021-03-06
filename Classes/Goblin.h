#pragma once
#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

USING_NS_CC;

class Goblin : public Enemy
{
public:
    Goblin();
   
    static Enemy* create(const cocos2d::Vec2& position, Player* player);
    Hands* hands;
    virtual void DeathRattle() override;
private:
    Vec2 targetPosition;
    Animation* idleAnimate;
    Animation* runAnimate;
    void idleGoblin(char* path);
    void update(float dt);
    void move();
};

#endif // __GOBLIN_H__
