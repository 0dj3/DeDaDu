#pragma once
#ifndef __GOBLIN_H__
#define __GOBLIN_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

class Goblin : public Enemy
{
public:
    Goblin();

    static Enemy* create(cocos2d::Layer* scene);
private:
    void update(float dt);
    int hp = 30;
    void move();
};

#endif // __GOBLIN_H__
