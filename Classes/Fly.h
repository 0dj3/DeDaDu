#pragma once
#ifndef __FLY_H__
#define __FLY_H__

#include "cocos2d.h"
#include <string>
#include <Box2d/Box2d.h>
#include "PhysicHelper.h"
#include "Enemy.h"

class Fly : public Enemy
{
public:
    Fly();
    static Enemy* create(const cocos2d::Vec2& position);
    virtual void DeathRattle() override;
private:
    void update(float dt);
    void move();

};

#endif // __FLY_H__
