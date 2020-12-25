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
    static Enemy* create(const cocos2d::Vec2& position);
    virtual void DeathRattle() override;
private:
    Weapon* weapon;
    void update(float dt);

};

#endif // __SLIME_H__
