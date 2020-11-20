#pragma once
#ifndef __SLIME_H__
#define __SLIME_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

class Slime : public Enemy
{
public:
    Slime();

    static Enemy* create(cocos2d::Layer* scene, Unit* Player);

private:
    void update(float dt);
    int hp = 30;
    void move();

};

#endif // __SLIME_H__
